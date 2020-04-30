# Icedtea's makefile is not compatible to parallelization so we cannot allow
# passing a valid ${PARALLEL_MAKE} to it. OTOH OpenJDK's makefiles are
# parallelizable and we need ${PARALLEL_MAKE} to derive the proper value.
# The base for this quirk is that GNU Make only considers the last "-j" option.
EXTRA_OEMAKE_remove_task-compile = "${PARALLEL_MAKE}"
EXTRA_OEMAKE_remove_task-install = "${PARALLEL_MAKEINST}"

# OpenJDK supports parallel compilation but uses a plain number for this.
# In OE we have PARALLEL_MAKE which is the actual option passed to make,
# e.g. "-j 4".
def openjdk_build_helper_get_parallel_make(d):
    pm = d.getVar('PARALLEL_MAKE');
    if not pm or '-j' not in pm:
        return 1

    return pm.partition('-j')[2].strip().split(' ')[0]

# All supported cross compilers support the compiler flags that were
# added to make compilation with gcc6 work. But the host compiler for
# native compilation is a different story: it may be too old (for example,
# gcc 4.9.2 on Debian Wheezy). In that case we need to check what the
# version is and only add the flags that are appropriate for that GCC
# version.
def openjdk_build_helper_get_cflags_by_cc_version(d, version):
    if version.isdigit():
        return d.getVar('FLAGS_GCC%d' % int(version)) or ''
    return ''

def openjdk_build_helper_get_build_cflags(d):
    def get_build_cc_version(build_cc):
        from subprocess import Popen, PIPE
        cmd = d.expand('%s -dumpversion' % build_cc).split()
        cc = Popen(cmd, stdout=PIPE, stderr=PIPE)
        return cc.communicate()[0].decode('utf-8').split()[0]

    build_cc = d.getVar('BUILD_CC')
    version = get_build_cc_version(build_cc)
    return openjdk_build_helper_get_cflags_by_cc_version(d, version)

def openjdk_build_helper_get_target_cflags(d):
    import re

    # in the cross case, trust that GCCVERSION is correct. This won't
    # work if the native toolchain is Clang, but as of this writing that
    # doesn't work anyway.
    version = d.getVar('GCCVERSION')[0]
    # skip non digit characters at the beginning, e.g. from "linaro-6.2%"
    match = re.search("\d", version)
    if match:
        version = version[match.start():]
    return openjdk_build_helper_get_cflags_by_cc_version(d, version)

# OpenJDK uses slightly different names for certain arches. We need to know
# this to create some files which are expected by the build.
def openjdk_build_helper_get_jdk_arch(d):
    import bb

    jdk_arch = d.getVar('TRANSLATED_TARGET_ARCH')
    if jdk_arch == "x86-64":
        jdk_arch = "amd64"
    elif jdk_arch == "powerpc":
        jdk_arch = "ppc"
    elif jdk_arch == "powerpc64":
        jdk_arch = "ppc64"
    elif jdk_arch in ['i486', 'i586', 'i686']:
        jdk_arch = "i386"

    return jdk_arch

# Shark also needs slightly different names for certain arches. Due to the fact
# these differ from the "normal" OpenJDK arch names we have a separate function
# for Shark here. Furthermore we warn if we think Shark doesn't support the arch
def openjdk_build_helper_get_llvm_configure_arch(d):
    import bb;

    arch = d.getVar('TRANSLATED_TARGET_ARCH')
    if arch in ['i386', 'i486', 'i586', 'i686', 'x86-64']:
        arch = "x86"
    elif arch in ['mipsel', 'mips']:
        arch = "mips"
    elif arch in ['powerpc', 'powerpc64']:
        arch = "powerpc"
    elif arch == "arm":
        arch = "arm"
    else:
        if 'shark' in d.getVar('PACKAGECONFIG').split():
            bb.warn("%s does not support %s in Shark builds yet" % (d.getVar('PN'), arch) );

    return arch

# Again it seems IcedTea native also needs slightly different names for certain
# arches. Therefore provide the translation.
def openjdk_build_helper_get_icedtea_arch(d):
    import bb;

    arch = d.getVar('TRANSLATED_TARGET_ARCH')
    if arch == "x86-64":
        arch = "amd64"
    elif arch in ['i386', 'i486', 'i586', 'i686']:
        arch = "x86"

    return arch
