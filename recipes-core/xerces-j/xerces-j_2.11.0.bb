DESCRIPTION = "Reference implementation of XNI, the Xerces Native Interface, and also a fully conforming XML Schema processor."
AUTHOR = "Apache Software Foundation"
LICENSE = "Apache-2.0"

PR = "r1"

LIC_FILES_CHKSUM = " \
                    file://LICENSE;md5=d273d63619c9aeaf15cdaf76422c4f87 \
                    file://LICENSE.DOM-documentation.html;md5=77c27084ca92e9a8efe9314f284acc05 \
                    file://LICENSE.DOM-software.html;md5=1f920675d8473fd5cbabf133a7e39e0d \
                    file://LICENSE.resolver.txt;md5=d229da563da18fe5d58cd95a6467d584 \
                    file://LICENSE.serializer.txt;md5=d229da563da18fe5d58cd95a6467d584 \
                   "

SRC_URI = "http://archive.apache.org/dist/xerces/j/source/Xerces-J-src.${PV}.tar.gz"

# CVE only applies to some Oracle Java SE and Red Hat Enterprise Linux versions.
# Already fixed with updates and closed.
# https://access.redhat.com/security/cve/CVE-2018-2799
# https://bugzilla.redhat.com/show_bug.cgi?id=1567542
CVE_STATUS[CVE-2018-2799] = "not-applicable-platform: Issue only applies on some Oracle Java SE and Red Hat Enterprise Linux versions"

S = "${WORKDIR}/xerces-2_11_0"

inherit java-library

JPN = "libxerces2-java"

DEPENDS = "fastjar-native jaxp1.3 xml-commons-resolver1.1"

RDEPENDS:${PN} = "libjaxp1.3-java libxml-commons-resolver1.1-java"
RDEPENDS:${PN}:class-native = ""

do_unpackpost[dirs] = "${B}"
do_unpackpost() {
  find src -exec \
    sed -i -e "s|@impl.name@|Xerces-J ${PV}|" \
           -e "s|@impl.version@|${PV}|" {} \;
}

addtask unpackpost after do_unpack before do_patch

JARFILENAME = "xercesImpl.jar"
ALTJARFILENAMES = ""

do_compile() {
  mkdir -p build

  # Prepend the bootclasspath with the earlier XML API to make
  # compilation succeed.
  oe_makeclasspath bcp -s jaxp-1.3 resolver
	bcp=$bcp:${STAGING_DATADIR_NATIVE}/classpath/glibj.zip

  javac -sourcepath src -d build -cp $bcp `find src -name "*.java"`

  (cd src && find org ! -name "*.java" -exec cp {} ../build/{} \;)

  fastjar cfm ${JARFILENAME} src/manifest.xerces -C build .

  # Like Debian we provide a symlink called xmlParserAPIs.jar pointing to the JAXP
  # classes.
  ln -sf ${D}${datadir_java}/xmlParserAPIs.jar jaxp-1.3.jar

}

SRC_URI[sha256sum] = "f59a5ef7b51bd883f2e9bda37a9360692e6c5e439b98d9b6ac1953e1f98b0680"

BBCLASSEXTEND = "native"
