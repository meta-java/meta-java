SUMMARY = "Parses, manipulates, and outputs XML using standard Java constructs"
DESCRIPTION = "JDOM aims to provide a complete, Java-based solution for \
accessing, manipulating, and outputting XML data from Java code."
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=897c700e4c122d8f4ef8f6d253a6f744"

HOMEPAGE = "http://jdom.org/"

DEPENDS = "fastjar-native virtual/javac-native jaxen"

SRC_URI = "http://www.jdom.org/dist/source/archive/jdom-${PV}.tar.gz"
SRC_URI[md5sum] = "dc8391e84cfdb170fcd8279aa370019f"
SRC_URI[sha256sum] = "d471718c4ac7a1a2f10715b93cb3fcd2ecbab60384b73ad1c089712e47bd8d1f"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

inherit java-library

S = "${WORKDIR}/${PN}"

do_compile() {
  mkdir -p build

  oe_makeclasspath cp -s jaxen

  javac -sourcepath src/java -cp $cp -d build `find src/java -name "*.java"`

  fastjar -C build -c -f ${JARFILENAME} .
}
