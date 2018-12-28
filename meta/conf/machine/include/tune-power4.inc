DEFAULTTUNE ?= "ppcp4"

require conf/machine/include/powerpc/arch-powerpc64.inc

TUNEVALID[power4] = "Enable IBM Power4 specific processor optimizations"
TUNE_CCARGS .= "${@bb.utils.contains('TUNE_FEATURES', 'power4', ' -mcpu=power4', '', d)}"

AVAILTUNES += "ppcp4 ppc64p4"
TUNE_FEATURES_tune-ppcp4 = "m32 fpu-hard power4"
BASE_LIB_tune-ppcp4 = "lib"
TUNE_PKGARCH_tune-ppcp4 = "ppcp4"
PACKAGE_EXTRA_ARCHS_tune-ppcp4 = "${PACKAGE_EXTRA_ARCHS_tune-powerpc} ppcp4"

TUNE_FEATURES_tune-ppc64p4 = "m64 fpu-hard power4"
BASE_LIB_tune-ppc64p4 = "lib64"
TUNE_PKGARCH_tune-ppc64p4 = "ppc64p4"
PACKAGE_EXTRA_ARCHS_tune-ppc64p4 = "${PACKAGE_EXTRA_ARCHS_tune-powerpc64} ppc64p4"

# glibc configure options to get power4 specific library
GLIBC_EXTRA_OECONF_powerpc64 += "${@bb.utils.contains('TUNE_FEATURES', 'power4', '--with-cpu=power4', '', d)}"
GLIBC_EXTRA_OECONF_powerpc += "${@bb.utils.contains('TUNE_FEATURES', 'power4', '--with-cpu=power4', '', d)}"

# QEMU usermode fails with invalid instruction error
MACHINE_FEATURES_BACKFILL_CONSIDERED_append = "${@bb.utils.contains('TUNE_FEATURES', 'power4', ' qemu-usermode', '', d)}"
