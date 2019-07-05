SUMMARY = "A simple and flexible library for working with XML, XPath and XSLT"
DESCRIPTION = "dom4j is a simple and flexible Java library for working with XML, XPath and XSLT"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=3f752b663f2a821c3b32482fc6aece3c"

HOMEPAGE = "http://dom4j.github.io"

DEPENDS = "fastjar-native virtual/javac-native \
           xerces-j xalan-j xpp2 xpp3 jaxen"

SRC_URI = "\
        ${SOURCEFORGE_MIRROR}/dom4j/${P}.tar.gz;name=archive \
        http://archive.apache.org/dist/ws/jaxme/source/ws-jaxme-0.5.2-src.tar.gz;name=jaxme \
        file://debian.patch \
"
SRC_URI[archive.md5sum] = "1e7ef6d20939315714de4a8502f27b2d"
SRC_URI[archive.sha256sum] = "01b4abf86bce337a2a900bf121b3107320ba63b4c0f352e1922fbec6e0736c6f"
SRC_URI[jaxme.md5sum] = "084ebfe4a816058f8ff6bd731fa70df4"
SRC_URI[jaxme.sha256sum] = "0415d721259acf95c564fb84606bb17f6227c1cc444e89b78d1cd9903c1c88dc"

PACKAGE_ARCH = "${TUNE_PKGARCH}"
inherit java-library

do_compile() {
  mkdir -p build

  oe_makeclasspath cp -s xercesImpl xalan2 xpp2 xpp3 jaxen
	scp="src/java:${WORKDIR}/ws-jaxme-0.5.2/src/api"

  javac -sourcepath $scp -cp $cp -d build `find src/java -name "*.java" -and -not -wholename "*datatype*"`
  (cd src/java && find org -name "*.properties" -exec cp {} ../../build/{} \;)

	rm -rf build/org/w3c
	rm -rf build/javax

  fastjar -C build -c -f ${JARFILENAME} .
}
