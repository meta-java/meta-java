require openjdk-8-release-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST:armv7a = "^$"
COMPATIBLE_HOST:armv7ve = "^$"

CORBA_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[corba.sha256sum] = "28c487a49546ab1a592eaf229c13e1896b390958ac4e6fa19bf5da34a1977138"

HOTSPOT_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[hotspot.sha256sum] = "55db6eb423445978e5a9a285c5adea238dec3d3998dc5f1216f8f5c7a8d7c5ea"

JAXP_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxp.sha256sum] = "778d3946b9cf84c9b7fd937dc91d0e919ba7616cc4e3db44b9d0347ecdad308a"

JAXWS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxws.sha256sum] = "a46eabbed4fedcdbd26510fc1ccf40aaa337e44542f112d4dba3e93f2bb7e492"

JDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jdk.sha256sum] = "9913adf85d3c5b039a5dfeb0962613d92c6f454d0bbbbe3e5341e221021e908e"

LANGTOOLS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[langtools.sha256sum] = "9189920ae3858c9a680912c54504302e0553cf25d892c8a03fe954859f587066"

NASHORN_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[nashorn.sha256sum] = "b42bed287349ecc702f874867a60c3e3664a799d69004e46260db5ff9a7df772"

OPENJDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[openjdk.sha256sum] = "3b335df278915237986ccdfc40e262d5b6a711072b2a0b99bf2b197dc9ff0cff"
