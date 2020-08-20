require openjdk-8-release-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

CHANGESET_ID="20200729"

CORBA_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "ade9cc2019f274efa8192a10b5ff5ca689671862c93b167f64fbac0673b1ee14"

HOTSPOT_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "2ce8c243c25f1607273fab7261203485926144b240a9a2f3298e7eaaad502f35"

JAXP_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "d318addf2fbab69c588c61bf86b128d491271c9c27bebbb69cab6bfbf0967990"

JAXWS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "452bd7be71bc7da65554da97c35470fb3c2f18228cbbf2ae01dd7ccdfeb55394"

JDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "b7068f3d21b060b4ffd9951eb07d9e24e6415d5ad49d1cc20c897f7d88349212"

LANGTOOLS_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "9ff01c83c40acedfb87ce566d88d135a5c92f5cc7ca110d5f5895305346f7968"

NASHORN_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "a752ebdeea4382f0d0c005861eea59c8b90a3488497974c2abc8915d4673cd0f"

OPENJDK_CHANGESET_arm = "jdk8u${PV}-ga-aarch32-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "f42a7536ea7c76711e5b7caa0f42c8797145e68f0881f8fa9b8517ff48d0d747"

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
