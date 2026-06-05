################################################################################
#
# ocaml3 — OCaml 3.07 bytecode interpreter + toplevel
#
# Two-stage build:
#   1. HOST_OCAML3: builds native ocaml on the host to produce bytecode
#      (ocaml toplevel, stdlib.cma — these are architecture-independent)
#   2. OCAML3: cross-compiles ocamlrun (the bytecode interpreter, a C program)
#      and installs everything to the target rootfs.
#
################################################################################

OCAML3_VERSION = 3.07-pl2
OCAML3_SITE = https://github.com/ocaml/ocaml.git
OCAML3_SITE_METHOD = git
OCAML3_LICENSE = LGPL-2.1-or-later WITH OCaml-linking-exception
OCAML3_LICENSE_FILES = LICENSE
OCAML3_DEPENDENCIES = host-ocaml3

HOST_OCAML3_LICENSE = LGPL-2.1-or-later WITH OCaml-linking-exception

# ---------- HOST BUILD (native OCaml for bytecode generation) ----------------

define HOST_OCAML3_CONFIGURE_CMDS
	# OCaml 3.07's configure is too old for modern systems.
	# Write config files manually (same approach used for manual build).

	cp $(OCAML3_PKGDIR)/host-config-Makefile $(@D)/config/Makefile
	cp $(OCAML3_PKGDIR)/host-config-m.h $(@D)/config/m.h
	cp $(OCAML3_PKGDIR)/host-config-s.h $(@D)/config/s.h
	cp $(TOPDIR)/../ocaml-3.07-host/boot/* $(@D)/boot/
endef

define HOST_OCAML3_BUILD_CMDS
	# Build coldstart (native ocamlrun + stdlib) — enough for bytecode.
	# Full 'make world' fails on otherlibraries but we only need the runtime.
	$(MAKE1) -C $(@D) coldstart 2>&1 || true
	test -f $(@D)/boot/ocamlrun
	test -f $(@D)/stdlib/stdlib.cma
endef

define HOST_OCAML3_INSTALL_CMDS
	mkdir -p $(HOST_DIR)/share/ocaml3
	# Toplevel is bytecode (arch-independent) — use pre-built copy
	cp $(TOPDIR)/../ocaml-3.07-host/ocaml $(HOST_DIR)/share/ocaml3/ocaml
	cp $(@D)/stdlib/stdlib.cma $(HOST_DIR)/share/ocaml3/
	cp $(@D)/stdlib/std_exit.cmo $(HOST_DIR)/share/ocaml3/
	cp $(@D)/stdlib/camlheader $(HOST_DIR)/share/ocaml3/
	cp $(@D)/stdlib/*.cmi $(HOST_DIR)/share/ocaml3/
endef

# ---------- TARGET BUILD (cross-compiled ocamlrun) ---------------------------

define OCAML3_CONFIGURE_CMDS
	sed -e 's|@TARGET_CC@|$(TARGET_CC)|g' \
	    -e 's|@TARGET_RANLIB@|$(TARGET_RANLIB)|g' \
	    -e 's|@TARGET_AR@|$(TARGET_AR)|g' \
	    -e 's|@TARGET_LD@|$(TARGET_LD)|g' \
	    $(OCAML3_PKGDIR)/target-config-Makefile.in > $(@D)/config/Makefile
	cp $(OCAML3_PKGDIR)/target-config-m.h $(@D)/config/m.h
	cp $(OCAML3_PKGDIR)/host-config-s.h $(@D)/config/s.h
endef

define OCAML3_BUILD_CMDS
	# Only build the bytecode runtime (ocamlrun) for the target.
	# Everything else (toplevel, stdlib) comes from the host build.
	$(MAKE) -C $(@D)/byterun all
endef

define OCAML3_INSTALL_TARGET_CMDS
	# Install cross-compiled ocamlrun (bytecode interpreter)
	$(INSTALL) -D -m 0755 $(@D)/byterun/ocamlrun \
		$(TARGET_DIR)/usr/bin/ocamlrun
	$(TARGET_STRIP) $(TARGET_DIR)/usr/bin/ocamlrun

	# Install host-built OCaml toplevel (bytecode, arch-independent)
	$(INSTALL) -D -m 0755 $(HOST_DIR)/share/ocaml3/ocaml \
		$(TARGET_DIR)/usr/bin/ocaml
	# Fix shebang to use target ocamlrun
	sed -i '1s|.*|#!/usr/bin/ocamlrun|' $(TARGET_DIR)/usr/bin/ocaml

	# Install standard library
	mkdir -p $(TARGET_DIR)/usr/lib/ocaml
	cp $(HOST_DIR)/share/ocaml3/stdlib.cma $(TARGET_DIR)/usr/lib/ocaml/
	cp $(HOST_DIR)/share/ocaml3/std_exit.cmo $(TARGET_DIR)/usr/lib/ocaml/
	cp $(HOST_DIR)/share/ocaml3/camlheader $(TARGET_DIR)/usr/lib/ocaml/
	cp $(HOST_DIR)/share/ocaml3/*.cmi $(TARGET_DIR)/usr/lib/ocaml/

	# Set OCAMLLIB environment variable
	mkdir -p $(TARGET_DIR)/etc/profile.d
	echo "export OCAMLLIB='/usr/lib/ocaml'" \
		> $(TARGET_DIR)/etc/profile.d/ocaml.sh
endef

$(eval $(generic-package))
$(eval $(host-generic-package))
