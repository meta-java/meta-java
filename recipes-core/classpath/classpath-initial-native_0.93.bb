# No later version of Classpath may be used because this is the latest that can be compiled
# by jikes!

require classpath-native.inc

DESCRIPTION="Java1.4-compatible GNU Classpath variant that is used as bootclasspath for jikes-native."
DEPENDS += "jikes-native"

PR = "${INC_PR}.2"

SRC_URI += " \
	    file://autotools.patch \
	    file://miscompilation.patch \
	   "
SRC_URI[md5sum] = "ffa9e9cac31c5acbf0ea9eff9efa923d"
SRC_URI[sha256sum] = "df2d093612abd23fe67e9409d89bb2a8e79b1664fe2b2da40e1c8ed693e32945"

EXTRA_OECONF += "\
    --with-jikes=jikes \
    --with-fastjar=fastjar \
    --disable-local-sockets \
    --with-glibj-dir=${STAGING_DATADIR_NATIVE}/classpath-initial \
    --with-native-libdir=${STAGING_LIBDIR_NATIVE}/classpath-initial \
    --includedir=${STAGING_INCDIR_NATIVE}/classpath-initial \
    --with-vm=java \
"

# Ensure tools.zip is not installed at same path as classpath-native
EXTRA_OEMAKE += "pkgdatadir=${STAGING_DATADIR_NATIVE}/classpath-initial"

do_install_append() {
    # remove files clashing with classpath-native in sysroot
    rm \
       ${D}${bindir}/gappletviewer \
       ${D}${bindir}/gjarsigner \
       ${D}${bindir}/gkeytool \
       ${D}${bindir}/gjar \
       ${D}${bindir}/gnative2ascii \
       ${D}${bindir}/gserialver \
       ${D}${bindir}/grmiregistry \
       ${D}${bindir}/gtnameserv \
       ${D}${bindir}/gorbd \
       ${D}${bindir}/grmid \
       ${D}${libdir}/logging.properties \
       ${D}${libdir}/security/classpath.security
}
