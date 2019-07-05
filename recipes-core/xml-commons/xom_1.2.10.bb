SUMMARY = "Tree-based API for processing XML with Java"
DESCRIPTION = "XML object model which is a tree-based API for processing XML \
with Java that strives for correctness, simplicity, and performance."
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=3f18f166096348ef9d457214a2484816"

HOMEPAGE = "http://xom.nu"

# jaxen recipe depends on xom, avoid circular dependency
# upstream jaxen moved to github, do not count on ephemeral github archives
SRCNAME_jaxen = "jaxen"
SRCREV_jaxen = "7d7755ac8b19daa2ff6f319f432b864cc72d89b6"
PV_jaxen = "1.1.6"

SRC_URI = "\
	http://www.cafeconleche.org/XOM/${P}-src.tar.gz;name=archive \
	git://github.com/codehaus/${SRCNAME_jaxen};name=jaxen \
	file://04_remove_sun_import.patch \
"
SRC_URI[archive.md5sum] = "9f3a2ae827a9f6826fe76e4b7b0c22b3"
SRC_URI[archive.sha256sum] = "39985c2debb8044005fd07b09cb06f10e75652b3c048c9b4431434215332bc85"

S = "${WORKDIR}/XOM"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

inherit java-library

DEPENDS = "fastjar-native virtual/javac-native xerces-j xalan-j"

do_move_jaxen() {
    if [ -d ${WORKDIR}/git ] ; then
        mv ${WORKDIR}/git/jaxen ${WORKDIR}/jaxen-${PV_jaxen}
        rm -rf ${WORKDIR}/git
    fi

}

addtask move_jaxen after do_removebinaries before do_patch

do_compile() {
    mkdir -p build

    oe_makeclasspath cp -s xercesImpl xalan2
    cp=build:$cp

    scp="${WORKDIR}/jaxen-${PV_jaxen}/src/java/main"

    javac -sourcepath src:$scp -cp $cp -d build `find src -name "*.java" -and -not \( -wholename "*tests*" -or -wholename "*samples*" -or -wholename "*tools*" \)`
    javac -sourcepath fatsrc:$scp -cp $cp -d build `find fatsrc -name "*.java" -and -not \( -wholename "*tests*" -or -wholename "*samples*" -or -wholename "*tools*" \)`
    javac -sourcepath src15:$scp -cp $cp -d build `find src15 -name "*.java" -and -not \( -wholename "*tests*" -or -wholename "*samples*" -or -wholename "*tools*" \)`

    (cd src && find . -name "*.properties" -exec cp {} ../build/{} \;)

    # Remove Jaxen classes from build
    rm -rf build/org/jaxen
    rm -rf build/org/w3c

    fastjar -C build -c -f ${JARFILENAME} .
}
