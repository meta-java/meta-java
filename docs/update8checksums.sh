#!/bin/bash
#
# quick-hack-script for updating the openjdk 8 source archive checksums
#
#set -x
set -e

function updateChecksums() {
	echo "updating ${ARCH} checksums..."
	for repo in ${REPOS}; do
		repoDL="/${repo}"
		[ "${repo}" == "openjdk" ] && repoDL=""
		echo -n "   ${ARCH}/${repo}."
		wget -q "${BASEURL}${repoDL}/archive/${TAG}.tar.bz2" -O "${tmpfile}"
		echo -n "."
		md5="$(md5sum "${tmpfile}" | cut -d " " -f1)"
		echo -n "."
		sha="$(sha256sum "${tmpfile}" | cut -d " " -f1)"
		echo -n "."
		sed -i "s|^SRC_URI\\[${repo}.md5sum\\].*\$|SRC_URI\\[${repo}.md5sum\\]    = \\\"${md5}\\\"|g" "${INCFILE}"
		sed -i "s|^SRC_URI\\[${repo}.sha256sum\\].*\$|SRC_URI\\[${repo}.sha256sum\\] = \\\"${sha}\\\"|g" "${INCFILE}"
		echo " done"
	done
}

REPOS="corba hotspot jaxp jaxws jdk langtools nashorn openjdk"
OPENJDK_UPDATE="$(basename "$(ls -1 recipes-core/openjdk/openjdk-8_*.bb)" | cut -d _ -f2 | cut -d . -f1)"

COMMON_BASEURL="https://hg.openjdk.java.net/jdk8u/jdk8u"
COMMON_TAG="jdk8u${OPENJDK_UPDATE}-ga"

AARCH32_BASEURL="https://hg.openjdk.java.net/aarch32-port/jdk8u"
AARCH32_CHANGESET_ID="$(grep "^CHANGESET_ID" recipes-core/openjdk/openjdk-8-release-aarch32.inc | cut -d= -f2 | tr -d \")"
AARCH32_TAG="jdk8u${OPENJDK_UPDATE}-ga-aarch32-${AARCH32_CHANGESET_ID}"

AARCH64_BASEURL="https://hg.openjdk.java.net/aarch64-port/jdk8u-shenandoah"
AARCH64_CHANGESET_ID="$(grep "^CHANGESET_ID" recipes-core/openjdk/openjdk-8-release-aarch64.inc | cut -d= -f2 | tr -d \")"
AARCH64_TAG="aarch64-shenandoah-jdk8u${OPENJDK_UPDATE}-${AARCH64_CHANGESET_ID}"

echo "meta-java openjdk8 source archive checksum update script"

tmpfile="$(mktemp)"

ARCH="common"
BASEURL="${COMMON_BASEURL}"
TAG="${COMMON_TAG}"
INCFILE="recipes-core/openjdk/openjdk-8-release.inc"
updateChecksums

ARCH="aarch32"
BASEURL="${AARCH32_BASEURL}"
TAG="${AARCH32_TAG}"
INCFILE="recipes-core/openjdk/openjdk-8-release-aarch32.inc"
updateChecksums

ARCH="aarch64"
BASEURL="${AARCH64_BASEURL}"
TAG="${AARCH64_TAG}"
INCFILE="recipes-core/openjdk/openjdk-8-release-aarch64.inc"
updateChecksums

rm -f "${tmpfile}"

echo "SUCCESS"
