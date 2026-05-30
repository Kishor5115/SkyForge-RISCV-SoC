/* Minimal stdlib.h for bare-metal PicoRV32 (no newlib) */
#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void abort(void) { for(;;); }

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H */
