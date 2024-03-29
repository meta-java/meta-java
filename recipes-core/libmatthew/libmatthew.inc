SUMMARY = "Unix socket, debug and hexdump JAVA libraries"
AUTHOR = "Matthew Johnson <web@matthew.ath.cx>"
HOMEPAGE = "http://www.matthew.ath.cx/projects/java"
SECTION = "libs"
LICENSE = "MIT"
DEPENDS = "virtual/java-native classpath-native classpath"


S = "${WORKDIR}/libmatthew-java-${PV}"

PACKAGE_ARCH = "${TUNE_PKGARCH}"
inherit java-library

include recipes-core/classpath/classpath-features-check.inc

# Some internal version numbers which change from time to time.
# Allowing to override them makes this include file more
# versatile.
VER_CGI 	?= "0.6"
VER_DEBUG 	?= "1.1"
VER_HEXDUMP	?= "0.2"
VER_IO 		?= "0.1"
VER_UNIX 	?= "0.5"

do_compile() {
    oe_runmake \
        JAVAC="javac" \
        JAR="fastjar" \
        JAVAH="gjavah" \
        INCLUDES="-I${STAGING_INCDIR}/classpath" \
        LDFLAGS="-fpic -shared -lc ${LDFLAGS}" \
        LD="${CC}" \
        CFLAGS="-fpic -Wall -Os -pedantic -std=c99 -Werror"
}

# we do not have jar name corresponding to JPN
# which will be installed via JARFILENAME see java-library.bbclass
# create a dummy for install to succeed

JARFILENAME = "unix-${VER_UNIX}.jar"

do_install() {
    oe_jarinstall cgi-${VER_CGI}.jar cgi.jar
    oe_jarinstall debug-disable-${VER_DEBUG}.jar debug-disable.jar
    oe_jarinstall debug-enable-${VER_DEBUG}.jar debug-enable.jar
    oe_jarinstall hexdump-${VER_HEXDUMP}.jar hexdump.jar
    oe_jarinstall io-${VER_IO}.jar io.jar
    oe_jarinstall unix-${VER_UNIX}.jar unix.jar
    oe_libinstall -so libcgi-java ${D}${libdir_jni}
    oe_libinstall -so libunix-java ${D}${libdir_jni}
}

do_install:append() {
    rm ${D}${datadir_java}/${PN}.jar
}
PACKAGES = "\
	libcgi-java libcgi-jni libcgi-jni-dbg \
	libunixsocket-java libunixsocket-jni libunixsocket-jni-dbg \
	${PN}-io-java ${PN}-debug-java \
"

FILES:libcgi-java = "${datadir_java}/cgi*.jar"
FILES:libcgi-jni = "${libdir_jni}/libcgi-java.so"
FILES:libcgi-jni-dbg = "${libdir_jni}/.debug/libcgi-java.so"
RDEPENDS:libcgi-java = "libcgi-jni"

FILES:libunixsocket-java = "${datadir_java}/unix*.jar"
FILES:libunixsocket-jni = "${libdir_jni}/libunix-java.so"
FILES:libunixsocket-jni-dbg = "${libdir_jni}/.debug/libunix-java.so"
RDEPENDS:libunixsocket-java = "libunixsocket-jni"

FILES:${PN}-io-java = "${datadir_java}/io*.jar"

FILES:${PN}-debug-java = "${datadir_java}/debug-*.jar ${datadir_java}/hexdump*.jar"

