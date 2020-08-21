JDK_DIR = "openjdk-8-native"
DEPENDS = "\
    icedtea7-native ant-native \
    libxslt-native attr-native \
    glib-2.0-native freetype-native fontconfig-native \
    zip-native unzip-native make-native \
    ca-certificates-native openssl-native coreutils-native \
"

PACKAGECONFIG ??= "gif jpeg png zlib"
PACKAGECONFIG[x11] = "--with-x,,libx11-native xorgproto-native libxt-native libxext-native libxrender-native libxtst-native"
PACKAGECONFIG[cups] = "--with-cups,,cups-native"
PACKAGECONFIG[alsa] = "--with-alsa,,alsa-lib-native"
PACKAGECONFIG[gif] = "--with-giflib=system,--with-giflib=bundled,giflib-native"
PACKAGECONFIG[jce] = "--enable-unlimited-crypto,,"
PACKAGECONFIG[jpeg] = "--with-libjpeg=system,--with-libjpeg=bundled,jpeg-native"
PACKAGECONFIG[png] = "--with-libpng=system,--with-libpng=bundled,libpng-native"
PACKAGECONFIG[zlib] = "--with-zlib=system,--with-zlib=bundled,zlib-native"

EXTRA_OECONF_append = "\
    --with-jobs=${@openjdk_build_helper_get_parallel_make(d)} \
    \
    --with-tools-dir=${STAGING_DIR_NATIVE} \
    --with-boot-jdk=${STAGING_LIBDIR_NATIVE}/jvm/icedtea7-native \
    --with-extra-cflags='${CFLAGS}' \
    --with-extra-cxxflags='${CXXFLAGS}' \
    --with-extra-ldflags='${LDFLAGS}' \
    --with-freetype-include=${STAGING_INCDIR_NATIVE}/freetype2 \
    --with-freetype-lib=${STAGING_LIBDIR_NATIVE} \
    --with-stdc++lib=dynamic \
    ${@jdk_configure_options(d)} \
"
# --with-boot-jdk=${WORKDIR}/fake-jdk

inherit native

require openjdk-8-common.inc

CFLAGS_append = " ${@jdk_cpp_options(d)}"
CPPFLAGS_append = "${@jdk_cpp_options(d)}"
CXXFLAGS_append = " ${@jdk_cpp_options(d)}"

export MAKE_VERBOSE = "y"
export MFLAGS="${@jdk_make_options(d)} MAKE_VERBOSE=y QUIETLY= VERBOSE=-s LOG_LEVEL=trace"

EXTRA_OEMAKE_append = ' \
    ${@jdk_make_options(d)} \
    MAKE_VERBOSE=y VERBOSE=-s LOG_LEVEL=trace \
    QUIETLY= \
    images \
'

do_configure_prepend() {
    export JAVA_TOOL_OPTIONS="${JAVA_TOOL_OPTIONS}"
    export ${@jdk_environment_options(d)}
    unset CC CXX
}

do_compile_prepend() {
    export JAVA_TOOL_OPTIONS="${JAVA_TOOL_OPTIONS}"
    rm -f "${B}/images/j2sdk-image/jre/lib/security/cacerts"
}

do_compile_append() {
    set -x
    mkdir -p ${B}/certs
    for pem in $(find ${STAGING_DATADIR}/ca-certificates -name "*.crt")
    do
        bp=`basename ${pem}`
        alias=`echo ${bp} | sed -e 's,\.[^.]*$,,'`
        md5a=`echo ${alias} | md5sum | awk '{print $1}'`
        der=`echo ${bp} | sed -e 's,crt$,der,'`
        openssl x509 -in "${pem}" -inform pem -out "${B}/certs/${md5a}.der" -outform der
        ${B}/images/j2sdk-image/bin/keytool -importcert -noprompt -storepass changeit \
            -keystore "${B}/images/j2sdk-image/jre/lib/security/cacerts" \
            -alias "${alias}" -file "${B}/certs/${md5a}.der"
    done
    set +x
}

do_install() {
    mkdir -p ${D}${libdir_jvm}/${JDK_DIR}
    cp -rp ${B}/images/j2sdk-image/* ${D}${libdir_jvm}/${JDK_DIR}

    mkdir -p ${D}${bindir}
    for tool in keytool pack200 unpack200
    do
        ln -sf "../lib/jvm/${JDK_DIR}/bin/$tool" ${D}${bindir}/$tool
    done
}

# FIXME libfreetype.so.6 is copied from STAGING_LIBDIR which is already stripped
INSANE_SKIP_${PN} = "already-stripped"
