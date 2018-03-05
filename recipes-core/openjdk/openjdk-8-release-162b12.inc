require openjdk-8-release-16xbyy.inc

# We do not yet work for aarch64.
COMPATIBLE_HOST = "^(?!aarch64).*"

CORBA_CHANGESET = "f6b6ad6feb6e"
SRC_URI[corba.md5sum] = "0358300224b63f3deeba63d3de7d765c"
SRC_URI[corba.sha256sum] = "54da09fd0c76834094d9f167c03ff1ac2373f5e46fb26d24d0d018cdc59a2842"

HOTSPOT_CHANGESET = "d2e3920d2fd0"
SRC_URI[hotspot.md5sum] = "17a1da8be42ad0c7778e7090ea5003c1"
SRC_URI[hotspot.sha256sum] = "3f07ee7a49cb4258ef00a8a896b0f7f87e85f06dc31f6c0db698d8058926b365"

JAXP_CHANGESET = "e8a1a2db69dc"
SRC_URI[jaxp.md5sum] = "9b344a6cf317ca485b8790e67ccc2467"
SRC_URI[jaxp.sha256sum] = "fbd0eaed48415c2918a47e7d76ce276416bab792e1959b1d3dee2b703aa76f5a"

JAXWS_CHANGESET = "7b4329f78e52"
SRC_URI[jaxws.md5sum] = "b1da20ee79382eb5bb72077eb02addd4"
SRC_URI[jaxws.sha256sum] = "ffd31d467c6fe7fc0956e801c08168d48ba02b4dea38b7dedbafc054092ca8f0"

JDK_CHANGESET = "d201d8b87f48"
SRC_URI[jdk.md5sum] = "bced8a322e53083472b39f01e938b21a"
SRC_URI[jdk.sha256sum] = "6e057ceb02a7d8bb66233d52b23d246120b5c0d72e7a71cb6fb0ace84e8bb581"

LANGTOOLS_CHANGESET = "034738d4f1d2"
SRC_URI[langtools.md5sum] = "fbc6faea65cfc248f93f54e634d7bf50"
SRC_URI[langtools.sha256sum] = "91615ade480c706f58062e74ee112f95ab947e1c5366a29a7d9b2b6b0a2f72d3"

NASHORN_CHANGESET = "81ce60cabe97"
SRC_URI[nashorn.md5sum] = "318993c189f16894abe94db14a067618"
SRC_URI[nashorn.sha256sum] = "8df64026be98e6efad200ef8639e2f7e96a783e262b402afcb8045f46709e457"

OPENJDK_CHANGESET = "4be07cb28b21"
SRC_URI[openjdk.md5sum] = "24d30b66aaaef51af9b598c8989c1c82"
SRC_URI[openjdk.sha256sum] = "8f9ecc5fc5f9c6df671a2ef07949f86080823c89954b2b87f6727a82af679eca"


#CACAO_VERSION = "e215e36be9fc"
#CACAO_FILE = "${CACAO_VERSION}.tar.gz"
#CACAO_URI = "http://icedtea.wildebeest.org/download/drops/cacao/${CACAO_FILE};name=cacao;unpack=false"
#SRC_URI[cacao.md5sum] = "79f95f0aea4ba04cf2f1a8632ac66d14"
#SRC_URI[cacao.sha256sum] = "4966514c72ee7ed108b882d9b6e65c3adf8a8f9c2dccb029f971b3c8cb4870ab"
#
#JAMVM_VERSION = "ec18fb9e49e62dce16c5094ef1527eed619463aa"
#JAMVM_FILE = "jamvm-${JAMVM_VERSION}.tar.gz"
#JAMVM_URI = "http://icedtea.wildebeest.org/download/drops/jamvm/${JAMVM_FILE};name=jamvm;unpack=false"
#SRC_URI[jamvm.md5sum] = "d50ae193d01a9251e10679c7a2cc6ff1"
#SRC_URI[jamvm.sha256sum] = "31810266666c23822942aac62a78019c2c4589e1c5ee48329cbf42652d4437bc"
