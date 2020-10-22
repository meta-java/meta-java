require openjdk-8-release-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

CHANGESET_ID="b09-aarch32-20200929"

CORBA_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "3675f043479c7e3ee7128651527d15c4e56f72d22dd953b8d0d8e5c9a2c68741"

HOTSPOT_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "d5ea125d7e54fd3dd21bf1654c09b5ce17497d9327f770abd56ad1108a337b81"

JAXP_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "a025f9f047bc50947aa631641b2f836c3a3ec4a5f2c9019bc7b11ab8444f7b9e"

JAXWS_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "ad921e0f5cafab4c5b4bb248ea59bf1615864c4de17bfd7321759d063398dc3f"

JDK_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "835e81fc88b8c0e40df0d89be5d8a852638b3f5f29acad6997cbc36a2e8341fe"

LANGTOOLS_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "554491026bb9fadb837d635d4beea3ca9cb73f034c1379d57fcd77787816139f"

NASHORN_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "8358000a7e52fcfd046027319569d17f2e99b710acbfd1a1120b50ce93afe223"

OPENJDK_CHANGESET_arm = "jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "4b38e672c82df5d18215849829a80a111b1c7b46567bc641e9fec92bedd0d32a"

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
