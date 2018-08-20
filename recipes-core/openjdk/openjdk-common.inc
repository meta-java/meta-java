inherit java autotools gettext qemu pkgconfig
inherit openjdk-build-helper

JDK_ARCH = "${@openjdk_build_helper_get_jdk_arch(d)}"

# Provides the target architecture to the configure script.
export LLVM_CONFIGURE_ARCH="${@openjdk_build_helper_get_llvm_configure_arch(d)}"
