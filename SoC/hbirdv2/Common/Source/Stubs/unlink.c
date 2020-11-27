
/* See LICENSE of license details. */
#include <errno.h>
#include <hbird_sdk_hal.h>

#undef errno
extern int errno;

__WEAK int _unlink(const char *name)
{
    return -1;
}
