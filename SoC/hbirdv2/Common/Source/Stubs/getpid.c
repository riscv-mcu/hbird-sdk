/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <errno.h>

__WEAK int _getpid(void)
{
    return 1;
}
