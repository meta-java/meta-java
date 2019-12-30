require openjdk-8-release-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

CHANGESET_ID="200120"

CORBA_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[corba.md5sum]    = "2abf6d5394d9c5310af1e4ca6cec4355"
SRC_URI[corba.sha256sum] = "52e83dfa2fa4fcc8c71f3b2959cca2136099b9c575d3726148c02b9cf7d06324"

HOTSPOT_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[hotspot.md5sum]    = "e252af6c20d6190e0613f39c6066e3cc"
SRC_URI[hotspot.sha256sum] = "bfff2ef23ee80acd73a0774e7011028c3598e75d2ee8b3271524ec8ea54801ae"

JAXP_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxp.md5sum]    = "56dc7a99589582b18bbbb5c4464022c8"
SRC_URI[jaxp.sha256sum] = "430e49ba485737c02312557f4deb8562853e58be19ed175ea63b396307f140ce"

JAXWS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxws.md5sum]    = "2bbcba759f24f5dcec0c33cd62382e4f"
SRC_URI[jaxws.sha256sum] = "c350716ff8782cc311ca17450e2d198d707d3fb71de9dc3394df39766979559f"

JDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jdk.md5sum]    = "e17f3f4ea8a409e4a1b09a12b3b5309d"
SRC_URI[jdk.sha256sum] = "dfa4a7e7f8ab8daf34343b1c33544b6209e422c74d5be1dbbd8ef80e2365c8aa"

LANGTOOLS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[langtools.md5sum]    = "06ca78c1d4e058f277876f4e6177d9b0"
SRC_URI[langtools.sha256sum] = "59ccafa433f5510c91835efcafbe9ff9c707034ec3305dc3a4c1a85fac65ab0c"

NASHORN_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[nashorn.md5sum]    = "1958e204f3984abeb2cf9e7c57aa7839"
SRC_URI[nashorn.sha256sum] = "e964721e539807a38bdcbce7259d235f873974a686badbc274b7368a288f0021"

OPENJDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[openjdk.md5sum]    = "9aceb3b4cd710cdda55be4fe6a5303c9"
SRC_URI[openjdk.sha256sum] = "9691291b26a650d854ce0feacf32dfb3b956165c5d2db6e1ff46dd44f4c517cf"

PACKAGECONFIG_append_armv7a = " client"
PACKAGECONFIG_append_armv7ve = " client"

do_install_append() {
    if [ -d ${D}${JDK_HOME} ] ; then
        sed -e 's,^\(-server ERROR$\),# \1,' \
            -e 's,^-client IGNORE,-client ERROR,' \
            -e 's,ALIASED_TO -server,ALIASED_TO -client,' \
            -i ${D}${JDK_HOME}/jre/lib/${JDK_ARCH}/jvm.cfg
    fi
    if [ -d ${D}${JRE_HOME} ] ; then
        sed -e 's,^\(-server ERROR$\),# \1,' \
            -e 's,^-client IGNORE,-client ERROR,' \
            -e 's,ALIASED_TO -server,ALIASED_TO -client,' \
            -i ${D}${JRE_HOME}/lib/${JDK_ARCH}/jvm.cfg
    fi
}

JDK_ARCH_armv7a = "aarch32"
JDK_ARCH_armv7ve = "aarch32"
