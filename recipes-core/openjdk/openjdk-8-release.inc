require openjdk-8-release-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

CORBA_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[corba.sha256sum] = "51212e37b6c6e120901e61b830f110bbd121e9c4611aec9ff4e3f404a667855f"

HOTSPOT_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[hotspot.sha256sum] = "a8c83dcd272dc29c538291f24d1b28b7069e048398681b6db082cdaa8f3a6b07"

JAXP_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxp.sha256sum] = "3f8b02337f4cd96e9180aa118705f48c39562f66287b46dd69554221fa196084"

JAXWS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxws.sha256sum] = "ed276f9a70bf2582183838ad8b1874c0993b4a28741c69f095669667b12cd3d4"

JDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jdk.sha256sum] = "a3deeab4ac721d1ce9d8a2fb1917ba9e2afc6041f03ad4a342e9a5441cce621d"

LANGTOOLS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[langtools.sha256sum] = "ed59eabe4eb3fcf9af592d1af2d052c5053da9d868542fc47a0bddcb91e69c60"

NASHORN_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[nashorn.sha256sum] = "a5b8c478cd7695bf83210b8e97be3bfc8248c22916cec3b8b869586c3d7f0007"

OPENJDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[openjdk.sha256sum] = "a80476dfe32c12882fe2d87bdb0dd37fc4a0dae8dd95f0c22c7c2445fc08ff7e"
