/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <sys/stat.h>
#include <errno.h>

#undef errno
extern int errno;

__WEAK int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}
