require jakarta-commons.inc

PR = "${INC_PR}.1"

SUMMARY = "Converts XML to a Java object by a set of mapping rules."

SRC_URI = "http://archive.apache.org/dist/commons/digester/source/${BP}-src.tar.gz"

DEPENDS += "commons-logging commons-beanutils"
RDEPENDS:${PN} = "libcommons-logging-java libcommons-beanutils-java"

CP = "commons-logging commons-beanutils"

FINDARGS = "-name '*.dtd'"

SRC_URI[sha256sum] = "d9a965c82828a881d2ab6256fba7076f62815a9545b3af9d553dc5271577182b"
