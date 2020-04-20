require openjdk-8-release-common.inc

COMPATIBLE_HOST = "aarch64"

CHANGESET_ID="b09"

CORBA_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[corba.sha256sum] = "13ce2345dec4390a7ed61066275528c1d4fe246abb3ffc16bdfd93c0e8ead193"

HOTSPOT_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[hotspot.sha256sum] = "80dd8b1289905252f5f9d97ba2302fe4b77a76851709f10d429848750b709c66"

JAXP_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxp.sha256sum] = "a52f5497318980f379ce05ff8e638a0ae0ce7265d8922ddfb731d26989faf161"

JAXWS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jaxws.sha256sum] = "1db8876408222a8eec8432bd9778559ea80cae36a2c6dead32723279d1622741"

JDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[jdk.sha256sum] = "abc7a1eec87ac330bebfa8ec4a3db72c27b63aa50175abfade580a46b7f2d865"

LANGTOOLS_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[langtools.sha256sum] = "c4e3dd471372dad5a545ec038104c7706fa02da452275ce118ad7e38e418a57a"

NASHORN_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[nashorn.sha256sum] = "956ef3a52dc97fb28aeeeb9ccbd371c2b7f14e253fd63d1f98bb1bf87ddf1929"

OPENJDK_CHANGESET_aarch64 = "aarch64-shenandoah-jdk8u${PV}-${CHANGESET_ID}"
SRC_URI[openjdk.sha256sum] = "b7b933ff2b8c0ee17eb6dbd02beb8769e7dfe15c50ab2fdeef55666e4b12cbe7"
