SUMMARY = "Servlet API 2.4 (from Tomcat 5.5)"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"
AUTHOR = "Apache Software Foundation"

SRC_URI = "http://archive.apache.org/dist/tomcat/tomcat-5/v${PV}/src/apache-tomcat-${PV}-src.tar.gz"

S = "${WORKDIR}/apache-tomcat-${PV}-src/servletapi/jsr154"

inherit java-library

DEPENDS = "fastjar-native"

# Value of implementation.revision in build.xml
IMPL_REVISION = "1"

JARFILENAME = "servlet-api-2.4.${IMPL_REVISION}.jar"
ALTJARFILENAMES = "servlet-api-2.4.jar servlet-api.jar servlet2.4.jar"

do_unpackpost[dirs] = "${B}"
do_unpackpost() {
  sed -i -e "s|2.3.@implementation.version@|2.4.${IMPL_REVISION}|" src/etc/manifest
}

addtask unpackpost after do_unpack before do_patch

do_compile() {
  mkdir -p build

  javac -sourcepath src/share -d build `find src/share/javax -name \*.java`

  # Copy extraneous files according to build.xml's compile task
  (cd src/share && find . -name "*.properties" -exec cp {} ../../build/{} \;)

  mkdir -p build/javax/servlet/resources
  cp src/share/dtd/jsp*.dtd build/javax/servlet/resources
  cp src/share/dtd/web-jsp*.dtd build/javax/servlet/resources

  fastjar -C build -c -m src/etc/manifest -f ${JARFILENAME} .
}

SRC_URI[sha256sum] = "ddc677d7391c438e6102d0b3e9653eaca661344ef74b0260c1f488340d660395"
