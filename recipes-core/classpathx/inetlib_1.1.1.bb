SUMMARY = "A Java library of clients for common internet protocols"
DESCRIPTION = "GNU Classpath inetlib is an extension library to provide \
extra network protocol support for GNU Classpath and ClasspathX project, \
but it can also used standalone to add http, imap, pop3 and smtp client \
support applications. \
"
AUTHOR = "GNU Classpath"
HOMEPAGE = "http://gnu.org/software/classpath/inetlib.html"
LICENSE = "GPL-2.0-with-GCC-exception"
LIC_FILES_CHKSUM = "file://COPYING;md5=0636e73ff0215e8d672dc4c32c317bb3"

SRC_URI = "http://ftp.gnu.org/gnu/classpath/${BP}.tar.gz \
           file://datadir_java.patch \
           file://inetlib-missing-dependency-for-util_classes.patch \
          "
SRC_URI[md5sum] = "aaa24be4bc8d172ac675be8bdfa636ee"
SRC_URI[sha256sum] = "1b078a39e022f86e4e2c8189b4d2789a5da414e8f1cb285587b7800b950a44de"

DEPENDS = "classpath-initial-native \
           virtual/javac-native \
"
inherit java-library autotools

JPN = "libgnuinet-java"

export JAVAC = "javac"

export JAVA = "java"

# We fake this, it is not neccessary anyway.
export JAVADOC = "true"

do_compile() {
  oe_runmake JARDIR=${datadir_java} inetlib_jar=${JARFILENAME}
}

BBCLASSEXTEND = "native"
