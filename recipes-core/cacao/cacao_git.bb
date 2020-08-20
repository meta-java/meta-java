SUMMARY = "CacaoVM for use as OpenEmbedded's Java VM"
HOMEPAGE = "http://www.cacaojvm.org/"
LICENSE  = "GPL-2.0"
LIC_FILES_CHKSUM = "file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552"
SECTION  = "interpreters"

DEPENDS_class-native = "zlib-native libtool-native ecj-initial-native fastjar-native classpath-initial-native classpath-native bdwgc-native virtual/java-initial-native"
PROVIDES_class-native = "virtual/java-native"

DEPENDS = "zlib libtool classpath virtual/javac-native bdwgc"
RPROVIDES_${PN} = "java2-runtime"

SRCREV = "6c4694f9bd175386a8c451531e9a5ad97aa23b6f"
SRC_URI = "git://bitbucket.org/cacaovm/cacao.git;protocol=https \
           file://0001-java.in-Do-not-use-hardcode-paths.patch \
           file://0002-cacao-use-system-s-boehm-garbage-collector.patch \
"
S = "${WORKDIR}/git"

inherit java autotools-brokensep update-alternatives pkgconfig features_check

REQUIRED_DISTRO_FEATURES = "x11"
REQUIRED_DISTRO_FEATURES_class-native := ""

EXTRA_OECONF_class-native = "\
    --enable-debug \
    --with-vm-zip=${datadir}/cacao/vm.zip \
    --with-java-runtime-library-classes=${datadir}/classpath/glibj.zip \
    --with-java-runtime-library-libdir=${libdir_jni}:${libdir} \
    --with-jni_md_h=${includedir}/classpath \
    --with-jni_h=${includedir}/classpath \
    --disable-test-dependency-checks \
    --disable-libjvm  \
"

CACHED_CONFIGUREVARS_class-native += "ac_cv_prog_JAVAC=${STAGING_BINDIR_NATIVE}/ecj-initial"

EXTRA_OECONF = "\
    --with-vm-zip=${datadir}/cacao/vm.zip \
    --disable-libjvm \
    --with-build-java-runtime-library-classes=${STAGING_DATADIR}/classpath/glibj.zip \
    --with-jni_h=${STAGING_INCDIR}/classpath \
    --with-jni_md_h=${STAGING_INCDIR}/classpath \
    --with-java-runtime-library-classes=${datadir}/classpath/glibj.zip \
    --with-java-runtime-library-libdir=${libdir_jni}:${libdir} \
    --disable-test-dependency-checks \
"

do_configure_prepend () {
    # upgrade m4 macros in source tree
    libtoolize --force --copy --install
    rm  -f src/mm/boehm-gc/ltmain.sh
    mkdir -p src/mm/boehm-gc/m4
}

do_install_append_class-target() {
    rm ${D}/${bindir}/java
}

FILES_${PN} = "${bindir}/${PN} ${libdir}/cacao/lib*.so ${libdir}/lib*.so* ${datadir}/${PN}"
FILES_${PN}-dbg += "${bindir}/.debug ${libdir}/.debug/lib*.so*"
FILES_${PN}-doc += "${datadir}/gc"

BBCLASSEXTEND = "native"

COMPATIBLE_MACHINE_aarch64 = "-"
