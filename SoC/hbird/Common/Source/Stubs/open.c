/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <errno.h>

#undef errno
extern int errno;

__WEAK int _open(const char *name, int flags, int mode)
{
    errno = ENOSYS;
    return -1;
}
