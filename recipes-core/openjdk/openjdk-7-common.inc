SUMMARY = "Java runtime based upon the OpenJDK- and Icedtea Project"
HOMEPAGE = "http://icedtea.classpath.org"
LICENSE  = "GPL-2.0-with-classpath-exception"
PRIORITY = "optional"
SECTION  = "libs"

ICEDTEA_VERSION = "${@bb.parse.BBHandler.vars_from_file(d.getVar('FILE', False),d)[1].split("-")[1] or '1.0'}"

S = "${WORKDIR}/${ICEDTEA}"

DEPENDS_append_libc-uclibc = " virtual/libiconv "

# The OpenJDK build with interpreter optimizations for ARM depends on a binary
# that generates constants for an assembler source file. There is no other
# way than to generate this on a pseudo machine. Cross-compiling would not help
# because structure sizes and/or alignment may differ.
DEPENDS_append = " qemu-native "

B = "${S}/build"

JDK_HOME = "${libdir_jvm}/${JDK_DIR}"
JDK_FAKE = "${WORKDIR}/fake-jdk"

# Puts an OE specific string into the binary making it possible for the user
# to know where it comes from (and blame the right people ...).
DIST_ID = "Built for ${DISTRO}"
DIST_NAME = "${DISTRO}"
EXTRA_OEMAKE = 'DIST_NAME="${DIST_NAME}" DIST_ID="${DIST_ID}"'

# llvm configure and compiles stuff
export WANT_LLVM_RELEASE = "2.8"

# Large stack is required at least on x86_64 host, otherwise random segfaults appear:
QEMU = "${@qemu_target_binary(d)} ${QEMU_OPTIONS} -s 2097152"

EXTRA_OEMAKE += 'QEMU="${QEMU}"'

require openjdk-common.inc

ICEDTEA = "icedtea-${ICEDTEA_VERSION}"

INC_PR = "r6"

SRC_URI = " \
    ${ICEDTEA_URI} \
    ${OPENJDK_URI} \
    ${HOTSPOT_URI} \
    ${CORBA_URI} \
    ${JAXP_URI} \
    ${JAXWS_URI} \
    ${JDK_URI} \
    ${LANGTOOLS_URI} \
    ${OEPATCHES} \
    ${ICEDTEAPATCHES} \
    file://jvm.cfg \
"

JDKPN = "openjdk-7"
JDK_DIR = "java-7-openjdk"

PN = "${JDKPN}-jre"
PROVIDES += "${JDKPN}"

DEPENDS = " \
    icedtea7-native zip-native ant-native \
    zlib libxslt-native \
    jpeg libpng giflib \
    gtk+ glib-2.0 \
    cups fontconfig \
    rhino \
    libxt libxinerama libxrender libxtst libxi \
    freetype alsa-lib libffi \
    attr \
"

# No package should directly depend on this (it should require
# java2-runtime instead).
PRIVATE_LIBS = "\
    lib.so libunpack.so libverify.so libjava.so libzip.so libnpt.so \
    libjava_crw_demo.so libhprof.so libjavanet.so libnio.so \
    libmanagement.so libinstrument.so libjsound.so libjsoundalsa.so \
    libj2pcsc.so libj2pkcs11.so libj2gss.so libmlib_image.so \
    libawt.so libsplashscreen.so libfreetype.so.6 libfontmanager.so \
    libjpeg.so liblcms.so librmi.so libjawt.so libjaas_unix.so \
    libattach.so libjdwp.so libdt_socket.so libhpi.so libjli.so \
    libmawt.so libjvm.so \
    libversionCheck.so libcompiledMethodLoad.so libgctest.so \
    libheapViewer.so libheapTracker.so libminst.so libmtrace.so \
    libwaiters.so libhprof.so \
"

export ALT_CUPS_HEADERS_PATH = "${STAGING_INCDIR}"
export ALT_FREETYPE_HEADERS_PATH = "${STAGING_INCDIR}/freetype2"
export ALT_FREETYPE_LIB_PATH = "${STAGING_LIBDIR}"
export CACAO_CONFIGURE_ARGS = " \
    ${@['','--enable-softfloat'][d.getVar('TARGET_FPU') == 'soft']}"

JAVA_HOME[unexport] = "1"

PACKAGECONFIG[kerberos] = "--enable-system-kerberos,--disable-system-kerberos,krb5"

EXTRA_OECONF = " \
    --enable-downloading=no \
    \
    --disable-tests \
    --disable-hotspot-tests \
    --disable-langtools-tests \
    --disable-jdk-tests \
    --disable-docs \
    --disable-nss \
    --disable-system-lcms \
    --disable-bootstrap \
    \
    --enable-zero \
    \
    --with-jdk-home=${STAGING_LIBDIR_JVM_NATIVE}/icedtea7-native \
    --with-rhino=${STAGING_DATADIR_JAVA}/rhino.jar \
    \
    --with-openjdk-src-zip=${WORKDIR}/${OPENJDK_FILE} \
    --with-hotspot-src-zip=${WORKDIR}/${HOTSPOT_FILE} \
    --with-corba-src-zip=${WORKDIR}/${CORBA_FILE} \
    --with-jaxp-src-zip=${WORKDIR}/${JAXP_FILE} \
    --with-jaxws-src-zip=${WORKDIR}/${JAXWS_FILE} \
    --with-jdk-src-zip=${WORKDIR}/${JDK_FILE} \
    --with-langtools-src-zip=${WORKDIR}/${LANGTOOLS_FILE} \
    \
    --with-parallel-jobs=${@openjdk_build_helper_get_parallel_make(d)} \
    \
    --with-pkgversion=${PV} \
    --with-cc-for-build=${BUILD_CC} \
    ac_cv_path_UNZIP_BIN="${STAGING_BINDIR_NATIVE}/unzip" \
"

# PCSC default value was changed to true and SCTP was added during the 2.6.0
# release so we disable them both explicitely here
EXTRA_OECONF += " \
    --disable-system-pcsc \
    --disable-system-sctp \
"

do_configure_prepend() {
    # Automatically copy everything that starts with "icedtea" (or "cacao") and ends with
    # ".patch" into the patches directory.
    find ${WORKDIR} -maxdepth 1 -name "icedtea*.patch" -exec cp {} ${S}/patches \;
    find ${WORKDIR} -maxdepth 1 -name "cacao*.patch" -exec cp {} ${S}/patches \;
}

do_configure_append() {
    oe_runmake patch
}

# Work around broken variable quoting in oe-stable 2009 and provide the variable
# via the environment which then overrides the erroneous value that was written
# into '${ICETDEA}/Makefile'.
EXTRA_OEMAKE += 'CC="${CC}" CCC="${CXX}" CPP="${CPP}" CXX="${CXX}" CC_FOR_BUILD="${BUILD_CC}"'

EXTRA_OEMAKE += ' \
    OE_CFLAGS="${TARGET_CFLAGS}" \
    OE_CPPFLAGS="${TARGET_CPPFLAGS}" \
    OE_CXXFLAGS="${TARGET_CXXFLAGS}" \
    OE_LDFLAGS="${TARGET_LDFLAGS}" \
    ZIPEXE="${STAGING_BINDIR_NATIVE}/zip" \
    CROSS_COMPILE_ARCH="${JDK_ARCH}" \
    REQUIRED_ALSA_VERSION="" \
    DISABLE_HOTSPOT_OS_VERSION_CHECK=ok \
    UNZIP_BIN="${STAGING_BINDIR_NATIVE}/unzip" \
'

OE_LAUNCHER_LDFLAGS = "-Wl,-rpath-link,${STAGING_LIBDIR}/llvm${WANT_LLVM_RELEASE} -Wl,-rpath,${libdir}/llvm${WANT_LLVM_RELEASE}"

OE_LAUNCHER_LDFLAGS_arm = ""

EXTRA_OEMAKE += 'OE_LAUNCHER_LDFLAGS="${OE_LAUNCHER_LDFLAGS}"'

do_compile() {
    bbnote "3/3 Building final JDK"

    # Build the final Hotspot + OpenJDK
    oe_runmake icedtea-stage2
}

do_install() {
    install -d ${D}${libdir_jvm}
    cp -R ${B}/${BUILD_DIR}/j2sdk-image ${D}${JDK_HOME}

    chmod u+rw -R ${D}${JDK_HOME}

    # Fix symlink which would point into staging in the binary package.
    ln -sf ${datadir_java}/rhino.jar ${D}${JDK_HOME}/jre/lib/rhino.jar

    # JRE is a subset of JDK. So to save space and resemble what the BIG distros
    # do we create symlinks from the JDK binaries to their counterparts in the
    # JRE folder (which have to exist by that time b/c of dependencies).
    for F in `find ${D}${JDK_HOME}/jre/bin -type f`
    do
        bf=`basename $F`
        bbnote "replace:" $bf
        rm ${D}${JDK_HOME}/bin/$bf
        ln -s ${JDK_HOME}/jre/bin/$bf ${D}${JDK_HOME}/bin/$bf
    done

    install -m644 ${WORKDIR}/jvm.cfg  ${D}${JDK_HOME}/jre/lib/${JDK_ARCH}/
    # workaround for shared libarary searching
    ln -sf ${JDK_HOME}/jre/lib/${JDK_ARCH}/server/libjvm.so ${D}${JDK_HOME}/jre/lib/${JDK_ARCH}/
}

# Notes about the ideas behind packaging:
# 1) User should install openjdk-7-jre. This is a provider of 'java2-runtime'.
# 2) This lets package mgmt install: openjdk-7-java
# -> openjdk-7-vm-shark|openjdk-7-vm-zero|openjdk-7-vm-cacao -> openjdk-7-common
#
# With opkg the zero VM is chosen which is good b/c that is the best known (= compatible)
# runtime. Installing other runtimes side-by-side is possible. Through jvm.cfg the following
# order of precedence is enforced: zero, shark, cacao. User can chose a different runtime
# by adding '-shark' or '-cacao' to the Java command (or by deinstalling an otherwise preferred
# runtime)
# 3) All other packages, including -jdk, are optional and not needed for normal Java apps.
PACKAGES = " \
    ${JDKPN}-jre \
    ${JDKPN}-jre-dbg \
    ${JDKPN}-dbg \
    ${JDKPN}-demo-dbg \
    ${JDKPN}-demo \
    ${JDKPN}-source \
    ${JDKPN}-doc \
    ${JDKPN}-jdk \
    ${JDKPN}-java \
    ${JDKPN}-vm-zero \
    ${JDKPN}-common \
"

FILES_${JDKPN}-dbg = "\
    ${JDK_HOME}/bin/.debug \
    ${JDK_HOME}/lib/.debug \
    ${JDK_HOME}/lib/${JDK_ARCH}/jli/.debug \
    ${JDK_HOME}/jre/bin/.debug \
    ${JDK_HOME}/jre/lib/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/jli/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/native_threads/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/server/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/headless/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/xawt/.debug \
    ${JDK_HOME}/jre/lib/${JDK_ARCH}/client/.debug \
"

FILES_${JDKPN}-demo = "${JDK_HOME}/demo ${JDK_HOME}/sample"
RDEPENDS_${JDKPN}-demo = "${JDKPN}-jre"
FILES_${JDKPN}-demo-dbg = "\
    ${JDK_HOME}/demo/jvmti/gctest/lib/.debug \
    ${JDK_HOME}/demo/jvmti/heapTracker/lib/.debug \
    ${JDK_HOME}/demo/jvmti/heapViewer/lib/.debug \
    ${JDK_HOME}/demo/jvmti/hprof/lib/.debug \
    ${JDK_HOME}/demo/jvmti/minst/lib/.debug \
    ${JDK_HOME}/demo/jvmti/mtrace/lib/.debug \
    ${JDK_HOME}/demo/jvmti/versionCheck/lib/.debug \
    ${JDK_HOME}/demo/jvmti/waiters/lib/.debug \
    ${JDK_HOME}/demo/jvmti/compiledMethodLoad/lib/.debug \
"

FILES_${JDKPN}-source = "${JDK_HOME}/src.zip"

FILES_${JDKPN}-java = "${JDK_HOME}/jre/bin/java"

FILES_${JDKPN}-vm-zero = "${JDK_HOME}/jre/lib/${JDK_ARCH}/server/"

FILES_${JDKPN}-common = "${JDK_HOME}/jre/ASSEMBLY_EXCEPTION \
    ${JDK_HOME}/jre/THIRD_PARTY_README \
    ${JDK_HOME}/jre/LICENSE \
    ${JDK_HOME}/ASSEMBLY_EXCEPTION \
    ${JDK_HOME}/THIRD_PARTY_README \
    ${JDK_HOME}/LICENSE \
    ${JDK_HOME}/release \
    ${JDK_HOME}/jre/lib \
"

FILES_${PN}_append = " \
    ${JDK_HOME}/jre/bin/keytool \
    ${JDK_HOME}/jre/bin/orbd \
    ${JDK_HOME}/jre/bin/pack200 \
    ${JDK_HOME}/jre/bin/rmid \
    ${JDK_HOME}/jre/bin/rmiregistry \
    ${JDK_HOME}/jre/bin/servertool \
    ${JDK_HOME}/jre/bin/tnameserv \
    ${JDK_HOME}/jre/bin/unpack200 \
    ${JDK_HOME}/jre/bin/policytool \
    ${JDK_HOME}/jre/bin/javaws \
"

RDEPENDS_${JDKPN}-common = "librhino-java"

RPROVIDES_${JDKPN}-vm-zero = "java2-vm"

# Even though a vm is a hard dependency it is set as RRECOMMENDS so a single vm can get uninstalled:
# root@beaglebone:~/java# opkg remove openjdk-7-vm-shark
# No packages removed.
# Collected errors:
#  * print_dependents_warning: Package openjdk-7-vm-shark is depended upon by packages:
#  * print_dependents_warning: 	openjdk-7-java
#  * print_dependents_warning: These might cease to work if package openjdk-7-vm-shark is removed.
RRECOMMENDS_${JDKPN}-java = "java2-vm"

# For some reason shark and cacao do not automatically depends on -common.
# So we add that manually.

# There is a symlink to a .so but this one is valid.
INSANE_SKIP_${JDKPN}-vm-zero = "dev-so"
INSANE_SKIP_${JDKPN}-common = "dev-so"

# libfreetype.so.6 is copied from STAGING_LIBDIR
# which is already stripped.
INSANE_SKIP_${JDKPN}-jre = "already-stripped"

FILES_${JDKPN}-jdk = " \
    ${JDK_HOME}/bin \
    ${JDK_HOME}/lib \
    ${JDK_HOME}/include \
    ${JDK_HOME}${libdir}/jvm \
"
RDEPENDS_${JDKPN}-jre = "${JDKPN}-java ${JDKPN}-common"
RDEPENDS_${JDKPN}-java = "${JDKPN}-common"
RPROVIDES_${JDKPN}-jre = "java2-runtime"

RDEPENDS_${JDKPN}-jdk = "${JDKPN}-jre"

FILES_${JDKPN}-doc = "${JDK_HOME}/man"

# Name of the directory containing the compiled output
BUILD_DIR = "openjdk.build"
BUILD_DIR_ECJ = "openjdk.build-ecj"

# Force arm mode for now
ARM_INSTRUCTION_SET_armv4t = "ARM"

ICEDTEA_URI = "http://icedtea.wildebeest.org/download/source/${ICEDTEA}.tar.gz;name=iced"

ICEDTEA_MAJOR = "icedtea7"
ICEDTEA_DROP_URL = "http://icedtea.classpath.org/download/drops/${ICEDTEA_MAJOR}/${ICEDTEA_VERSION}"

OPENJDK_FILE = "openjdk.tar.bz2"
OPENJDK_URI = "${ICEDTEA_DROP_URL}/${OPENJDK_FILE};name=openjdk;unpack=false"

HOTSPOT_FILE = "hotspot.tar.bz2"
HOTSPOT_URI = "${ICEDTEA_DROP_URL}/${HOTSPOT_FILE};name=hotspot;unpack=false"

CORBA_FILE = "corba.tar.bz2"
CORBA_URI = "${ICEDTEA_DROP_URL}/${CORBA_FILE};name=corba;unpack=false"

JAXP_FILE = "jaxp.tar.bz2"
JAXP_URI = "${ICEDTEA_DROP_URL}/${JAXP_FILE};name=jaxp;unpack=false"

JAXWS_FILE = "jaxws.tar.bz2"
JAXWS_URI = "${ICEDTEA_DROP_URL}/${JAXWS_FILE};name=jaxws;unpack=false"

JDK_FILE = "jdk.tar.bz2"
JDK_URI = "${ICEDTEA_DROP_URL}/${JDK_FILE};name=jdk;unpack=false"

LANGTOOLS_FILE = "langtools.tar.bz2"
LANGTOOLS_URI = "${ICEDTEA_DROP_URL}/${LANGTOOLS_FILE};name=langtools;unpack=false"

# handles all postinst action for openjdk
# some of the former results in a build error because "ERR" is in the first line.

pkg_postinst_ontarget_${JDKPN}-vm-shark () {
    true
    if grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && ! grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        sed -i -e "/\-shark.*/d" -e "s|\(^\-server*\)|\-shark KNOWN\n\1|" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    else
        sed -i -e "s/\-shark.*/\-shark KNOWN/" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi
}

pkg_prerm_${JDKPN}-vm-shark () {
    true
    sed -i -e "/^\-shark.*/d" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    if grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        FIRST_KNOWN=`grep "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg | head -n 1`
        sed -i -e "/${FIRST_KNOWN}/d" -e  "s|\(^\-server*\)|${FIRST_KNOWN}\n\1|" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi

    echo "-shark ERROR" >> ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
}

pkg_postinst_ontarget_${JDKPN}-vm-cacao () {
    true
    if grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && ! grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        sed -i -e "/\-cacao.*/d" -e "s|\(^\-server*\)|\-cacao KNOWN\n\1|" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    else
        sed -i -e "s/\-cacao.*/\-cacao KNOWN/" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi
}

pkg_prerm_${JDKPN}-vm-cacao () {
    true
    sed -i -e "/^\-cacao.*/d" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    if grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        FIRST_KNOWN=`grep "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg | head -n 1`
        sed -i -e "/${FIRST_KNOWN}/d" -e  "s|\(^\-server*\)|${FIRST_KNOWN}\n\1|" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi

    echo "-cacao ERROR" >> ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
}

pkg_postinst_ontarget_${JDKPN}-vm-jamvm () {
    true
    if grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && ! grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        sed -i -e "/\-jamvm.*/d" -e "s|\(^\-server*\)|\-jamvm KNOWN\n\1|" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    else
        sed -i -e "s/\-jamvm.*/\-jamvm KNOWN/" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi
}

pkg_prerm_${JDKPN}-vm-jamvm () {
    true
    sed -i -e "/^\-jamvm.*/d" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    if grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        FIRST_KNOWN=`grep "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg | head -n 1`
        sed -i -e "/${FIRST_KNOWN}/d" -e  "s|\(^\-server*\)|${FIRST_KNOWN}\n\1|" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi

    echo "-jamvm ERROR" >> ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
}

pkg_postinst_ontarget_${JDKPN}-vm-zero () {
    true
    if grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg && grep -q "\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        FIRST_KNOWN=`grep "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg | head -n 1`
        sed -i -e "/${FIRST_KNOWN}/d" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
        echo ${FIRST_KNOWN} >> ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi

    sed -i -e "s|^\-server.*|\-server KNOWN|" -e "/^$/d" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
}

pkg_prerm_${JDKPN}-vm-zero () {
    true
    sed -i -e "/^\-server.*/\-server ERROR" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    if grep -q "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg; then
        FIRST_KNOWN=`grep "KNOWN" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg | head -n 1`
        sed -i -e "/${FIRST_KNOWN}/d" -e  "s|\(^\-server*\)|${FIRST_KNOWN}\n\1|" ${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi
}

pkg_postinst_${JDKPN}-jre () {
    ln -s ${JDK_HOME}/jre  $D/${libdir}/jvm/jre
}

inherit update-alternatives

ALTERNATIVE_${JDKPN}-jre = "java keytool"
ALTERNATIVE_${JDKPN}-jdk = "javac"

ALTERNATIVE_TARGET[java] = "${JDK_HOME}/jre/bin/java"
ALTERNATIVE_TARGET[javac] = "${JDK_HOME}/bin/javac"
ALTERNATIVE_TARGET[keytool] = "${JDK_HOME}/jre/bin/keytool"

ALTERNATIVE_LINK_NAME[java] = "${bindir}/java"
ALTERNATIVE_LINK_NAME[javac] = "${bindir}/javac"
ALTERNATIVE_LINK_NAME[keytool] = "${bindir}/keytool"

ALTERNATIVE_PRIORITY = "50"
