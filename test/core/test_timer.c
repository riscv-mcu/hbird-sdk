#include <stdlib.h>
#include "ctest.h"
#include "hbird_sdk_soc.h"

void core_msip_handler(void)
{
    ASSERT_NOT_EQUAL(SysTimer_GetMsipValue() & SysTimer_MSIP_MSIP_Msk, 0);
    SysTimer_ClearSWIRQ();
}

CTEST(timer, timer_irq) {
  __disable_irq();
  __disable_core_irq(SysTimerSW_IRQn);
  ASSERT_EQUAL(__get_core_irq_pending(SysTimerSW_IRQn), 0);

//   Core_Register_IRQ(SysTimerSW_IRQn ,core_msip_handler);    /* register system timer SW interrupt */
//   SysTimer_SetSWIRQ();
//   __RWMB();
//   ASSERT_NOT_EQUAL(__get_core_irq_pending(SysTimerSW_IRQn), 0);
//   __enable_irq();
//   for(uint32_t i = 10; i > 0; --i) {}
//   ASSERT_EQUAL(__get_core_irq_pending(SysTimerSW_IRQn), 0);

  __disable_core_irq(SysTimerSW_IRQn);
  __disable_irq();
}

CTEST(timer, timer_start_stop) {
    uint64_t cur_value = SysTimer_GetLoadValue();
    ctest_delay(20);
    ASSERT_NOT_EQUAL(cur_value, SysTimer_GetLoadValue());
}

CTEST(timer, timer_set_msip) {
    __disable_irq();
    SysTimer_SetMsipValue(SysTimer_MSIP_Msk);
    ASSERT_NOT_EQUAL(SysTimer_GetMsipValue() & SysTimer_MSIP_MSIP_Msk, 0);

    SysTimer_SetMsipValue(0);
    ASSERT_EQUAL(SysTimer_GetMsipValue() & SysTimer_MSIP_MSIP_Msk, 0);
    SysTimer_ClearSWIRQ();
}
