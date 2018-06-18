DESCRIPTION = "An image for OpenJRE testing purposes"

IMAGE_FEATURES += "ssh-server-openssh package-management"

IMAGE_INSTALL = "${CORE_IMAGE_BASE_INSTALL}"

DEFAULT_TEST_SUITES_pn-${PN} = "ping ssh java"

inherit core-image
