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
