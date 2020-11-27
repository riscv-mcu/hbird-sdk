/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <errno.h>
#include <time.h>
#include <stdint.h>

/* Get resolution of clock. */
__WEAK int clock_getres(clockid_t clock_id, struct timespec *res)
{
    res->tv_sec = 0;
    res->tv_nsec = 1000000000 / SystemCoreClock;

    return 0;
}
