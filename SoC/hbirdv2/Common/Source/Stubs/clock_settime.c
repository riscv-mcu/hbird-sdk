/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <errno.h>
#include <time.h>

/* Set CLOCK to value TP. */
__WEAK int clock_settime(clockid_t clock_id, const struct timespec *tp)
{
    return -1;
}
