#!/bin/sh
#
# post-build.sh — runs after target-finalize, before rootfs image creation.
#
# Buildroot's target-finalize removes /usr/include and *.a from the target.
# Reinstall them so tcc can compile C programs on-device.
#
set -e

TARGET_DIR="$1"
BUILD_DIR="${BASE_DIR}/build"
SYSROOT="${HOST_DIR}/riscv32-buildroot-linux-musl/sysroot"
HOST_GCC_LIB="${HOST_DIR}/lib/gcc/riscv32-buildroot-linux-musl"

TCC_BUILD=$(echo "${BUILD_DIR}"/tcc-*)
[ -d "${TCC_BUILD}" ] || { echo "post-build: tcc build dir not found, skipping dev install"; exit 0; }

echo "post-build: reinstalling tcc dev files (headers, libs, CRT)"

# libtcc1.a and tcc internal headers
install -D -m 0644 "${TCC_BUILD}/libtcc1.a" "${TARGET_DIR}/usr/lib/tcc/libtcc1.a"
mkdir -p "${TARGET_DIR}/usr/lib/tcc/include"
cp "${TCC_BUILD}"/include/*.h "${TARGET_DIR}/usr/lib/tcc/include/"

# musl C headers
mkdir -p "${TARGET_DIR}/usr/include"
cp -a "${SYSROOT}/usr/include/"*.h "${TARGET_DIR}/usr/include/"
for d in arpa asm asm-generic bits linux net netinet netpacket sys; do
    test -d "${SYSROOT}/usr/include/${d}" && \
        cp -a "${SYSROOT}/usr/include/${d}" "${TARGET_DIR}/usr/include/"
done

# CRT startup files
for f in crt1.o crti.o crtn.o; do
    test -f "${SYSROOT}/lib/${f}" && \
        install -D -m 0644 "${SYSROOT}/lib/${f}" "${TARGET_DIR}/usr/lib/${f}"
done

# Static libs for tcc static linking
for f in libc.a libm.a libdl.a libpthread.a librt.a libcrypt.a libresolv.a libxnet.a libutil.a; do
    test -f "${SYSROOT}/lib/${f}" && \
        install -D -m 0644 "${SYSROOT}/lib/${f}" "${TARGET_DIR}/usr/lib/${f}"
done

# libgcc.a
LIBGCC=$(ls "${HOST_GCC_LIB}"/*/libgcc.a 2>/dev/null | head -1)
[ -f "${LIBGCC}" ] && install -D -m 0644 "${LIBGCC}" "${TARGET_DIR}/usr/lib/libgcc.a"

# Convenience symlinks for riscv32-linux-gnu paths (some tools look here)
mkdir -p "${TARGET_DIR}/usr/lib/riscv32-linux-gnu"
for f in crt1.o crti.o crtn.o libc.a libm.a libdl.a libpthread.a librt.a libcrypt.a libresolv.a libgcc.a; do
    test -f "${TARGET_DIR}/usr/lib/${f}" && \
        ln -sf "../${f}" "${TARGET_DIR}/usr/lib/riscv32-linux-gnu/${f}" 2>/dev/null || true
done

echo "post-build: done"
