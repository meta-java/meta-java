require classpath-native.inc

DEPENDS += "classpath-initial-native ecj-initial-native virtual/java-initial-native"

PR = "${INC_PR}.0"

SRC_URI += " \
           file://sun-security-getproperty.patch;striplevel=0 \
           file://ecj_java_dir.patch \
           file://autotools.patch \
           file://miscompilation.patch \
           file://toolwrapper-exithook.patch \
           file://0001-Fix-bad-implementation-of-compareTo-in-BigDecimal.patch \
           file://0002-Fix-BigDecimal.stripTrailingZeros-s-handling-of-0.patch \
           "
SRC_URI[md5sum] = "0ae1571249172acd82488724a3b8acb4"
SRC_URI[sha256sum] = "f929297f8ae9b613a1a167e231566861893260651d913ad9b6c11933895fecc8"

EXTRA_OECONF += "\
    --enable-local-sockets \
    --disable-gjdoc \
    --enable-tools \
    --includedir=${STAGING_INCDIR}/classpath \
"

do_compile_append () {
    # tools using java-initial rather than java sed it out
    cd tools
    sed -e "s/java-initial/java/g" \
        -i gappletviewer gjarsigner gkeytool \
           gjar gnative2ascii gserialver grmiregistry \
           gtnameserv gorbd grmid grmic gjavah
}
