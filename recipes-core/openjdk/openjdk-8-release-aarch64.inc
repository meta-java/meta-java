require openjdk-8-release-common.inc

COMPATIBLE_HOST = "aarch64"

CHANGESET_ID="b10"

CORBA_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "112143d935a94cb95a0f9dba19a86184d08e699a68a82db58cdd9f0de1baeeae"

HOTSPOT_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "16ed30b46279e2ffef04ab392502e32525451bea38f3af0d3c3782bcd33a0274"

JAXP_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "5dde165d7327b08f2ebc8d3081a1734d9ef737117dcaa417eb7dc39344220987"

JAXWS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "cedde28264a85cb16ae46123091edb64f7c1d2cd5f3de6ba0d21cffff84c3ccf"

JDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "7e53438e0506536fe373b7f8176512c701b87adda268831d180ead2695154a93"

LANGTOOLS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "8dbcd45109d0c782a6cac5a1a310a5816d4dac8a9c095635832ab803bfdb861a"

NASHORN_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "85497cdba0943644d838862761891d0a06dfaad5ea13b63af69f1a6d595e6387"

OPENJDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "97175c78de4c82b78d3c80b1b0d22c44b195ca067f253cfaa3c235328b808760"
