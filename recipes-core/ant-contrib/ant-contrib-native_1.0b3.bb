SUMMARY = "(java): collection of tasks, types and other tools for Apache Ant"
DESCRIPTION = "The Ant-Contrib project is a collection of tasks (and at one \
point maybe types and other tools) for Apache Ant."
HOMEPAGE = "http://ant-contrib.sourceforge.net"
PRIORITY = "optional"
SECTION = "libs"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://docs/LICENSE.txt;md5=f84919efee8dbf5c7730927c5b8716f9"

DEPENDS = "ant-native commons-cli-native commons-codec-native \
           commons-httpclient-native commons-logging-native \
           oro-native bcel-native xerces-j-native \
          "

inherit java-library native

SRC_URI = "${SOURCEFORGE_MIRROR}/ant-contrib/ant-contrib-${PV}-src.zip"

SRC_URI[md5sum] = "07b23539bef04ec56970c876a33f7665"
SRC_URI[sha256sum] = "ba3621f397af14d5a19375f391ec9bf2908c46c5558ca0df8365e04fe3ac3633"

S = "${WORKDIR}/ant-contrib"

do_compile() {
    mkdir -p build

    oe_makeclasspath cp -s ant commons-cli commons-codec commons-httpclient commons-logging oro bcel xercesImpl
    cp=build:${S}/lib/ivy/jars/ivy-1.3.1.jar:$cp

    find src/java -name "*.java" > java_files

    javac -sourcepath src/java -cp $cp -d build @java_files

    (cd src/java && find . \( -name "*.properties" -or -name "*.xml" -or -name "*.mf" \) -exec cp {} ../../build/{} \;)

    fastjar cf ${JARFILENAME} -C build .
}
