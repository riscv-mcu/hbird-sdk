#include <stdio.h>

#define CTEST_MAIN

// uncomment lines below to enable/disable features. See README.md for details
//#define CTEST_SEGFAULT
//#define CTEST_NO_COLORS
//#define CTEST_COLOR_OK

#include "ctest.h"
#include "hbird_sdk_soc.h"

void ctest_delay(uint32_t ms)
{
    uint64_t cur_cycle = __get_rv_cycle();
    uint64_t end_cycle = cur_cycle + SystemCoreClock  / 1000 / ms;

    do {
        cur_cycle = __get_rv_cycle();
    } while (cur_cycle < end_cycle);
}

int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);

    return result;
}

