SUMMARY = "Common CA certificates (JKS trustStore)"
DESCRIPTION = "This package uses the hooks of the ca-certificates \
package to update the cacerts JKS trustStore used for many java runtimes."
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "\
	file://debian/copyright;md5=ab0f6b6900f6564dc3e273dfa36fcc72 \
	file://src/main/java/org/debian/security/InvalidKeystorePasswordException.java;endline=17;md5=f9150bf1ca3139a38ddb54f9e1c0eb9b \
	file://src/main/java/org/debian/security/KeyStoreHandler.java;endline=18;md5=3fd0e26abbca2ec481cf3698431574ae \
	file://src/main/java/org/debian/security/UnableToSaveKeystoreException.java;endline=17;md5=f9150bf1ca3139a38ddb54f9e1c0eb9b \
	file://src/main/java/org/debian/security/UnknownInputException.java;endline=17;md5=f9150bf1ca3139a38ddb54f9e1c0eb9b \
	file://src/main/java/org/debian/security/UpdateCertificates.java;endline=18;md5=3fd0e26abbca2ec481cf3698431574ae \
"
DEPENDS = "virtual/javac-native fastjar-native"
# We can't use virtual/javac-native, because that would create a
# keystore that can't be read on the target (as virtual/javac-native
# usually is either too old, or plain incompatible with this)
PACKAGE_WRITE_DEPS += "openjdk-8-native"

SRC_URI = "\
	git://salsa.debian.org/java-team/ca-certificates-java.git \
	file://0001-UpdateCertificates-handle-SYSROOT-environment-variab.patch \
	file://${BPN}.hook.in \
"

SRCREV = "793b846dcd4e79371bbe8069e4125ec2fd462e57"

inherit java

S = "${WORKDIR}/git"
B = "${WORKDIR}/build"

JARFILENAME = "${BPN}.jar"

python () {
    runtime = d.getVar("PREFERRED_RPROVIDER_java2-runtime") or ""
    if not runtime in ("openjdk-8", "openjre-8"):
        raise bb.parse.SkipRecipe("PREFERRED_RPROVIDER_java2-runtime '%s' unsupported" % runtime)
}

do_patch_append () {
    bb.build.exec_func('do_fix_sysconfdir', d)
}

do_fix_sysconfdir () {
	sed -e 's|/etc/ssl/certs/java|${sysconfdir}/ssl/certs/java|g' \
	    -i ${S}/src/main/java/org/debian/security/UpdateCertificates.java
}

do_compile () {
	mkdir -p build # simplify in-tree builds (externalsrc)
	javac -g \
	    -source 1.7 -target 1.7 -encoding ISO8859-1 \
	    -d build \
	    -sourcepath ${S}/src/main/java \
	    $(find ${S}/src/main/java -name '*.java' -type f)

	# needs to end with two empty lines
	cat << EOF > ${B}/manifest
Manifest-Version: 1.0
Main-Class: org.debian.security.UpdateCertificates

EOF
	fastjar -cfm ${JARFILENAME} ${B}/manifest -C build .
}

do_install () {
	oe_jarinstall ${JARFILENAME}

	mkdir -p ${D}${sysconfdir}/ssl/certs/java
	install -Dm0755 ${WORKDIR}/${BPN}.hook.in ${D}${sysconfdir}/ca-certificates/update.d/${BPN}-hook
	sed -e 's|@@datadir_java@@|${datadir_java}|' \
	    -e 's|@@libdir_jvm@@|${libdir_jvm}|' \
	    -e 's|@@JARFILENAME@@|${JARFILENAME}|' \
	    -i ${D}${sysconfdir}/ca-certificates/update.d/${BPN}-hook

	install -d -m0755 ${D}${sbindir}
	ln -s ${@os.path.relpath("${sysconfdir}/ca-certificates/update.d/${BPN}-hook", "${sbindir}")} \
	      ${D}${sbindir}/create-ca-certificates-java
}

pkg_postinst_${PN} () {
	if [ -n "$D" ] ; then
	    # In this case we want to use the Java in the image recipe's
	    # native sysroot (native Java, not qemu target Java) to
	    # generate the trustStore.
	    # None of the supported Java versions are in PATH, though, so
	    # we have to find a satisfactory one ourselves below $libdir_jvm.
	    # We really need the $NATIVE_ROOT variable for that to work,
	    # as STAGING_LIBDIR_JVM_NATIVE resolves to this recipe's native
	    # sysroot during recipe build time, so it's of no use during
	    # image build time.
	    if [ -z $NATIVE_ROOT ] ; then
		echo "$0: NATIVE_ROOT not known"
		false
	    fi
	    JVM_LIBDIR=$NATIVE_ROOT${libdir_jvm}
	fi
	JVM_LIBDIR=$JVM_LIBDIR $D${sbindir}/create-ca-certificates-java
}

RDEPENDS_${PN} = "ca-certificates"
RDEPENDS_${PN}_append_class-target = " java2-runtime"
RDEPENDS_${PN}_append_class-native = " virtual/java-native"

FILES_${PN} += "${datadir_java}"

BBCLASSEXTEND = "native"
