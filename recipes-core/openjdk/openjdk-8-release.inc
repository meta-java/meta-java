require openjdk-8-release-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

CORBA_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[corba.md5sum]    = "e269b1b01c00bec6c9f2684d7e3e6540"
SRC_URI[corba.sha256sum] = "45433c179dd5ee117b8097c75f475feb5a2d2fae052be3e582c59511696a5d0e"

HOTSPOT_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[hotspot.md5sum]    = "105c2a6bdfecc2f1fe09aac65748bf47"
SRC_URI[hotspot.sha256sum] = "08729033233b3a42bf1fa3d2a2c0cdf1c950c682cc27bd486f7c19ae28d34ef7"

JAXP_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxp.md5sum]    = "a9fb321b6c466e83b9ad23da0d9674c5"
SRC_URI[jaxp.sha256sum] = "8e52661976169fca3fe567b269be5852dff378cb2e66e9f8a4e9f40aaa8d89e4"

JAXWS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxws.md5sum]    = "6ee14ea4974b93bff075499cd820413b"
SRC_URI[jaxws.sha256sum] = "95a14275db59e0c1a8fa4ca4861b8761b1598f0ed7f3ef2f2cef7c619df1eb83"

JDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jdk.md5sum]    = "57d2bc331d9506fa652fac686c6b64c1"
SRC_URI[jdk.sha256sum] = "3ecb62288df04d05f541a26da32464c04558a951b2962290f08b149d614ae020"

LANGTOOLS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[langtools.md5sum]    = "5456b86c13a21c8e73a088af5723ba06"
SRC_URI[langtools.sha256sum] = "ffaf18753935cd03b2d581f17789172f4cfdc093d62ca764bf14068d7e30599c"

NASHORN_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[nashorn.md5sum]    = "0716fb438451ac45285a0cd8c17cc27b"
SRC_URI[nashorn.sha256sum] = "3a572a5d5c2e8b590c9ac2c65905069a991f7e168f5bbe15e7dbb924b10ab96d"

OPENJDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[openjdk.md5sum]    = "5f5cf2638bba1b4f9b4915be9973077e"
SRC_URI[openjdk.sha256sum] = "633f1d20d4d8d36fea1680140b5514ab153096a19c306b812fbbd19314c8dece"
