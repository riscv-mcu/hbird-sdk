/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <errno.h>

#undef errno
extern int errno;

__WEAK int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}
