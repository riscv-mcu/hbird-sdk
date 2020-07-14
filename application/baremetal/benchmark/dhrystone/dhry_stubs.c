#include "hbird_sdk_soc.h"

/* The functions in this file are only meant to support Dhrystone on an
 * embedded RV32 system and are obviously incorrect in general. */

long csr_cycle(void)
{
  return __get_rv_cycle();
}

long csr_instret(void)
{
  return __get_rv_instret();
}

long time(void)
{
  return SysTimer_GetLoadValue() / SOC_TIMER_FREQ;
}

