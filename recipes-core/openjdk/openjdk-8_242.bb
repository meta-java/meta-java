INC_FILE_SUFFIX = ""
INC_FILE_SUFFIX_aarch64 = "-aarch64"
INC_FILE_SUFFIX_armv7a = "-aarch32"
INC_FILE_SUFFIX_armv7ve = "-aarch32"
require openjdk-8-release${INC_FILE_SUFFIX}.inc
require openjdk-8-cross.inc

do_install() {
    rm -rf ${D}${JDK_HOME}
    mkdir -p ${D}${JDK_HOME}
    cp -rp ${B}/images/j2sdk-image/* ${D}${JDK_HOME}
    chown -R root:root ${D}${JDK_HOME}
    install -m644 ${WORKDIR}/jvm.cfg  ${D}${JDK_HOME}/jre/lib/${JDK_ARCH}/
    find ${D}${JDK_HOME} -name "*.debuginfo" -exec rm {} \;
}

PACKAGES_append = " \
    ${PN}-demo \
    ${PN}-source \
"

FILES_${PN}_append = "\
    ${JDK_HOME}/bin/[a-z]* \
    ${JDK_HOME}/lib/[a-z]* \
    ${JDK_HOME}/jre/bin/[a-z]* \
    ${JDK_HOME}/jre/lib/[a-z]* \
    ${JDK_HOME}/LICENSE \
    ${JDK_HOME}/jre/LICENSE \
    ${JDK_HOME}/release \
"

FILES_${PN}-dev_append = "\
    ${JDK_HOME}/include \
"

FILES_${PN}-demo = " ${JDK_HOME}/demo ${JDK_HOME}/sample "
RDEPENDS_${PN}-demo = " ${PN} "

FILES_${PN}-doc_append = "\
    ${JDK_HOME}/man \
    ${JDK_HOME}/ASSEMBLY_EXCEPTION \
    ${JDK_HOME}/THIRD_PARTY_README \
    ${JDK_HOME}/jre/ASSEMBLY_EXCEPTION \
    ${JDK_HOME}/jre/THIRD_PARTY_README \
    ${JDK_HOME}/man \
"

FILES_${PN}-source = " ${JDK_HOME}/src.zip "

RPROVIDES_${PN} = "java2-runtime"

inherit update-alternatives

ALTERNATIVE_PRIORITY = "100"

ALTERNATIVE_${PN} = "java javac"
ALTERNATIVE_LINK_NAME[java] = "${bindir}/java"
ALTERNATIVE_TARGET[java] = "${JDK_HOME}/bin/java"

ALTERNATIVE_LINK_NAME[javac] = "${bindir}/javac"
ALTERNATIVE_TARGET[javac] = "${JDK_HOME}/bin/javac"
