/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-24     Wu Han    RTT MSH Demo
 */

#include "hbird_sdk_soc.h"
#include <rtthread.h>

void hbird(int argc, char* argv[])
{
    rt_kprintf("Hello HBird SDK!\n");
}
MSH_CMD_EXPORT(hbird, msh hbird demo)


int main(void)
{
    rt_kprintf("Hello RT-Thread!\n");
    while (1) {
        rt_thread_mdelay(1000);
    }
}
