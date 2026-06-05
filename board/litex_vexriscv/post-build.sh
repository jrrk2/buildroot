#!/bin/sh
#
# post-build.sh — runs after target-finalize, before rootfs image creation.
#
# Buildroot's target-finalize removes /usr/include from the target.
# Reinstall a curated set so gcc8-native can compile C programs on-device,
# while keeping the total rootfs size under 32MB (flashxip.bin budget).
#
set -e

TARGET_DIR="$1"
BUILD_DIR="${BASE_DIR}/build"
SYSROOT="${HOST_DIR}/riscv32-buildroot-linux-musl/sysroot"

echo "post-build: reinstalling dev headers for on-device gcc"

# --- musl top-level C headers (skip BFD, zlib, curses — not needed) ---
mkdir -p "${TARGET_DIR}/usr/include"
for h in "${SYSROOT}"/usr/include/*.h; do
    name=$(basename "$h")
    case "$name" in
        # BFD/binutils dev headers — not needed for C compilation
        bfd.h|bfdlink.h|dis-asm.h|sframe.h|ansidecl.h|symcat.h) continue ;;
        # Library-specific dev headers — large and rarely needed on target
        zlib.h|zconf.h|curses.h|ncurses.h|term.h|termcap.h) continue ;;
        # Lua dev header — lua runtime is already installed as .so
        luaconf.h|lua.h|lualib.h|lauxlib.h) continue ;;
        *) cp "$h" "${TARGET_DIR}/usr/include/" ;;
    esac
done

# --- subdirectory headers ---
# sys/, bits/, arpa/, net/, netinet/, netpacket/ — all needed for POSIX/sockets
for d in sys bits arpa net netinet netpacket; do
    test -d "${SYSROOT}/usr/include/${d}" && \
        cp -a "${SYSROOT}/usr/include/${d}" "${TARGET_DIR}/usr/include/"
done

# asm/ and asm-generic/ — needed for low-level / syscall code
for d in asm asm-generic; do
    test -d "${SYSROOT}/usr/include/${d}" && \
        cp -a "${SYSROOT}/usr/include/${d}" "${TARGET_DIR}/usr/include/"
done

# linux/ — curated subset for embedded hardware access on Sonata
# Full linux/ is 7MB; this subset is ~100KB covering common use cases.
LINUX_KEEP="
    types.h posix_types.h stddef.h compiler.h swab.h
    ioctl.h fcntl.h stat.h limits.h fs.h errno.h
    time.h signal.h wait.h
    termios.h serial.h tty.h
    gpio.h i2c.h i2c-dev.h
    socket.h sockios.h in.h in6.h if.h if_ether.h if_arp.h
    un.h uio.h poll.h select.h
    mman.h sched.h prctl.h ptrace.h
    reboot.h
"
mkdir -p "${TARGET_DIR}/usr/include/linux"
for h in $LINUX_KEEP; do
    src="${SYSROOT}/usr/include/linux/${h}"
    test -f "$src" && cp "$src" "${TARGET_DIR}/usr/include/linux/"
done
# spi/ subdir
if [ -d "${SYSROOT}/usr/include/linux/spi" ]; then
    mkdir -p "${TARGET_DIR}/usr/include/linux/spi"
    cp "${SYSROOT}/usr/include/linux/spi/spidev.h" \
       "${TARGET_DIR}/usr/include/linux/spi/" 2>/dev/null || true
fi
# byteorder/ — needed by network code
if [ -d "${SYSROOT}/usr/include/linux/byteorder" ]; then
    cp -a "${SYSROOT}/usr/include/linux/byteorder" \
       "${TARGET_DIR}/usr/include/linux/"
fi

# --- CRT startup files (needed for gcc linking) ---
for f in crt1.o crti.o crtn.o; do
    test -f "${SYSROOT}/lib/${f}" && \
        install -D -m 0644 "${SYSROOT}/lib/${f}" "${TARGET_DIR}/usr/lib/${f}"
done

# --- crtbegin.o / crtend.o (from cross-toolchain libgcc, needed by ld) ---
HOST_GCC_LIB="${HOST_DIR}/lib/gcc/riscv32-buildroot-linux-musl"
GCC8_LIBDIR="${TARGET_DIR}/usr/lib/gcc/riscv32-buildroot-linux-musl/8.4.0"
for f in crtbegin.o crtend.o; do
    src=$(find "${HOST_GCC_LIB}" -name "${f}" 2>/dev/null | head -1)
    test -f "$src" && install -D -m 0644 "$src" "${GCC8_LIBDIR}/${f}"
done

# --- Generate a minimal specs file for gcc8 to use sysroot=/ on target ---
# gcc8 was configured with --with-sysroot pointing to the build host staging dir.
# Override sysroot and add /usr/lib to link paths (multilib dirs don't exist on target).
cat > "${GCC8_LIBDIR}/specs" <<'SPECS'
*self_spec:
--sysroot=/

*link_libgcc:
-L/usr/lib/gcc/riscv32-buildroot-linux-musl/8.4.0 -L/usr/lib -L/lib -lgcc

*startfile:
/usr/lib/crt1.o /usr/lib/crti.o %{shared|pie:crtbeginS.o%s;:crtbegin.o%s}

*endfile:
%{shared|pie:crtendS.o%s;:crtend.o%s} /usr/lib/crtn.o

SPECS

# --- Remove static libraries (saves ~6MB; gcc uses dynamic linking) ---
find "${TARGET_DIR}" -name '*.a' -delete

# --- libgcc_s.so linker script references -lgcc (libgcc.a), rewrite for dynamic-only ---
# Replace the linker script so -lgcc resolves to libgcc_s.so.1 without needing libgcc.a
echo '/* GNU ld script */ GROUP ( libgcc_s.so.1 )' > "${TARGET_DIR}/lib/libgcc_s.so"
# gcc8 searches its own lib dir for -lgcc; provide a symlink there too
ln -sf /lib/libgcc_s.so "${GCC8_LIBDIR}/libgcc.so"

# --- Remove gcc tools not needed for compilation ---
# gcov/gcov-tool/gcov-dump are coverage analysis only (~1.6MB)
rm -f "${TARGET_DIR}"/usr/bin/gcov*

# Keep all binutils shared libs — as/ld need libopcodes, libsframe, libctf at runtime

# --- Remove duplicate old binutils shared libs ---
for lib in libbfd; do
    newest=$(ls "${TARGET_DIR}/usr/lib/${lib}"-*.so 2>/dev/null | sort -V | tail -1)
    for f in "${TARGET_DIR}/usr/lib/${lib}"-*.so; do
        [ "$f" = "$newest" ] || rm -f "$f"
    done
done

# --- Remove luac (lua bytecode compiler, not needed at runtime) ---
rm -f "${TARGET_DIR}/usr/bin/luac"

# --- Remove unneeded gcc8 internal tools ---
GCC8_LIBDIR="${TARGET_DIR}/usr/lib/gcc/riscv32-buildroot-linux-musl/8.4.0"
rm -f "${GCC8_LIBDIR}/lto-wrapper"
rm -rf "${GCC8_LIBDIR}/install-tools"

# --- Remove gcc LTO wrappers (LTO is disabled) ---
rm -f "${TARGET_DIR}"/usr/bin/gcc-ar "${TARGET_DIR}"/usr/bin/gcc-nm "${TARGET_DIR}"/usr/bin/gcc-ranlib
rm -f "${TARGET_DIR}"/usr/bin/*-gcc-ar "${TARGET_DIR}"/usr/bin/*-gcc-nm "${TARGET_DIR}"/usr/bin/*-gcc-ranlib

# --- Remove libstdc++ (nothing on target links against it; gcc8 compiles C only) ---
rm -f "${TARGET_DIR}"/usr/lib/libstdc++* "${TARGET_DIR}"/usr/lib/libstdc++*.py

# --- Remove gitweb (leftover from git package, not useful on target) ---
rm -rf "${TARGET_DIR}/usr/share/gitweb"

# --- Remove m4 (GNU macro processor, 234KB — only needed by bison, not gcc) ---
rm -f "${TARGET_DIR}/usr/bin/m4"

# --- Slim down git for romfs (hardlinks → symlinks, remove unneeded helpers) ---
if [ -d "${TARGET_DIR}/usr/libexec/git-core" ]; then
    # Convert hardlinks to symlinks (romfs doesn't support hardlinks)
    GIT_INODE=$(stat -f '%i' "${TARGET_DIR}/usr/bin/git" 2>/dev/null || stat -c '%i' "${TARGET_DIR}/usr/bin/git")
    for f in "${TARGET_DIR}"/usr/libexec/git-core/*; do
        [ -f "$f" ] || continue
        F_INODE=$(stat -f '%i' "$f" 2>/dev/null || stat -c '%i' "$f")
        if [ "$F_INODE" = "$GIT_INODE" ]; then
            ln -sf ../../bin/git "$f"
        fi
    done
    # Remove standalone binaries not needed for basic git usage
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/scalar
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-imap-send
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-daemon
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-http-backend
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-http-fetch
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-http-push
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-shell
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-sh-i18n--envsubst
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-cvsserver
    rm -f "${TARGET_DIR}"/usr/libexec/git-core/git-p4
    echo "post-build: slimmed git-core (hardlinks→symlinks, removed helpers)"
fi

echo "post-build: done"
