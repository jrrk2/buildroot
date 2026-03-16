################################################################################
#
# gcc142 (GCC 1.42) - riscv32 native build
#
################################################################################

GCC142_VERSION = 1.42
GCC142_SITE = $(TOPDIR)/package/gcc142/gcc-1.42
GCC142_SITE_METHOD = local
GCC142_LICENSE = GPL-1.0+
GCC142_LICENSE_FILES = COPYING
GCC142_DEPENDENCIES = binutils

# K&R C warning suppression flags
GCC142_XCFLAGS = \
	-Wno-implicit-function-declaration -Wno-return-type \
	-Wno-builtin-declaration-mismatch \
	-Wno-int-conversion -Wno-implicit-int -fgnu89-inline -Os

GCC142_INCLUDES = -I$(@D) -I$(@D)/config

# Language-independent object files
GCC142_OBJS = toplev.o version.o tree.o print-tree.o stor-layout.o fold-const.o \
	rtl.o rtlanal.o expr.o stmt.o expmed.o explow.o optabs.o varasm.o \
	symout.o dbxout.o sdbout.o emit-rtl.o insn-emit.o \
	integrate.o jump.o cse.o loop.o flow.o stupid.o combine.o \
	regclass.o local-alloc.o global-alloc.o reload.o reload1.o caller-save.o \
	insn-peep.o final.o recog.o insn-recog.o insn-extract.o insn-output.o \
	obstack.o

# C language object files
GCC142_C_OBJS = c-parse.tab.o c-decl.o c-typeck.o c-convert.o

# Preprocessor object files
GCC142_CPP_OBJS = cccp.o cexp.o version.o obstack.o

# Driver object files
GCC142_GCC_OBJS = gcc.o version.o obstack.o

define GCC142_CONFIGURE_CMDS
	ln -sf config/xm-riscv.h $(@D)/config.h
	ln -sf config/tm-riscv.h $(@D)/tm.h
	ln -sf config/riscv.md $(@D)/md
	ln -sf config/out-riscv.c $(@D)/aux-output.c
	touch $(@D)/config.status
	echo '#include "gstab.h"' > $(@D)/stab.h
endef

define GCC142_BUILD_CMDS
	# Compile all cc1 objects
	$(foreach obj,$(GCC142_OBJS) $(GCC142_C_OBJS), \
		$(TARGET_CC) $(GCC142_XCFLAGS) $(GCC142_INCLUDES) \
			-c $(@D)/$(obj:.o=.c) -o $(@D)/$(obj) && \
	) true

	# Link cc1
	$(TARGET_CC) $(GCC142_XCFLAGS) -o $(@D)/cc1 \
		$(addprefix $(@D)/,$(GCC142_C_OBJS) $(GCC142_OBJS))

	# Compile preprocessor (cccp) with include dir path
	$(TARGET_CC) $(GCC142_XCFLAGS) $(GCC142_INCLUDES) \
		-DGCC_INCLUDE_DIR=\"/usr/lib/gcc142-include\" \
		-DGPLUSPLUS_INCLUDE_DIR=\"/usr/lib/gcc142-include\" \
		-c $(@D)/cccp.c -o $(@D)/cccp.o
	$(TARGET_CC) $(GCC142_XCFLAGS) $(GCC142_INCLUDES) \
		-c $(@D)/cexp.c -o $(@D)/cexp.o

	# Link cccp (cpp)
	$(TARGET_CC) $(GCC142_XCFLAGS) -o $(@D)/cccp \
		$(@D)/cccp.o $(@D)/cexp.o $(@D)/version.o $(@D)/obstack.o

	# Compile gcc driver with search paths
	$(TARGET_CC) $(GCC142_XCFLAGS) $(GCC142_INCLUDES) \
		-DSTANDARD_STARTFILE_PREFIX=\"/usr/lib/\" \
		-DSTANDARD_EXEC_PREFIX=\"/usr/lib/gcc142-\" \
		-c $(@D)/gcc.c -o $(@D)/gcc.o

	# Link gcc driver
	$(TARGET_CC) $(GCC142_XCFLAGS) -o $(@D)/gcc142 \
		$(@D)/gcc.o $(@D)/version.o $(@D)/obstack.o
endef

define GCC142_INSTALL_TARGET_CMDS
	# Install binaries
	$(INSTALL) -D -m 0755 $(@D)/gcc142 $(TARGET_DIR)/usr/bin/gcc142
	$(INSTALL) -D -m 0755 $(@D)/cc1 $(TARGET_DIR)/usr/lib/gcc142-cc1
	$(INSTALL) -D -m 0755 $(@D)/cccp $(TARGET_DIR)/usr/lib/gcc142-cpp

	# Install compiler headers
	$(INSTALL) -d $(TARGET_DIR)/usr/lib/gcc142-include
	$(INSTALL) -m 0644 $(@D)/stddef.h $(TARGET_DIR)/usr/lib/gcc142-include/
	$(INSTALL) -m 0644 $(@D)/assert.h $(TARGET_DIR)/usr/lib/gcc142-include/
	$(INSTALL) -m 0644 $(@D)/limits.h $(TARGET_DIR)/usr/lib/gcc142-include/
	$(INSTALL) -m 0644 $(@D)/proto.h $(TARGET_DIR)/usr/lib/gcc142-include/
	$(INSTALL) -m 0644 $(@D)/gvarargs.h \
		$(TARGET_DIR)/usr/lib/gcc142-include/varargs.h
	$(INSTALL) -m 0644 $(@D)/gstdarg.h \
		$(TARGET_DIR)/usr/lib/gcc142-include/stdarg.h
	$(INSTALL) -m 0644 \
		$(TOPDIR)/package/gcc142/float.h \
		$(TARGET_DIR)/usr/lib/gcc142-include/float.h

	# Install C89-compatible libc headers (shadow musl's modern versions)
	$(INSTALL) -m 0644 \
		$(TOPDIR)/package/gcc142/include/*.h \
		$(TARGET_DIR)/usr/lib/gcc142-include/

	# GCC 1.42 link spec hardcodes "gnulib" as the runtime library name.
	# Create a symlink so it resolves to musl's libgcc.a.
	ln -sf libgcc.a $(TARGET_DIR)/usr/lib/gnulib
endef

$(eval $(generic-package))
