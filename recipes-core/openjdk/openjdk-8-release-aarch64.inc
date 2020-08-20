require openjdk-8-release-common.inc

COMPATIBLE_HOST = "aarch64"

CHANGESET_ID="b01"

CORBA_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "43636545f3a4ad08e11728d20472d0bc8bb05b4833f9ab2bdcd0d195f8b6f96c"

HOTSPOT_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "4ddf5e0e2e7840211849bf13ffafeda69696c1477ae1720c802e3182d87798fd"

JAXP_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "215920996bffd3cf7ebfd14f767b3f302503cddf82c1c0a63759764426c03938"

JAXWS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "96d8c429e4286184e008b6ee20942f6abaf01c014bc384a441552f7eb521ec5f"

JDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "f0b882d16ef766ebce0e0106e54034a14ef5cd15dae2aff4695c199f6a84bce1"

LANGTOOLS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "a115bd03600093658dc9da549122e553fd6ce6cb7f317fb4461e15efad8ab140"

NASHORN_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "43ba2d8b825cf521e6ffb429f8578afc9ca7d90d6daf9bd2b22d598fb532d871"

OPENJDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "dd46927e9821a69083feaff2161cce19d2cbbc2549be6c28da996ddba52b0d11"
