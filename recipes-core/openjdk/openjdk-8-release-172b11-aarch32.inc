require openjdk-8-release-172b11-common.inc

COMPATIBLE_HOST = "^$"
COMPATIBLE_HOST_armv7a = "arm"
COMPATIBLE_HOST_armv7ve = "arm"

CORBA_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[corba.md5sum] = "557b94847d8fade14c048cb0a96ed035"
SRC_URI[corba.sha256sum] = "366fa9aaf11d75f74e8c6bdf9cab9214cf66b0eac1ca40f2789b3ba442929708"

HOTSPOT_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[hotspot.md5sum] = "37d796794234f38fa71339ba78368b80"
SRC_URI[hotspot.sha256sum] = "5f89f8ba9a099a2d84b4ca6bd49553ce4efe1b29d55de9134809b7b59b6c9ce3"

JAXP_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[jaxp.md5sum] = "2dc311a7c0d6483226cdc5e501b1f8d0"
SRC_URI[jaxp.sha256sum] = "f62db09a41213b5b5d1886c1aeabe43def09235de1d60af518213b9acea4fdca"

JAXWS_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[jaxws.md5sum] = "fbd81e288d1ee5df631f213c130f21bb"
SRC_URI[jaxws.sha256sum] = "bac66e848ee48c6fef6130db4bb6879dbd64c550c1f42e4676ab6a2c3ee4fab8"

JDK_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[jdk.md5sum] = "b8003e6f1714617461f3eb7ee8b1efee"
SRC_URI[jdk.sha256sum] = "0a7eef6fef2b457bef3bd1d24031234bbb9d74a5fca2f65e1603278cd9d393a0"

LANGTOOLS_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[langtools.md5sum] = "e38f50b0113b3a956ac4917720655e93"
SRC_URI[langtools.sha256sum] = "9ca88fcfe5a07861de693ff3b38d03f063a7937576cd93116ea6b4a4bd7894d5"

NASHORN_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[nashorn.md5sum] = "c191cc92996fcb271254fc0a4f3eb7c9"
SRC_URI[nashorn.sha256sum] = "853bb3162fefa989fa0c31848cb990d8e5698ccd8a2a336dbf98bde35eb5241d"

OPENJDK_CHANGESET_arm = "jdk8u172-b11-aarch32-180511"
SRC_URI[openjdk.md5sum] = "25398ccf25633a878dca54a8d606e48e"
SRC_URI[openjdk.sha256sum] = "8c8e515ebcceded4b90187b4bdaf129b63ae6e64ddfe4f05a60df0694235b9e7"

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
