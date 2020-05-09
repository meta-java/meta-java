SUMMARY = "Java runtime based upon the OpenJDK Project"
HOMEPAGE = "http://openjdk.java.net/"
LICENSE  = "GPL-2.0-with-classpath-exception"

LIC_FILES_CHKSUM = "file://LICENSE;md5=3e0b59f8fac05c3c03d4a26bbda13f8f"

require openjdk-common.inc

AUTOTOOLS_SCRIPT_PATH = "${S}/common/autoconf/"
export AUTOCONF_DIR="${AUTOTOOLS_SCRIPT_PATH}"
FILESPATH =. "${FILE_DIRNAME}/patches-openjdk-8:"

# for weird openjdk-common.inc
S = "${WORKDIR}/${OPENJDK_HG_U}-${OPENJDK_CHANGESET}"

SRC_URI = "\
    ${OPENJDK_URI} \
    ${HOTSPOT_URI} \
    ${CORBA_URI} \
    ${JAXP_URI} \
    ${JAXWS_URI} \
    ${JDK_URI} \
    ${LANGTOOLS_URI} \
    ${NASHORN_URI} \
    file://LICENSE \
    ${PATCHES_URI} \
"

do_configure_prepend () {
    export TOPDIR=${S}
}

do_unpack_extract_submodules () {
    cd "${S}"
    # tar --transform
    tar xjf ${WORKDIR}/${CORBA_FILE_LOCAL} --transform "s,-${CORBA_CHANGESET},,g"
    tar xjf ${WORKDIR}/${HOTSPOT_FILE_LOCAL} --transform "s,-${HOTSPOT_CHANGESET},,g"
    tar xjf ${WORKDIR}/${JAXP_FILE_LOCAL} --transform "s,-${JAXP_CHANGESET},,g"
    tar xjf ${WORKDIR}/${JAXWS_FILE_LOCAL} --transform "s,-${JAXWS_CHANGESET},,g"
    tar xjf ${WORKDIR}/${JDK_FILE_LOCAL} --transform "s,-${JDK_CHANGESET},,g"
    tar xjf ${WORKDIR}/${LANGTOOLS_FILE_LOCAL} --transform "s,-${LANGTOOLS_CHANGESET},,g"
    tar xjf ${WORKDIR}/${NASHORN_FILE_LOCAL} --transform "s,-${NASHORN_CHANGESET},,g"
}

do_patch_prepend() {
    # use do_patch_prepend syntax and not pre/postfuncs to
    # call do_unpack_extract_submodules
    # *) the archiver.bbclass modifies WORKDIR, S, B,...
    #    and those modifications are lost otherwise,
    #    which leads to build failures in do_unpack_and_patch -> do_patch
    func = 'do_unpack_extract_submodules'
    bb.build.exec_func(func, d)

    # delete X11 wrappers if x11 is not part of PACKAGECONFIG
    if bb.utils.contains('PACKAGECONFIG', 'x11', False, True, d):
       func_delete = 'do_unpack_delete_X11_wrappers'
       bb.build.exec_func(func_delete, d)
}

do_unpack_delete_X11_wrappers() {
    find ${S}/jdk/src/solaris/classes/sun/awt/X11 -maxdepth 1 -name '*.java' -delete
}

def package_config_option_cleanup(d):
    distro_x11 = bb.utils.contains('DISTRO_FEATURES', 'x11', True, False, d)
    distro_alsa = bb.utils.contains('DISTRO_FEATURES', 'alsa', True, False, d)
    distro_pulseaudio = bb.utils.contains('DISTRO_FEATURES', 'pulseaudio', True, False, d)

    with_x11 = bb.utils.contains('PACKAGECONFIG', 'x11', True, False, d)
    with_cups = bb.utils.contains('PACKAGECONFIG', 'cups', True, False, d)
    with_alsa = bb.utils.contains('PACKAGECONFIG', 'alsa', True, False, d)
    with_pulseaudio = bb.utils.contains('PACKAGECONFIG', 'pulseaudio', True, False, d)

    option_headless = bb.utils.contains('PACKAGECONFIG', 'headless', True, False, d)
    option_headful = bb.utils.contains('PACKAGECONFIG', 'headful', True, False, d)
    option_soundless = bb.utils.contains('PACKAGECONFIG', 'soundless', True, False, d)

    if option_headless and option_headful:
        option_headless = False

    if option_headful and not with_x11:
        with_x11 = True

    if option_headful and not with_cups:
        with_cups = True

    if option_soundless and with_alsa:
        with_alsa = False

    if option_soundless and with_pulseaudio:
        with_pulseaudio = False

    if with_x11 and not distro_x11:
        with_x11 = False

    if with_alsa and not distro_alsa:
        with_alsa = False

    if with_pulseaudio and not distro_pulseaudio:
        with_pulseaudio = False

    if option_headful and not with_x11:
        option_headful = False

    if option_headful and not with_cups:
        option_headful = False

    if not option_headless and not with_x11:
        option_headless = True

    if not option_headless and not with_cups:
        option_headless = True

    if not option_soundless and not with_alsa:
        option_soundless = True

    if not option_soundless and not with_pulseaudio:
        option_soundless = True

    options = {'make': [], 'cpp': [], 'env': [], 'configure': ["--disable-ccache"] }

    if option_headful:
        options['configure'].append("--enable-headful")

    if option_headless:
        options['configure'].append("--disable-headful")
        options['make'].append("BUILD_HEADLESS_ONLY=1")
        options['make'].append("BUILD_HEADLESS=true")
        options['cpp'].append("-DHEADLESS=true")

    if option_soundless:
        options['make'].append("BUILD_SOUNDLESS_ONLY=1")

    if not with_x11:
        options['make'].append("X11_NOT_NEEDED=1")
        options['env'].append("X11_NOT_NEEDED=yes")

    if not with_cups:
        options['make'].append("CUPS_NOT_NEEDED=1")
        options['env'].append("CUPS_NOT_NEEDED=yes")

    if not with_alsa:
        options['make'].append("ALSA_NOT_NEEDED=1")
        options['env'].append("ALSA_NOT_NEEDED=yes")

    if not with_pulseaudio:
        options['make'].append("PULSE_NOT_NEEDED=1")
        options['env'].append("PULSE_NOT_NEEDED=yes")

    options = [ ' '.join(options['make']), ' '.join(options['cpp']), ' '.join(options['env']), ' '.join(options['configure']) ]

    return options

def jdk_make_options(d):
    options = package_config_option_cleanup(d)
    return options[0]

def jdk_cpp_options(d):
    options = package_config_option_cleanup(d)
    if not options[1]:
        return ""

    return " " + options[1]

def jdk_environment_options(d):
    options = package_config_option_cleanup(d)
    return options[2]

def jdk_configure_options(d):
    options = package_config_option_cleanup(d)
    return options[3]

#do_unpack[postfuncs] += "do_unpack_extract_submodules"
#do_unpack[postfuncs] += "${@bb.utils.contains('PACKAGECONFIG', 'x11', '', 'do_unpack_delete_X11_wrappers', d)}"

export DEBUG_BINARIES = "true"

ALTERNATIVE_PRIORITY = "50"

OPENJDK_UPDATE_VERSION = "${PV}"
OPENJDK_BUILD_NUMBER = "ga"
EXTRA_OECONF_append = "\
        --with-build-number=${OPENJDK_BUILD_NUMBER} \
        --with-update-version=${OPENJDK_UPDATE_VERSION} \
"

# Since v6, GCC sets the default C++ standard to C++14 and introduces
# dead store elimination by default.
# Since v10, GCC defaults to -fno-common.
# OpenJDK 8 is not ready for either of these changes.
GLOBAL_FLAGS = "-fno-lifetime-dse -fno-delete-null-pointer-checks -fcommon"

# flags for -native, and for bits that need a host-tool during -cross
BUILD_CFLAGS_append = " ${GLOBAL_FLAGS}"
BUILD_CXXFLAGS_append = " ${GLOBAL_FLAGS}"
# flags for -cross
TARGET_CFLAGS_append = " ${GLOBAL_FLAGS}"
TARGET_CXXFLAGS_append = " ${GLOBAL_FLAGS}"
