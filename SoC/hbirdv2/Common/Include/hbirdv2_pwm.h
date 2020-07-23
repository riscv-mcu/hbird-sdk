// See LICENSE for license details.

#ifndef _HBIRDV2_PWM_H
#define _HBIRDV2_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Register offsets */
#define PWM_TIMER_TO_TIMER_OFFSET           0x40
#define PWM_CHANNEL_TO_CHANNEL_OFFSET       0x04

#define PWM_TIMER_CMD_OFFSET                0x00
#define PWM_TIMER_CONFIG_OFFSET             0x04
#define PWM_TIMER_THRESHOLD_OFFSET          0x08
#define PWM_TIMER_TH_CHANNEL_OFFSET         0x0C
#define PWM_TIMER_COUNTER_OFFSET            0x2C

/* Timer Base:    PWM_BASE_ADDR + Timer*PWM_TIMER_TO_TIMER_OFFSET
 *   Config:      + PWM_TIMER_CONFIG_OFFSET
 *   Threhsold:   + PWM_TIMER_THRESHOLD_OFFSET
 *   Channel Thresh:    + PWM_TIMER_TH_CHANNEL_OFFSET + Channel*PWM_CHANNEL_TO_CHANNEL_OFFSET
 */
#define PWM_TIMER_BASE_ADDR(timer)                      (PWM_BASE + timer*PWM_TIMER_TO_TIMER_OFFSET)
#define PWM_TIMER_CMD_ADDR(timer)                       (PWM_TIMER_BASE_ADDR(timer) + PWM_TIMER_CMD_OFFSET)
#define PWM_TIMER_CONFIG_ADDR(timer)                    (PWM_TIMER_BASE_ADDR(timer) + PWM_TIMER_CONFIG_OFFSET)
#define PWM_TIMER_THRESHOLD_ADDR(timer)                 (PWM_TIMER_BASE_ADDR(timer) + PWM_TIMER_THRESHOLD_OFFSET)
#define PWM_TIMER_TH_CHANNEL_ADDR(timer, channel)       (PWM_TIMER_BASE_ADDR(timer) + PWM_TIMER_TH_CHANNEL_OFFSET + (channel*PWM_CHANNEL_TO_CHANNEL_OFFSET))
#define PWM_TIMER_COUNTER_ADDR(timer)                   (PWM_TIMER_BASE_ADDR(timer) + PWM_TIMER_COUNTER_OFFSET)

#define REG_EVENT_CFG                                   (PWM_BASE + 0x100)
#define REG_PWM_TIMER_EN                                (PWM_BASE + 0X104)

#define PWM_TIMER_EN(timer)                             (0x1<<timer)
#define PWM_TIMER_EN_ALL                                (0xF)
#define PWM_TIMER_DISABLE(timer)                        ((~PWM_TIMER_EN(timer))&0xF)
#define PWM_TIMER_DISABLE_ALL                           (0x0)


/* Constants */

#define ADV_TIMER_INMODE_AO       0x0 //event at each clock cycle
#define ADV_TIMER_INMODE_IN0      0x1 //event if input signal is 0
#define ADV_TIMER_INMODE_IN1      0x2 //event if input signal is 1
#define ADV_TIMER_INMODE_RISE     0x3 //event on input signal rising edge
#define ADV_TIMER_INMODE_FALL     0x4 //event on input signal falling edge
#define ADV_TIMER_INMODE_EDGE     0x5 //event on input signal rising or falling edge
#define ADV_TIMER_INMODE_ARM_RISE 0x6 //event on input signal rising edge when armed
#define ADV_TIMER_INMODE_ARM_FALL 0x7 //event on input signal falling edge when armed

#define ADV_TIMER_SAW             0x1
#define ADV_TIMER_NOSAW           0x0

#define ADV_TIMER_USEREF          0x1
#define ADV_TIMER_USESIG          0x0

#define ALL_CHANNEL               0x1
#define THIS_CHANNEL_ONLY         0x0

// When channel counter reaches threshold:
#define ADV_TIMER_OP_SET    0       // 000: Set
#define ADV_TIMER_OP_TOGRST 1       // 001: Toggle then next is Clear
#define ADV_TIMER_OP_SETRST 2       // 010: Set then Clear
#define ADV_TIMER_OP_TOG    3       // 011: Toggle
#define ADV_TIMER_OP_RST    4       // 100: Clear
#define ADV_TIMER_OP_TOGSET 5       // 101: Toggle then next is Set
#define ADV_TIMER_OP_RSTSET 6       // 110: Clear then Set

static inline void pwm_timer_cmd(PwmTimerNum timer, PwmCounterCmd CMD) {
    *(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_CMD_ADDR(timer)) = (unsigned int)CMD;
}

static inline void pwm_timer_config(PwmTimerNum timer, unsigned int conf) {
    *(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_CONFIG_ADDR(timer)) = (unsigned int)conf;
}

static inline unsigned int pwm_timer_config_get(PwmTimerNum timer) {
    return (*(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_CONFIG_ADDR(timer)));
}

static inline void pwm_timer_threshold_set(PwmTimerNum timer, unsigned int value) {
    *(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_THRESHOLD_ADDR(timer)) = (unsigned int)value;
}

static inline unsigned int pwm_timer_threshold_get(PwmTimerNum timer) {
    return (*(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_THRESHOLD_ADDR(timer)));
}

static inline void pwm_timer_th_channel_set(PwmTimerNum timer, PwmTimerThChannel channel, unsigned int value) {
    *(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_TH_CHANNEL_ADDR(timer, channel)) = (unsigned int)value;
}

static inline unsigned int pwm_timer_th_channel_get(PwmTimerNum timer, PwmTimerThChannel channel) {
    return (*(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_TH_CHANNEL_ADDR(timer, channel)));
}

static inline unsigned int pwm_timer_read_counter(PwmTimerNum nTimer) {
    return (*(volatile unsigned int *)(volatile unsigned int)(PWM_TIMER_COUNTER_ADDR(nTimer)));
}

static inline void pwm_timer_evt_reg_cfg (unsigned int CMD) {
    *(volatile unsigned int *)(volatile unsigned int)(REG_EVENT_CFG) = (unsigned int)CMD;
}

static inline unsigned int pwm_timer_evt_reg_read() {
    return (*(volatile unsigned int *)(volatile unsigned int)(REG_EVENT_CFG));
}

static inline unsigned int pwm_timer_status() {
    return (*(volatile unsigned int *)(volatile unsigned int)(REG_PWM_TIMER_EN));
}

static inline void pwm_timer_en_reg(unsigned int timer_en_val) {
    *(volatile unsigned int *)(volatile unsigned int)(REG_PWM_TIMER_EN) = (unsigned int)timer_en_val;
}


void pwm_timer_en(PwmTimerNum nTimer);
void pwm_timer_all_en();
void pwm_timer_disable(PwmTimerNum nTimer);
void pwm_timer_all_disable();
void pwm_timer_conf(PwmTimerNum nTimer, unsigned int inputSource,
                    unsigned int enableIn, unsigned int FllOrRTC,
                    unsigned int IncThenDec, unsigned int PreScaler);
void pwm_timer_channel_config(PwmTimerNum nTimer, PwmTimerThChannel channel, unsigned int thCh, unsigned int actCh);
void pwm_timer_all_channel_config(PwmTimerNum nTimer, unsigned int thCh0, unsigned int actCh0,
                                  unsigned int thCh1, unsigned int actCh1, unsigned int thCh2,
                                  unsigned int actCh2, unsigned int thCh3, unsigned int actCh3);

#ifdef __cplusplus
}
#endif
#endif /* _HBIRDV2_PWM_H */
