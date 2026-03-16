################################################################################
#
# gcc8-native — GCC 8.4.0 built to run on the target (riscv32 native compiler)
#
# This cross-compiles GCC with --host == --target == riscv32-linux-musl so the
# resulting binaries run on the device and compile for the device.
# C language only, no multilib, minimal size.
#
################################################################################

GCC8_NATIVE_VERSION = 8.4.0
GCC8_NATIVE_SITE = $(BR2_GNU_MIRROR:/=)/gcc/gcc-$(GCC8_NATIVE_VERSION)
GCC8_NATIVE_SOURCE = gcc-$(GCC8_NATIVE_VERSION).tar.xz
GCC8_NATIVE_LICENSE = GPL-3.0+, LGPL-3.0+, GPL-3.0+ with GCC Runtime Library Exception
GCC8_NATIVE_LICENSE_FILES = COPYING COPYING3 COPYING.LIB COPYING3.LIB
GCC8_NATIVE_DEPENDENCIES = binutils

# GCC needs GMP, MPFR, MPC — use bundled copies to avoid dependency headaches
GCC8_NATIVE_CONF_OPTS = \
	--host=$(GNU_TARGET_NAME) \
	--target=$(GNU_TARGET_NAME) \
	--build=$(GNU_HOST_NAME) \
	--prefix=/usr \
	--libexecdir=/usr/lib \
	--enable-languages=c \
	--disable-multilib \
	--disable-shared \
	--enable-static \
	--disable-libssp \
	--disable-libquadmath \
	--disable-libmudflap \
	--disable-libgomp \
	--disable-libatomic \
	--disable-libitm \
	--disable-libsanitizer \
	--disable-libvtv \
	--disable-libstdcxx \
	--disable-nls \
	--disable-decimal-float \
	--disable-fixed-point \
	--disable-threads \
	--disable-bootstrap \
	--with-newlib \
	--without-headers \
	--with-gnu-as \
	--with-gnu-ld \
	--with-sysroot=$(STAGING_DIR) \
	--with-build-sysroot=$(STAGING_DIR) \
	--with-gmp-include=$(HOST_DIR)/include \
	--with-gmp-lib=$(HOST_DIR)/lib \
	--with-mpfr-include=$(HOST_DIR)/include \
	--with-mpfr-lib=$(HOST_DIR)/lib \
	--with-mpc-include=$(HOST_DIR)/include \
	--with-mpc-lib=$(HOST_DIR)/lib \
	--with-system-zlib

GCC8_NATIVE_CONF_ENV = \
	$(TARGET_CONFIGURE_ARGS) \
	$(TARGET_CONFIGURE_OPTS) \
	CFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
	CXXFLAGS_FOR_TARGET="$(TARGET_CFLAGS)"

define GCC8_NATIVE_CONFIGURE_CMDS
	mkdir -p $(@D)/build
	(cd $(@D)/build && \
		$(GCC8_NATIVE_CONF_ENV) \
		../configure $(GCC8_NATIVE_CONF_OPTS))
endef

define GCC8_NATIVE_BUILD_CMDS
	$(MAKE) -C $(@D)/build \
		CFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
		all-gcc
endef

define GCC8_NATIVE_INSTALL_TARGET_CMDS
	$(MAKE) -C $(@D)/build \
		DESTDIR=$(TARGET_DIR) \
		install-gcc
	# Remove documentation and unneeded files
	rm -rf $(TARGET_DIR)/usr/share/man \
	       $(TARGET_DIR)/usr/share/info \
	       $(TARGET_DIR)/usr/share/locale \
	       $(TARGET_DIR)/usr/lib/gcc/$(GNU_TARGET_NAME)/$(GCC8_NATIVE_VERSION)/include-fixed
	# Strip the compiler binaries
	$(TARGET_STRIP) $(TARGET_DIR)/usr/bin/gcc* 2>/dev/null || true
	$(TARGET_STRIP) $(TARGET_DIR)/usr/lib/gcc/$(GNU_TARGET_NAME)/$(GCC8_NATIVE_VERSION)/cc1 2>/dev/null || true
	$(TARGET_STRIP) $(TARGET_DIR)/usr/lib/gcc/$(GNU_TARGET_NAME)/$(GCC8_NATIVE_VERSION)/lto1 2>/dev/null || true
endef

$(eval $(autotools-package))
