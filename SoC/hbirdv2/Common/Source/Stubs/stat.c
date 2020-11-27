/* See LICENSE of license details. */
#include "hbird_sdk_soc.h"
#include <sys/stat.h>

__WEAK int _stat(char *file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}
