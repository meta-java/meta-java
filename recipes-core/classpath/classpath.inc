SUMMARY = "GNU Classpath standard Java libraries"
HOMEPAGE = "http://www.gnu.org/software/classpath/"
SECTION = "libs"

# GPLv2 + custom linking exception
LICENSE = "GPL-2.0 & SAX-PD"

PBN = "classpath"

inherit autotools pkgconfig java gettext

DEPENDS = "virtual/javac-native fastjar-native zip-native gmp antlr-native gtk+ gconf libxtst file"

RPROVIDES:${PN} = ""

RDEPENDS:${PN} = "${PBN}-common (>= ${PV})"
RDEPENDS:${PN}-examples = "java2-runtime ${PN}-awt"
RDEPENDS:${PN}-tools = "java2-runtime"

RPROVIDES:${PN} = "${PBN}"
RPROVIDES:${PN}-common = "${PBN}-common"
RPROVIDES:${PN}-gtk = "${PBN}-awt"

PR = "r3"

SRC_URI = "${GNU_MIRROR}/classpath/classpath-${PV}.tar.gz"

S = "${WORKDIR}/${PBN}-${PV}"

export JAVA = "java"
export JAVAC = "javac"

EXTRA_OECONF = "\
  --with-glibj \
  --with-jar=${STAGING_BINDIR_NATIVE}/fastjar \
  --includedir=${includedir}/classpath \
  --disable-Werror \
  --with-antlr-jar=${STAGING_DATADIR_JAVA_NATIVE}/antlr.jar \
  --with-gmp=${STAGING_LIBDIR}/.. \
  --disable-alsa \
  --disable-dssi \
  --disable-plugin \
  --enable-gconf-peer \
  --enable-gtk-peer \
  --enable-local-sockets \
  "


EXTRA_OECONF += "\
               "

do_configure:prepend () {
  cp ${STAGING_DATADIR_NATIVE}/gettext/config.rpath ${S}
}
	

do_install() {
	autotools_do_install
	mv ${D}${libdir}/security ${D}${libdir}/${PBN}
}

# We really have valid non-symlink .so files
INSANE_SKIP:${PN} = "dev-so"

# Defines the packages that this classpath recipe creates.
# This allows the classpath-minimal variants to override this
# again.
CPPACKAGES = "${PBN}-common ${PN}-examples \
             ${PN}-tools ${PN}-tools-doc \
             ${PN}-gtk ${PN}-gconf"

PACKAGES =+ "${CPPACKAGES}"

FILES:${PN}-dev += "${libdir}/${PBN}/*.la ${incdir}/${PBN}"

FILES:${PBN}-common = "${datadir}/${PBN}/glibj.zip ${libdir}/logging.properties ${libdir}/${PBN}/security"
FILES:${PN}-examples = "${datadir}/${PBN}/examples"

FILES:${PN}-tools = "${datadir}/${PBN}/tools.zip ${bindir}"
FILES:${PN}-tools-doc = "${mandir}"

FILES:${PN}-dbg += "${libdir}/${PBN}/.debug"
FILES:${PN}-doc = "${infodir}"

# gcjwebplugin - not built yet
#FILES_${PN}-gcjwebplugin = "${libdir}/${PBN}/libgcjwebplugin.so"
FILES:${PN}-gtk = "${libdir}/${PBN}/libgtkpeer.so ${libdir}/${PBN}/libjawt.so"
FILES:${PN}-gconf = "${libdir}/${PBN}/libgconfpeer.so"
FILES:${PN} = "${libdir}/${PBN}/lib*so*"

