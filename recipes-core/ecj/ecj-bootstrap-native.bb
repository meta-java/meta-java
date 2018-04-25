# ECJ as a bootstrap compiler is a drop-in replacement for Sun's javac. It offers no more
# and no less features.
#
# This recipe uses the jar created by libecj-bootstrap.

SUMMARY = "JDT Core Batch Compiler - Bootstrap variant"
HOMEPAGE = "http://www.eclipse.org/"
SECTION = "devel"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420 \
                   "
PR = "r1"

DEPENDS = "libecj-bootstrap-native virtual/java-native"

PROVIDES = "virtual/javac-native"

SRC_URI = "file://ecj.in"

S = "${WORKDIR}"

JAR = "ecj-bootstrap.jar"

inherit native

do_compile() {
  # Create the start script
  echo "#!/bin/sh" > ecj-bootstrap

  # get absolute path to parent directory, and use that as base path for the jar
  echo "SH_DIR=\`dirname "\$0"\`" >> ecj-bootstrap
  echo "CURRENT_DIR=\`cd "\${SH_DIR}" && pwd\`" >> ecj-bootstrap
  echo "PARENT_DIR=\`dirname \${CURRENT_DIR}\`" >> ecj-bootstrap

  echo "ECJ_JAR=\${PARENT_DIR}/share/java/${JAR}" >> ecj-bootstrap
  echo "RUNTIME=java" >> ecj-bootstrap
  cat ecj.in >> ecj-bootstrap
}

do_install() {
  install -d ${D}${bindir}
  install -m 755 ${S}/ecj-bootstrap ${D}${bindir}
  install -m 755 ${S}/ecj-bootstrap ${D}${bindir}/javac
}
