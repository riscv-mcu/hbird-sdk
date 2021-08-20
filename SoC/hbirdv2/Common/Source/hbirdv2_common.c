#include "hbird_sdk_soc.h"

__STATIC_FORCEINLINE uint64_t get_timer_freq(void)
{
    return SOC_TIMER_FREQ;
}

uint32_t measure_cpu_freq(uint32_t n)
{
    uint32_t start_mcycle, delta_mcycle;
    uint32_t start_mtime, delta_mtime;
    uint64_t mtime_freq = get_timer_freq();

    // Don't start measuruing until we see an mtime tick
    uint32_t tmp = (uint32_t)SysTimer_GetLoadValue();
    do {
        start_mtime = (uint32_t)SysTimer_GetLoadValue();
        start_mcycle = __RV_CSR_READ(CSR_MCYCLE);
    } while (start_mtime == tmp);

    do {
        delta_mtime = (uint32_t)SysTimer_GetLoadValue() - start_mtime;
        delta_mcycle = __RV_CSR_READ(CSR_MCYCLE) - start_mcycle;
    } while (delta_mtime < n);

    return (delta_mcycle / delta_mtime) * mtime_freq
           + ((delta_mcycle % delta_mtime) * mtime_freq) / delta_mtime;
}

uint32_t get_cpu_freq(void)
{
    uint32_t cpu_freq;

    // warm up
    measure_cpu_freq(1);
    // measure for real
    cpu_freq = measure_cpu_freq(100);

    return cpu_freq;
}

/**
 * \brief      delay a time in milliseconds
 * \details
 *             provide API for delay
 * \param[in]  count: count in milliseconds
 * \remarks
 */
void delay_1ms(uint32_t count)
{
    uint64_t start_mtime, delta_mtime;
    uint64_t delay_ticks = (SOC_TIMER_FREQ * (uint64_t)count) / 1000;

    start_mtime = SysTimer_GetLoadValue();

    do {
        delta_mtime = SysTimer_GetLoadValue() - start_mtime;
    } while (delta_mtime < delay_ticks);
}

#ifdef SIMULATION_XLSPIKE
// never return for xlspike
void xlspike_exit(int status)
{
    // pass exit status via DLM register
    UART0->DLM = status;
    uart_write(UART0, 4);
}
#endif

#ifdef SIMULATION_SPIKE
// never return for spike
void spike_exit(int status)
{
    extern int htif_system_reset(uint32_t type);
    htif_system_reset(status);
}
#endif

#ifdef SIMULATION_RTL
// never return for rtl
void rtlsim_exit(int status)
{
    __ASM volatile("li x3, 0xDEADBEEF");
    while (1) {
        __RV_CSR_WRITE(CSR_MSCRATCH, 0x1);
    }
}
#endif
