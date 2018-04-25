SUMMARY = "Design quality metrics generator for each Java"

# see https://github.com/clarkware/jdepend/blob/master/LICENSE
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://LICENSE;md5=f5777d32a7709d558c2877d4a6616230"

HOMEPAGE = "https://github.com/clarkware/jdepend"

SRC_URI = "git://github.com/clarkware/jdepend"
SRCREV = "57980590313a5dbde236a3eb2c8958e9e53e6a10"
S = "${WORKDIR}/git"

inherit java-library

do_compile() {
  mkdir -p build

  javac -sourcepath src -d build `find src -name "*.java"`

  fastjar cf ${JARFILENAME} -C build .
}

BBCLASSEXTEND = "native"
