# This package compiles and stages only the Jar

SUMMARY = "JDT Core Batch Compiler - Jar only"
HOMEPAGE = "http://www.eclipse.org/"
LICENSE = "EPL-1.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/EPL-1.0;md5=57f8d5e2b3e98ac6e088986c12bf94e6"

DEPENDS = "classpath-initial-native fastjar-native jikes-initial-native virtual/java-initial-native"

INC_PR = "r5"

inherit native java

S = "${WORKDIR}"

JAR = "ecj-bootstrap-${PV}.jar"

do_unpackpost[dirs] = "${B}"
do_unpackpost() {
  mkdir -p source
  mkdir -p build

  # Remove crap.
  rm -f about.html build.xml
  rm -rf META-INF

  # Move source into separate subdir.
  if [ -d org  -a ! -d source/org ]; then
    mv org source/
  fi
  # Remove stuff unneeded for the bootstrap compiler.
  rm -rf source/org/eclipse/jdt/internal/compiler/apt
  rm -rf source/org/eclipse/jdt/internal/compiler/tool
  rm -rf source/org/eclipse/jdt/internal/antadapter
  rm -f source/org/eclipse/jdt/core/JDTCompilerAdapter.java

  # Make a copy of the remaining source to get the embedded
  # resources.
  cp -R source/org build/

  # Remove source code and other stuff.
  find build -depth \( -name '*.java' -o -name '*.html' \) -delete
}

addtask unpackpost after do_unpack before do_patch

do_compile() {
  # Compiling in place is done because the sources contain
  # property files which need to be available at runtime.
  find source -name '*.java' -print0 \
    | LC_ALL=C sort -z \
    | xargs -0 -n25 -P ${BB_NUMBER_THREADS} \
        jikes-initial -d build -source 1.4 -sourcepath source

  fastjar -c -C build . -f ${JAR}
}

do_install() {
  oe_jarinstall ${JAR} ecj-bootstrap.jar
}

