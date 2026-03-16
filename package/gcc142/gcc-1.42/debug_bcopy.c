#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bcopy(const void *src, void *dst, int len) {
    /* Check for obviously truncated pointers (upper 32 bits zero, but value > 0x100000) */
    unsigned long long s = (unsigned long long)src;
    unsigned long long d = (unsigned long long)dst;
    if ((s != 0 && s < 0x100000000ULL && s > 0x100000) ||
        (d != 0 && d < 0x100000000ULL && d > 0x100000)) {
        fprintf(stderr, "TRUNCATED POINTER in bcopy: src=%p dst=%p len=%d\n", src, dst, len);
        /* Print backtrace using macOS API */
        void *bt[20];
        /* Use abort to get a crash we can debug */
        abort();
    }
    memmove(dst, src, len);
}
