DEFAULTTUNE ?= "ppcp8"

require conf/machine/include/powerpc/arch-powerpc64.inc

TUNEVALID[power8] = "Enable IBM Power8 specific processor optimizations"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'power8', ' -mcpu=power8', '', d)}"

AVAILTUNES += "ppcp8 ppc64p8"
TUNE_FEATURES_tune-ppcp8 = "m32 fpu-hard power8 altivec"
BASE_LIB_tune-ppcp8 = "lib"
TUNE_PKGARCH_tune-ppcp8 = "ppcp8"
PACKAGE_EXTRA_ARCHS_tune-ppcp8 = "${PACKAGE_EXTRA_ARCHS_tune-powerpc} ppcp8"

TUNE_FEATURES_tune-ppc64p8 = "m64 fpu-hard power8 altivec"
BASE_LIB_tune-ppc64p8 = "lib64"
TUNE_PKGARCH_tune-ppc64p8 = "ppc64p8"
PACKAGE_EXTRA_ARCHS_tune-ppc64p8 = "${PACKAGE_EXTRA_ARCHS_tune-powerpc64} ppc64p8"

# glibc configure options to get power8 specific library
GLIBC_EXTRA_OECONF_powerpc64 += "${@bb.utils.contains('TUNE_FEATURES', 'power8', '--with-cpu=power8', '', d)}"
GLIBC_EXTRA_OECONF_powerpc += "${@bb.utils.contains('TUNE_FEATURES', 'power8', '--with-cpu=power8', '', d)}"

# QEMU usermode fails with invalid instruction error
MACHINE_FEATURES_BACKFILL_CONSIDERED_append_powerpc = "${@bb.utils.contains('TUNE_FEATURES', 'power8', ' qemu-usermode', '', d)}"
