require openjdk-8-release-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

CORBA_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[corba.sha256sum] = "a3adf57f7d50155bb83926afc2ca0007c6f17602660bacaff67201dd886b379f"

HOTSPOT_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[hotspot.sha256sum] = "b4f6ab5466fc73f6e015d5394b4204453a109dc532e8bbac069c46c109545ce6"

JAXP_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxp.sha256sum] = "d8e6a5bf406bf32f7806081907bd299098f13ade00260a737d3c141bcc2890a9"

JAXWS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jaxws.sha256sum] = "436a0aaecda8f2cc66ef2cbccea34a85887e5646fff60036473c08f975a68e33"

JDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[jdk.sha256sum] = "f9ca5bcda71f91d087d7483c1ae53d266a92f9691836f1cbbfaa37a9993f1f9b"

LANGTOOLS_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[langtools.sha256sum] = "ea33875d91addd8f6dd52afe5cfa11c108f0e378df8451ed22a4e6767576c899"

NASHORN_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[nashorn.sha256sum] = "660148fab294a98147d346209e19b6dcf82807588d3c8c54abfc1262c95043d4"

OPENJDK_CHANGESET = "jdk8u${PV}-ga"
SRC_URI[openjdk.sha256sum] = "b5fd22b2f4a0a59611373e5f1ffc423d26e62ea38f1084a80a401beb6bd04d88"
