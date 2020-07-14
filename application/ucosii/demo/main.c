#include <stdint.h>
#include <ucos_ii.h>

#include "hbird_sdk_soc.h"

#define mainQUEUE_LENGTH (1)
static void prvSetupHardware(void);
extern void idle_task(void);

void prvSetupHardware(void)
{
}

#define STK_LEN 256

OS_STK task1_stk[STK_LEN];
OS_STK task2_stk[STK_LEN];
OS_STK task3_stk[STK_LEN];
OS_STK start_stk[STK_LEN];

#define TASK1_PRIO 13
#define TASK2_PRIO 12
#define TASK3_PRIO 11
#define TASK_START_PRIO 10

void task1(void *args)
{
    int cnt = 0;
    for (;;) {
        cnt++;
        printf("task1 is running... %d\r\n", cnt);
        OSTimeDly(200);
    }
}

void task2(void *args)
{
    int cnt = 0;
    for (;;) {
        cnt++;
        printf("task2 is running... %d\r\n", cnt);
        OSTimeDly(100);
    }
}

void task3(void *args)
{
    int cnt = 0;
    for (;;) {
        cnt++;
        printf("task3 is running... %d\r\n", cnt);
        OSTimeDly(100);
    }
}

void start_task(void *args)
{
    printf("start all task...\r\n");
    OSTaskCreate(task1, NULL, &task1_stk[STK_LEN - 1], TASK1_PRIO);
    OSTaskCreate(task2, NULL, &task2_stk[STK_LEN - 1], TASK2_PRIO);
    OSTaskCreate(task3, NULL, &task3_stk[STK_LEN - 1], TASK3_PRIO);
    OSTaskSuspend(TASK_START_PRIO);
}

int main(void)
{
    printf("Start ucosii...\r\n");
    prvSetupHardware();
    OSInit();
    OSTaskCreate(start_task, NULL, &start_stk[STK_LEN - 1], TASK_START_PRIO);
    printf("create start task success \r\n");
    OSStart();
    while (1) {
    }
}
