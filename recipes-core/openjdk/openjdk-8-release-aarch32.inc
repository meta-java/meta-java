require openjdk-8-release-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

CHANGESET_ID="20200415"

CORBA_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "e8dab3ffbc39fec724604b8c65408f32dcca1682769077c5b4f71b571938fe26"

HOTSPOT_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "7aebf690a05746e4fbcdcd75ac4e67acb2f0b087bba3bcb064675468626f5822"

JAXP_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "44883e0e836ee5fa2fcb4df936bafcfad69c57d05876d44ecefc5b3cb6b085c0"

JAXWS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "34f6cf3eb34c0c310e0cc31b876b189fd6b2e2c2dcc1066af5347f3a0873d2d3"

JDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "f89688b5673ed75b1bebfd530a979788a4cbe942ce39eb38784f8c9e1303012b"

LANGTOOLS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "18357720e3b924dea2f171235ae06e753aeef7958a3ce7a2a8d41fa6e2c90454"

NASHORN_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "abd6ccf28278ce5775eebada339228fe2e3380d57d009179acdd7026adb21448"

OPENJDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "06d141aa01b80aa0c167167081e2139b3edf5af764cf17bbe9e1b57bf4f585ab"

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
