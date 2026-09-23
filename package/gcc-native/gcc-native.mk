################################################################################
#
# gcc-native -- gcc running ON the target
#
# A Canadian cross: built on this machine, running on the target, emitting
# code for the target.  Exactly the shape package/binutils already uses to
# put as and ld on the board, and the same source and version buildroot
# built the cross compiler from, so the compiler on the target and the
# libgcc/libstdc++ already there came out of the same tree.
#
################################################################################

GCC_NATIVE_VERSION = $(call qstrip,$(BR2_GCC_VERSION))
GCC_NATIVE_SITE = $(BR2_GNU_MIRROR:/=)/gcc/gcc-$(GCC_NATIVE_VERSION)
GCC_NATIVE_SOURCE = gcc-$(GCC_NATIVE_VERSION).tar.xz
# Share package/gcc's download directory: this is the same tarball buildroot
# already fetched to build the cross compiler, and re-fetching it under
# another name would put a second identical 90 MB archive on disk -- and, as
# it happens, fail, because the buildroot mirror does not carry it.
GCC_NATIVE_DL_SUBDIR = gcc
GCC_NATIVE_LICENSE = GPL-3.0+, GPL-2.0+ with exceptions
GCC_NATIVE_LICENSE_FILES = COPYING COPYING3 COPYING.LIB COPYING.RUNTIME

GCC_NATIVE_DEPENDENCIES = binutils gmp mpfr mpc zlib

# --host and --target both the board; the autotools infrastructure supplies
# --build and the cross compiler.  --with-sysroot=/ because on the target
# the sysroot IS the root: headers at /usr/include, libraries at /usr/lib.
# --with-build-sysroot points the BUILD-time checks at staging, which is
# where those same headers live on this machine.
GCC_NATIVE_CONF_OPTS = \
	--host=$(GNU_TARGET_NAME) \
	--target=$(GNU_TARGET_NAME) \
	--prefix=/usr \
	--with-sysroot=/ \
	--with-build-sysroot=$(STAGING_DIR) \
	--enable-languages=c,c++ \
	--disable-multilib \
	--disable-bootstrap \
	--disable-nls \
	--disable-libsanitizer \
	--disable-werror \
	--without-isl \
	--with-gmp=$(STAGING_DIR)/usr \
	--with-mpfr=$(STAGING_DIR)/usr \
	--with-mpc=$(STAGING_DIR)/usr \
	--with-system-zlib

# The ISA and ABI must be pinned to the cross compiler's.  Left to itself
# gcc's riscv32 default is rv32imafdc/ilp32d -- hard float, double -- on a
# CPU that is rv32ima soft float, linked against a loader
# (ld-linux-riscv32-ilp32d.so.1) that does not exist on the board.  Nothing
# about that is visible in the compiler binary: it is a correct riscv32
# executable, and only the code it EMITS is wrong.
#
# Buildroot's own --with-arch comes from BR2_GCC_TARGET_ARCH, which is empty
# for riscv, so there is nothing to inherit; ask the cross compiler instead.
# Deferred (=, not :=) because TARGET_CC is not defined when this file is
# parsed -- evaluating it here is what produced an empty flag and the wrong
# default the first time.
GCC_NATIVE_XGCC = $(HOST_DIR)/bin/$(GNU_TARGET_NAME)-gcc
GCC_NATIVE_ARCH = $(shell $(GCC_NATIVE_XGCC) -v 2>&1 | \
	sed -n 's/.*--with-arch=\([a-z0-9_]*\).*/\1/p')
GCC_NATIVE_ABI = $(shell $(GCC_NATIVE_XGCC) -v 2>&1 | \
	sed -n 's/.*--with-abi=\([a-z0-9]*\).*/\1/p')
GCC_NATIVE_CONF_OPTS += --with-arch=$(GCC_NATIVE_ARCH) --with-abi=$(GCC_NATIVE_ABI)

# ...and refuse to build rather than emit code for the wrong machine.  An
# empty flag here does not fail configure, it silently selects gcc's default,
# which is the one outcome that looks like success and is not.
define GCC_NATIVE_CHECK_ARCH
	@test -n "$(GCC_NATIVE_ARCH)" -a -n "$(GCC_NATIVE_ABI)" || { \
		echo "gcc-native: could not read --with-arch/--with-abi from"; \
		echo "  $(GCC_NATIVE_XGCC)"; \
		echo "without them gcc defaults to rv32imafdc/ilp32d, which this"; \
		echo "CPU cannot run.  Refusing to build."; exit 1; }
	@echo "gcc-native: targeting $(GCC_NATIVE_ARCH)/$(GCC_NATIVE_ABI)"
endef
GCC_NATIVE_PRE_CONFIGURE_HOOKS += GCC_NATIVE_CHECK_ARCH

# Only the compiler proper.  A full `make` would go on to build libgcc and
# libstdc++ with the compiler it has just produced -- a riscv32 binary this
# machine cannot run -- and those libraries are already on the target from
# the identical gcc version, so there is nothing to gain by it.
define GCC_NATIVE_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) all-gcc
endef

define GCC_NATIVE_INSTALL_TARGET_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) DESTDIR=$(TARGET_DIR) install-gcc
	# gcc needs a sysroot to compile against, and buildroot does not put one
	# on the target: headers are a build-time thing it strips.  Take them
	# from staging, where they are the very headers the cross compiler used.
	$(INSTALL) -d $(TARGET_DIR)/usr/include
	cp -a $(STAGING_DIR)/usr/include/. $(TARGET_DIR)/usr/include/
	# ...and the startup files and static libc the linker needs, which are
	# likewise staging-only.
	$(INSTALL) -D -m 0644 $(STAGING_DIR)/usr/lib/crt1.o $(TARGET_DIR)/usr/lib/crt1.o
	$(INSTALL) -D -m 0644 $(STAGING_DIR)/usr/lib/crti.o $(TARGET_DIR)/usr/lib/crti.o
	$(INSTALL) -D -m 0644 $(STAGING_DIR)/usr/lib/crtn.o $(TARGET_DIR)/usr/lib/crtn.o
	$(INSTALL) -D -m 0644 $(STAGING_DIR)/usr/lib/libc.a $(TARGET_DIR)/usr/lib/libc.a
	# libc.so on a glibc sysroot is a linker script naming the real files by
	# absolute path; it is correct as it stands on the target and is what
	# lets `gcc hello.c` link.
	cp -a $(STAGING_DIR)/usr/lib/libc.so $(TARGET_DIR)/usr/lib/ 2>/dev/null || true
	cp -a $(STAGING_DIR)/usr/lib/libm.so $(TARGET_DIR)/usr/lib/ 2>/dev/null || true
	ln -sf gcc $(TARGET_DIR)/usr/bin/cc
endef

$(eval $(autotools-package))
