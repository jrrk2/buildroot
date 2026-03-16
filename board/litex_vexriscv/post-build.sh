#!/bin/sh
#
# post-build.sh — runs after target-finalize, before rootfs image creation.
#
# Buildroot's target-finalize removes /usr/include and *.a from the target.
# Reinstall a curated set so tcc can compile C programs on-device, while
# keeping the total rootfs size under 32MB (flashxip.bin budget).
#
set -e

TARGET_DIR="$1"
BUILD_DIR="${BASE_DIR}/build"
SYSROOT="${HOST_DIR}/riscv32-buildroot-linux-musl/sysroot"
HOST_GCC_LIB="${HOST_DIR}/lib/gcc/riscv32-buildroot-linux-musl"

TCC_BUILD=$(echo "${BUILD_DIR}"/tcc-*)
[ -d "${TCC_BUILD}" ] || { echo "post-build: tcc build dir not found, skipping dev install"; exit 0; }

echo "post-build: reinstalling tcc dev files (headers, libs, CRT)"

# --- libtcc1.a and tcc internal headers ---
install -D -m 0644 "${TCC_BUILD}/libtcc1.a" "${TARGET_DIR}/usr/lib/tcc/libtcc1.a"
mkdir -p "${TARGET_DIR}/usr/lib/tcc/include"
cp "${TCC_BUILD}"/include/*.h "${TARGET_DIR}/usr/lib/tcc/include/"

# --- musl top-level C headers (skip BFD, zlib, curses — not needed by tcc) ---
mkdir -p "${TARGET_DIR}/usr/include"
for h in "${SYSROOT}"/usr/include/*.h; do
    name=$(basename "$h")
    case "$name" in
        # BFD/binutils dev headers — not needed for C compilation
        bfd.h|bfdlink.h|dis-asm.h|sframe.h|ansidecl.h|symcat.h) continue ;;
        # Library-specific dev headers — large and rarely needed on target
        zlib.h|zconf.h|curses.h|ncurses.h|term.h|termcap.h) continue ;;
        # Lua dev header — large, lua runtime is already installed as .so
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

# --- CRT startup files ---
for f in crt1.o crti.o crtn.o; do
    test -f "${SYSROOT}/lib/${f}" && \
        install -D -m 0644 "${SYSROOT}/lib/${f}" "${TARGET_DIR}/usr/lib/${f}"
done

# --- Static libs for tcc static linking ---
for f in libc.a libm.a libdl.a libpthread.a librt.a libcrypt.a libresolv.a libxnet.a libutil.a; do
    test -f "${SYSROOT}/lib/${f}" && \
        install -D -m 0644 "${SYSROOT}/lib/${f}" "${TARGET_DIR}/usr/lib/${f}"
done

# --- libgcc.a ---
LIBGCC=$(ls "${HOST_GCC_LIB}"/*/libgcc.a 2>/dev/null | head -1)
[ -f "${LIBGCC}" ] && install -D -m 0644 "${LIBGCC}" "${TARGET_DIR}/usr/lib/libgcc.a"

# --- Convenience symlinks for riscv32-linux-gnu paths ---
mkdir -p "${TARGET_DIR}/usr/lib/riscv32-linux-gnu"
for f in crt1.o crti.o crtn.o libc.a libm.a libdl.a libpthread.a librt.a libcrypt.a libresolv.a libgcc.a; do
    test -f "${TARGET_DIR}/usr/lib/${f}" && \
        ln -sf "../${f}" "${TARGET_DIR}/usr/lib/riscv32-linux-gnu/${f}" 2>/dev/null || true
done

# --- Remove duplicate old binutils shared libs ---
# Keep only the newest version of libbfd/libopcodes/libsframe/libctf.
# Two binutils versions can end up installed if the build dir has old artifacts.
for lib in libbfd libopcodes; do
    newest=$(ls "${TARGET_DIR}/usr/lib/${lib}"-*.so 2>/dev/null | sort -V | tail -1)
    for f in "${TARGET_DIR}/usr/lib/${lib}"-*.so; do
        [ "$f" = "$newest" ] || rm -f "$f"
    done
done
# Keep only one libsframe and libctf (drop versioned duplicates, keep symlinks)
for lib in libsframe libctf; do
    newest=$(ls "${TARGET_DIR}/usr/lib/${lib}".so.*.*.* 2>/dev/null | sort -V | tail -1)
    for f in "${TARGET_DIR}/usr/lib/${lib}".so.*.*.*; do
        [ "$f" = "$newest" ] || rm -f "$f"
    done
done

echo "post-build: done"
