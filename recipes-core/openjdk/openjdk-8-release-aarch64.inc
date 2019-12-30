require openjdk-8-release-common.inc

COMPATIBLE_HOST = "aarch64"

CHANGESET_ID="b07"

CORBA_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[corba.md5sum]    = "d6dfd6f0c3bf4c6dc1f867dc7bcf8730"
SRC_URI[corba.sha256sum] = "e80dae94f21ca9de2269bc9de72f1098d417e9f7d6ff69d047e26669e31b1bc4"

HOTSPOT_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[hotspot.md5sum]    = "44731f82f6e2a0697f414ae62f9eff54"
SRC_URI[hotspot.sha256sum] = "3acb0bfa3eda0137e3c70ab10b59f139e0720116ed6ecf3f9c8633ebc36947b1"

JAXP_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxp.md5sum]    = "7fb4207ba9277e109439101961223fc7"
SRC_URI[jaxp.sha256sum] = "22616e56825c611c70968c34a229661d4cb910fdb0c3936ae3c75de2330abfb5"

JAXWS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxws.md5sum]    = "a27379cbd6253408eee4aa0b8a551042"
SRC_URI[jaxws.sha256sum] = "b6eb69d867694002284712a28058770170d885e6de6872cba260061d001b77ae"

JDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jdk.md5sum]    = "2e64397ef1f35309aa7de00d46c2c751"
SRC_URI[jdk.sha256sum] = "d470d24eddc314e5c30035881f3af6f0c48a3360accc0644ec26d9d32d9ea0e6"

LANGTOOLS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[langtools.md5sum]    = "71c2ce819538b0acc443c0519dfa43c1"
SRC_URI[langtools.sha256sum] = "219919b7980d863cc26abd87341012f4802dd12a11a45f6627309ec365a9e838"

NASHORN_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[nashorn.md5sum]    = "6ee9418598ca411fe0b2339fa1a3a272"
SRC_URI[nashorn.sha256sum] = "6d86c23301d2cbc1ea72474730336e089eb4c3d3014bdf0f3a9d3b5976a75f58"

OPENJDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[openjdk.md5sum]    = "188b5d7ef0976cfc1a4258d1dc8ccce0"
SRC_URI[openjdk.sha256sum] = "7c32399a85f56bda2c740fc6834b8b5d648e75271a5376c2fa968bd713e3fec8"
