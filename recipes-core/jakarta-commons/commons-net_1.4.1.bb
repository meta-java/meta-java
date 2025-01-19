require jakarta-commons.inc

PR = "${INC_PR}.1"

SUMMARY = "Java Internet protocol suite library"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=3b83ef96387f14655fc854ddc3c6bd57"

SRC_URI = "http://archive.apache.org/dist/commons/net/source/${BP}-src.tar.gz"

S = "${WORKDIR}/${BP}"

DEPENDS += "oro"

RDEPENDS:${PN} = "liboro-java"
RDEPENDS:${PN}:class-native = ""

CP = "oro"

MAINSOURCES = "src/java/org"

SRC_URI[sha256sum] = "fdea779f261f70b9bbec40121c830b11e3e63b6188f662f95505045ff8d44add"

BBCLASSEXTEND = "native"
