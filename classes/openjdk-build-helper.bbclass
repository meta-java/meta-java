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
    pm = d.getVar('PARALLEL_MAKE', True);
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
        return cc.communicate()[0].decode('utf-8')[0]

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
