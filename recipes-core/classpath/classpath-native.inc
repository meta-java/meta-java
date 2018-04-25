SUMMARY = "GNU Classpath standard Java libraries - For native Java-dependent programs"
HOMEPAGE = "http://www.gnu.org/software/classpath/"
LICENSE = "GPL-2.0 & SAX-PD"
LIC_FILES_CHKSUM = "file://COPYING;md5=af0004801732bc4b20d90f351cf80510"

DEPENDS = "fastjar-native zip-native"

inherit autotools native gettext

SRC_URI = "${GNU_MIRROR}/classpath/classpath-${PV}.tar.gz"

INC_PR = "r6"

export JAVA="${STAGING_BINDIR_NATIVE}/java-initial"
export JAVAC="${STAGING_BINDIR_NATIVE}/ecj-initial"
export JAVACFLAGS="-nowarn"

EXTRA_OECONF = "\
    --with-glibj \
    --disable-Werror \
    --disable-alsa \
    --disable-gconf-peer \
    --disable-gtk-peer \
    --disable-plugin \
    --disable-dssi \
    --disable-examples \
"
