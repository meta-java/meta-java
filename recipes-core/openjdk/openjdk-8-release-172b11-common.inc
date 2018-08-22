PATCHES_URI = "\
    file://remove-shell-variables-from-autoheader.patch;striplevel=0 \
    file://filter-aclocal-copy-too.patch;striplevel=0 \
    file://dont-expect-fqpn-for-make.patch;striplevel=0 \
    file://openjdk8-no-genx11-in-headless.patch;striplevel=0 \
    file://openjdk8-no-unused-deps.patch;striplevel=0 \
    file://openjdk8-find-compiler-fix-env-respect.patch;striplevel=0 \
    file://openjdk8-prevent-debuginfo-in-favour-of-openembedded-package-split.patch;striplevel=0 \
    file://0001-jdk-comparison-between-pointer-and-integer.patch \
    file://0002-hotspot-fix-compilation-with-security-flags-enabled.patch \
    file://0003-jdk-Allow-using-a-system-installed-libjpeg.patch \
    file://0004-jdk-Allow-using-a-system-installed-libpng.patch \
    file://0005-hotspot-use-correct-include-for-poll.patch \
    file://0006-hotspot-don-t-rely-on-old-SysV-SIGCLD.patch \
    file://0007-jdk-use-correct-include-for-poll.patch \
    file://0008-jdk-use-correct-include-for-signal.patch \
    file://0009-jdk-disable-backtrace-musl-build-fix.patch \
    file://0010-build-fix-build-on-as-needed-toolchains-generic.patch \
    file://0011-hotspot-backport-patch-to-fix-misuses-of-strncpy-str.patch \
    ${HOTSPOT_UB_PATCH} \
    ${LIBPNG_NEON_PATCH} \
    file://handle_extra_output.patch \
"
HOTSPOT_UB_PATCH = "\
    file://0014-hotspot-zero-fix-undefined-behaviour-gcc-v8-fix.patch \
    file://0015-hotspot-fix-Wreturn-type-issues-introduced-by-806165.patch \
    file://0016-hotspot-Zero-build-requires-disabled-warnings.patch \
    file://0017-hotspot-Missing-return-statement-in-__sync_val_compa.patch \
    file://0018-hotspot-Fix-debug-build-after-8062808-Turn-on-the-Wr.patch \
    file://0019-hotspot-Turn-on-the-Wreturn-type-warning.patch \
"
HOTSPOT_UB_PATCH_prepend_aarch64 = "\
    file://0012-hotspot-aarch64-fix-undefined-behaviour-gcc-v8-fix.patch \
    file://0013-hotspot-aarch64-Fix-further-functions-with-a-missing.patch \
"
HOTSPOT_UB_PATCH_append_armv7a = " file://0001-hotspot-aarch32-fix-missing-return-values.patch"
HOTSPOT_UB_PATCH_append_armv7ve = " file://0001-hotspot-aarch32-fix-missing-return-values.patch"
# some patches extracted from http://cr.openjdk.java.net/~rkennke/shark-build-hotspot/webrev.01/hotspot.patch
# reported via http://mail.openjdk.java.net/pipermail/build-dev/2015-January/013972.html
# by Roman Kennke (rkennke at redhat.com)
LIBPNG_NEON_PATCH = "file://openjdk8-fix-libpng-neon-build.patch;striplevel=0"
LIBPNG_NEON_PATCH_aarch64 = ""

PATCHES_URI_append_class-target = "\
    file://openjdk8-restrict-to-staging-dir.patch;striplevel=0 \
    file://openjdk8-fix-shark-build-common.patch;striplevel=0 \
    ${FIX_SHARK_BUILD_PT2_PATCH} \
    file://openjdk8-fix-shark-stdc++11.patch;striplevel=0 \
    file://openjdk8-fix-assembler-flag-handling-in-makefile.patch;striplevel=0 \
    file://openjdk8-fix-adlc-flags.patch;striplevel=0 \
    file://openjdk8-add-missing-linker-flags.patch;striplevel=0 \
"
FIX_SHARK_BUILD_PT2_PATCH = "file://openjdk8-fix-shark-build-pt2.patch;striplevel=0"
FIX_SHARK_BUILD_PT2_PATCH_armv7a = "file://openjdk8-fix-shark-build-pt2-aarch32.patch;striplevel=0"
FIX_SHARK_BUILD_PT2_PATCH_armv7ve = "file://openjdk8-fix-shark-build-pt2-aarch32.patch;striplevel=0"

PATCHES_URI_append_libc-musl = "\
    ${OBSOLETE_ISNANF_PATCH} \
    file://musl-0002-jdk-give-a-much-bigger-buffer-to-getmntent_r.patch \
    file://musl-0003-jdk-fix-libjvm-load-on-musl-set-LD_LIBRARY_PATH.patch \
    file://musl-0004-jdk-remove-sysctl.h-include-musl-build-fix.patch \
    file://musl-0005-hotspot-disable-agent-build-common.patch \
    ${DISABLE_AGENT_BUILD_PT2} \
    file://musl-0006-hotspot-os_linux-remove-glibc-dependencies-common.patch \
    ${REMOVE_GLIBC_DEPENDENCIES_PT2} \
    file://musl-0007-hotspot-os_linux_x86-remove-glibc-dependencies-fpu_c.patch \
    file://musl-0008-jdk-musl-build-fix-use-SIGRTMAX-rather-than-__SIGRTM.patch \
    file://musl-0009-jdk-musl-has-gethostby_r.patch \
"
OBSOLETE_ISNANF_PATCH = "file://musl-0001-hotspot-stop-using-obsolete-isnanf.patch"
OBSOLETE_ISNANF_PATCH_armv7a = ""
OBSOLETE_ISNANF_PATCH_armv7ve = ""
DISABLE_AGENT_BUILD_PT2 = "file://musl-0005-hotspot-disable-agent-build-pt2.patch"
DISABLE_AGENT_BUILD_PT2_armv7a = "file://musl-0005-hotspot-disable-agent-build-pt2-aarch32.patch"
DISABLE_AGENT_BUILD_PT2_armv7ve = "file://musl-0005-hotspot-disable-agent-build-pt2-aarch32.patch"
REMOVE_GLIBC_DEPENDENCIES_PT2 = "file://musl-0006-hotspot-os_linux-remove-glibc-dependencies-pt2.patch"
REMOVE_GLIBC_DEPENDENCIES_PT2_armv7a = "file://musl-0006-hotspot-os_linux-remove-glibc-dependencies-pt2-aarch.patch"
REMOVE_GLIBC_DEPENDENCIES_PT2_armv7ve = "file://musl-0006-hotspot-os_linux-remove-glibc-dependencies-pt2-aarch.patch"

PATCHES_URI_append_libc-musl_armv7a = " file://hotspot-remaining-musl-fixes-aarch32.patch"
PATCHES_URI_append_libc-musl_armv7ve = " file://hotspot-remaining-musl-fixes-aarch32.patch"
PATCHES_URI_append_libc-musl_aarch64 = " file://hotspot-remaining-musl-fixes-aarch64.patch"

# Name of the directory containing the compiled output
BUILD_DIR = "openjdk.build"
BUILD_DIR_ECJ = "openjdk.build-ecj"

# Force arm mode for now
ARM_INSTRUCTION_SET_armv4t = "ARM"

# readdir_r was deprecated in glibc-2.24. Ignore the error for now
# NOTE: When updating the recipe, please check if this is still needed
BUILD_CFLAGS_append = " -Wno-error=deprecated-declarations"
TARGET_CFLAGS_append = " -Wno-error=deprecated-declarations"

# Enable zero mode for arm based builds, as normal hotspot fails to build
PACKAGECONFIG_append_armv4 = " zero"
PACKAGECONFIG_append_armv5 = " zero"
PACKAGECONFIG_append_armv6 = " zero"

OPENJDK_ARCH_PORT = "jdk8u"
OPENJDK_ARCH_PORT_aarch64 = "aarch64-port"
OPENJDK_ARCH_PORT_armv7a = "aarch32-port"
OPENJDK_ARCH_PORT_armv7ve = "aarch32-port"
OPENJDK_HG_U = "jdk8u"
OPENJDK_HG_URL = "http://hg.openjdk.java.net/${OPENJDK_ARCH_PORT}/${OPENJDK_HG_U}"

OPENJDK_FILE = "${OPENJDK_CHANGESET}.tar.bz2"
OPENJDK_FILE_LOCAL = "openjdk8-${PV}-jdk8u-${OPENJDK_FILE}"
OPENJDK_URI = "${OPENJDK_HG_URL}/archive/${OPENJDK_FILE};downloadfilename=${OPENJDK_FILE_LOCAL};name=openjdk"

HOTSPOT_FILE = "${HOTSPOT_CHANGESET}.tar.bz2"
HOTSPOT_FILE_LOCAL = "openjdk8-${PV}-hotspot-${HOTSPOT_FILE}"
HOTSPOT_URI = "${OPENJDK_HG_URL}/hotspot/archive/${HOTSPOT_FILE};downloadfilename=${HOTSPOT_FILE_LOCAL};name=hotspot;unpack=false"

CORBA_FILE = "${CORBA_CHANGESET}.tar.bz2"
CORBA_FILE_LOCAL = "openjdk8-${PV}-corba-${CORBA_FILE}"
CORBA_URI = "${OPENJDK_HG_URL}/corba/archive/${CORBA_FILE};downloadfilename=${CORBA_FILE_LOCAL};name=corba;unpack=false"

JAXP_FILE = "${JAXP_CHANGESET}.tar.bz2"
JAXP_FILE_LOCAL = "openjdk8-${PV}-jaxp-${JAXP_FILE}"
JAXP_URI = "${OPENJDK_HG_URL}/jaxp/archive/${JAXP_FILE};downloadfilename=${JAXP_FILE_LOCAL};name=jaxp;unpack=false"

JAXWS_FILE = "${JAXWS_CHANGESET}.tar.bz2"
JAXWS_FILE_LOCAL = "openjdk8-${PV}-jaxws-${JAXWS_FILE}"
JAXWS_URI = "${OPENJDK_HG_URL}/jaxws/archive/${JAXWS_FILE};downloadfilename=${JAXWS_FILE_LOCAL};name=jaxws;unpack=false"

JDK_FILE = "${JDK_CHANGESET}.tar.bz2"
JDK_FILE_LOCAL = "openjdk8-${PV}-jdk-${JDK_FILE}"
JDK_URI = "${OPENJDK_HG_URL}/jdk/archive/${JDK_FILE};downloadfilename=${JDK_FILE_LOCAL};name=jdk;unpack=false"

LANGTOOLS_FILE = "${LANGTOOLS_CHANGESET}.tar.bz2"
LANGTOOLS_FILE_LOCAL = "openjdk8-${PV}-langtools-${LANGTOOLS_FILE}"
LANGTOOLS_URI = "${OPENJDK_HG_URL}/langtools/archive/${LANGTOOLS_FILE};downloadfilename=${LANGTOOLS_FILE_LOCAL};name=langtools;unpack=false"

NASHORN_FILE = "${NASHORN_CHANGESET}.tar.bz2"
NASHORN_FILE_LOCAL = "openjdk8-${PV}-nashorn-${NASHORN_FILE}"
NASHORN_URI = "${OPENJDK_HG_URL}/nashorn/archive/${NASHORN_FILE};downloadfilename=${NASHORN_FILE_LOCAL};name=nashorn;unpack=false"
