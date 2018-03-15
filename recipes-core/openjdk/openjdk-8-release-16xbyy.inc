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
"
# some patches extracted from http://cr.openjdk.java.net/~rkennke/shark-build-hotspot/webrev.01/hotspot.patch
# reported via http://mail.openjdk.java.net/pipermail/build-dev/2015-January/013972.html
# by Roman Kennke (rkennke at redhat.com)
LIBPNG_NEON_PATCH = "file://openjdk8-fix-libpng-neon-build.patch;striplevel=0"
LIBPNG_NEON_PATCH_aarch64 = ""
PATCHES_URI_append_class-target = "\
    file://openjdk8-restrict-to-staging-dir.patch;striplevel=0 \
    file://openjdk8-fix-shark-build.patch;striplevel=0 \
    file://openjdk8-fix-shark-stdc++11.patch;striplevel=0 \
    file://openjdk8-fix-assembler-flag-handling-in-makefile.patch;striplevel=0 \
    file://openjdk8-fix-adlc-flags.patch;striplevel=0 \
    file://openjdk8-add-missing-linker-flags.patch;striplevel=0 \
    ${LIBPNG_NEON_PATCH} \
"
PATCHES_URI_append_libc-musl = "\
    file://musl-0001-hotspot-stop-using-obsolete-isnanf.patch \
    file://musl-0002-jdk-give-a-much-bigger-buffer-to-getmntent_r.patch \
    file://musl-0003-jdk-fix-libjvm-load-on-musl-set-LD_LIBRARY_PATH.patch \
    file://musl-0004-jdk-remove-sysctl.h-include-musl-build-fix.patch \
    file://musl-0005-hotspot-disable-agent-build.patch \
    file://musl-0006-hotspot-os_linux-remove-glibc-dependencies.patch \
    file://musl-0007-hotspot-os_linux_x86-remove-glibc-dependencies-fpu_c.patch \
    file://musl-0008-jdk-musl-build-fix-use-SIGRTMAX-rather-than-__SIGRTM.patch \
    file://musl-0009-jdk-musl-has-gethostby_r.patch \
"
PATCHES_URI_append_libc-musl_aarch64 = " file://hotspot-remaining-musl-fixes-aarch64.patch"

# Name of the directory containing the compiled output
BUILD_DIR = "openjdk.build"
BUILD_DIR_ECJ = "openjdk.build-ecj"

# Force arm mode for now
ARM_INSTRUCTION_SET_armv4t = "ARM"

# readdir_r was deprecated in glibc-2.24. Ignore the error for now
# NOTE: When updating the recipe, please check if this is still needed
CFLAGS_append = " -Wno-error=deprecated-declarations"

# Enable zero mode for arm based builds, as normal hotspot fails to build
PACKAGECONFIG_append_arm = " zero"

OPENJDK_ARCH_PORT = "jdk8u"
OPENJDK_ARCH_PORT_aarch64 = "aarch64-port"
OPENJDK_HG_U = "jdk8u"
OPENJDK_HG_URL = "http://hg.openjdk.java.net/${OPENJDK_ARCH_PORT}/${OPENJDK_HG_U}"

OPENJDK_FILE = "${OPENJDK_CHANGESET}.tar.bz2"
OPENJDK_URI = "${OPENJDK_HG_URL}/archive/${OPENJDK_FILE};name=openjdk"

HOTSPOT_FILE = "${HOTSPOT_CHANGESET}.tar.bz2"
HOTSPOT_URI = "${OPENJDK_HG_URL}/hotspot/archive/${HOTSPOT_FILE};name=hotspot;unpack=false"

CORBA_FILE = "${CORBA_CHANGESET}.tar.bz2"
CORBA_URI = "${OPENJDK_HG_URL}/corba/archive/${CORBA_FILE};name=corba;unpack=false"

JAXP_FILE = "${JAXP_CHANGESET}.tar.bz2"
JAXP_URI = "${OPENJDK_HG_URL}/jaxp/archive/${JAXP_FILE};name=jaxp;unpack=false"

JAXWS_FILE = "${JAXWS_CHANGESET}.tar.bz2"
JAXWS_URI = "${OPENJDK_HG_URL}/jaxws/archive/${JAXWS_FILE};name=jaxws;unpack=false"

JDK_FILE = "${JDK_CHANGESET}.tar.bz2"
JDK_URI = "${OPENJDK_HG_URL}/jdk/archive/${JDK_FILE};name=jdk;unpack=false"

LANGTOOLS_FILE = "${LANGTOOLS_CHANGESET}.tar.bz2"
LANGTOOLS_URI = "${OPENJDK_HG_URL}/langtools/archive/${LANGTOOLS_FILE};name=langtools;unpack=false"

NASHORN_FILE = "${NASHORN_CHANGESET}.tar.bz2"
NASHORN_URI = "${OPENJDK_HG_URL}/nashorn/archive/${NASHORN_FILE};name=nashorn;unpack=false"
