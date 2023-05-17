SUMMARY = "Lexical analyzer generator for Java"
LICENSE = "MPL-2.0"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=8e2372bdbf22c99279ae4599a13cc458"

DEPENDS:class-native += "classpath-native"

BBCLASSEXTEND = "native"

PACKAGE_ARCH = "${TUNE_PKGARCH}"

inherit java-library

SRCREV = "82ffb8f3e09e77e3b1f5782c35b621e7ca742b58"
SRC_URI = "\
	git://github.com/mozilla/rhino;protocol=https;branch=master \
	file://rhino \
	file://rhino-jsc \
	"

S = "${WORKDIR}/git"

PACKAGES = "${JPN} rhino"

FILES:${PN} = "${bindir}/rhino ${bindir}/rhino-jsc"
RDEPENDS:${PN} = "java2-runtime ${JPN}"
RDEPENDS:${PN}:class-native = ""

do_compile() {
	mkdir -p build

	# Compatibility fix for jamvm which has non-genericised
	# java.lang classes. :(
	bcp_arg="-bootclasspath ${STAGING_DATADIR_NATIVE}/classpath/glibj.zip"

	javac $bcp_arg -source 1.6 -sourcepath src -d build `find src -name "*.java"`

	mkdir -p build/org/mozilla/javascript/resources
	cp src/org/mozilla/javascript/resources/*.properties build/org/mozilla/javascript/resources

	fastjar cfm ${JARFILENAME} ${S}/src/manifest -C build .
}

do_install:append() {
	install -d ${D}${bindir}

	install -m 0755 ${WORKDIR}/rhino ${D}${bindir}
	install -m 0755 ${WORKDIR}/rhino-jsc ${D}${bindir}
}

SRC_URI[md5sum] = "1f893577269631703d31e4de9d5dc1f4"
SRC_URI[sha256sum] = "860965fc611764745b3a4fc5bd4baac07356a9fedd2ce6642e7bb0bd7ef58d07"
