require openjdk-8-release-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

CORBA_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[corba.sha256sum] = "97513397015ca62953c6afa3ba925b1dabc0238d47f3a2b81c2bd5b683d4d050"

HOTSPOT_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[hotspot.sha256sum] = "80a91f421bbe750f5e8c66b74f77fb79f31cce2f6e9e1cfe8407d773bb1ed57d"

JAXP_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxp.sha256sum] = "ead123b56c1c5d4c381665da6c0858cd9b11c69b8afc7494f9831980bc71bc92"

JAXWS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxws.sha256sum] = "ef6532ac77e7e4333283c09c87b6923fbaa91b8bca6770f06494c3bb1643455e"

JDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jdk.sha256sum] = "7203ded24a10843ac8e84269ad8ac347f29b1dd950f7e0bb9739ddcb8280b8fb"

LANGTOOLS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[langtools.sha256sum] = "6e2329e3f15c0fd23da47cd8f454cb49cdae0b12c951eb2910061fa95acb8ea4"

NASHORN_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[nashorn.sha256sum] = "195237fd89f34c27bf98c3a8bfda64bbc799a014e83907062a8b4e10bd4f2021"

OPENJDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[openjdk.sha256sum] = "a83f8daa2afece63bf7ae95cfbca91ef765424c40b9f5b45e4a3c2d4da0f7a95"
