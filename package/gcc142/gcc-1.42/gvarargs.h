/* gvarargs.h - Redirect to system stdarg.h for modern compilers.
   GCC 1.42's original K&R varargs (__builtin_va_alist) does not work
   on ARM64 or other modern ABIs where arguments are passed in registers.

   Functions using va_alist/va_dcl must be manually converted to ANSI style:
     old: func(va_alist) va_dcl { va_list p; va_start(p); x=va_arg(p,T); }
     new: func(T x, ...) { va_list p; va_start(p, x); }  */

#ifndef _GVARARGS_H
#define _GVARARGS_H

#include <stdarg.h>

#endif /* _GVARARGS_H */
