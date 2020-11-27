/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

__WEAK void *_sbrk(ptrdiff_t incr)
{
    extern char _end[];
    extern char _heap_end[];
    static char *curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end)) {
        return (void *)(-1);
    }

    curbrk += incr;
    return (void *)(curbrk - incr);
}
