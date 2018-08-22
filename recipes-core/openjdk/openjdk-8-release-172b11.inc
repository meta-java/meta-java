require openjdk-8-release-172b11-common.inc

# We do not yet work for aarch64, and we make sure
# to use the aarch32 port for ARMv7.
COMPATIBLE_HOST = "^(?!(aarch64)).*$"
COMPATIBLE_HOST_armv7a = "^$"
COMPATIBLE_HOST_armv7ve = "^$"

CORBA_CHANGESET = "875a75c440cd"
SRC_URI[corba.md5sum] = "66242dd6e749f39a5ef6add34f5ecb2f"
SRC_URI[corba.sha256sum] = "f1618be7ad88619c7d7c1eed9800c528d0646e1c9f039e20a57b3e72ae3d3512"

HOTSPOT_CHANGESET = "32ba4d2121c1"
SRC_URI[hotspot.md5sum] = "a3e1d2f91ba8873f71e9a72043e2644a"
SRC_URI[hotspot.sha256sum] = "680b1f5100786910bfceeef90ce28d74fcf6eacfdd3b92dfc76dcf3216060e99"

JAXP_CHANGESET = "30586bb50743"
SRC_URI[jaxp.md5sum] = "b413b1cb709d74e513f13c586215366d"
SRC_URI[jaxp.sha256sum] = "ba36dd8ad72ff3d8bda38b7d6773037e18c3c68ebadd61f1e1f7fc167a506baa"

JAXWS_CHANGESET = "452a6a5a878e"
SRC_URI[jaxws.md5sum] = "5c3c4d1fec19398128cf818aef5486a9"
SRC_URI[jaxws.sha256sum] = "89aa34e6bc3410a85ea697aa4ae70c21f7099efdacef78a6e5a46747421e86f9"

JDK_CHANGESET = "5ccc572f4ffe"
SRC_URI[jdk.md5sum] = "29dd4772e3862193e56007a0bb0d6886"
SRC_URI[jdk.sha256sum] = "4d1758ceec155fcd2cd786f11071ed614947a9720373d704221d78ed98beadec"

LANGTOOLS_CHANGESET = "34ee52bc68a4"
SRC_URI[langtools.md5sum] = "b195802f2aaa5c95c06cc50021bb42a6"
SRC_URI[langtools.sha256sum] = "0403bd2c9a45e4c0dc2148907028e0cdfd087be512e6d6b3763a01411936663a"

NASHORN_CHANGESET = "7efd6152328e"
SRC_URI[nashorn.md5sum] = "3aa4b31fdbf330baf28194e21697b8d6"
SRC_URI[nashorn.sha256sum] = "8b5cbd29e9dbace477a57d7c07a127312dd3cf6b8e648b0b64026616d12c6862"

OPENJDK_CHANGESET = "33d274a7dda0"
SRC_URI[openjdk.md5sum] = "105f62e8f22a68b8c4151c68a447f76e"
SRC_URI[openjdk.sha256sum] = "bf49215fe1e43e6f110470c911fce32722c843e03efb68e40cc7a832eb80faea"
