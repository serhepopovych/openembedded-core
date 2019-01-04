require binutils.inc
require binutils-${PV}.inc

DEPENDS += "flex bison zlib"

EXTRA_OECONF += "--with-sysroot=/ \
                --enable-install-libbfd \
                --enable-install-libiberty \
                --enable-shared \
                --with-system-zlib \
                "

EXTRA_OEMAKE_append_libc-musl = "\
                                 gt_cv_func_gnugettext1_libc=yes \
                                 gt_cv_func_gnugettext2_libc=yes \
                                "
EXTRA_OECONF_class-native = "--enable-targets=all \
                             --enable-64-bit-bfd \
                             --enable-install-libiberty \
                             --enable-install-libbfd \
                             --disable-werror"

do_configure_append_class-native () {
	for l in zlib intl bfd libiberty opcodes; do
		oe_runmake configure-${l}
	done
}

do_compile_class-native () {
	for l in zlib intl bfd libiberty opcodes; do
		cd "${l}"
		autotools_do_compile
		cd - >/dev/null
	done
}

do_install_class-native () {
	for l in bfd libiberty opcodes; do
		cd "${l}"
		autotools_do_install
		cd - >/dev/null
	done

	# Install the libiberty header
	install -d ${D}${includedir}
	install -m 644 ${S}/include/ansidecl.h ${D}${includedir}
	install -m 644 ${S}/include/libiberty.h ${D}${includedir}
}

# Split out libbfd-*.so so including perf doesn't include extra stuff
PACKAGE_BEFORE_PN += "libbfd"
FILES_libbfd = "${libdir}/libbfd-*.so"

BBCLASSEXTEND = "native nativesdk"
