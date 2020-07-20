#include "hbirdv2.h"
#include "hbirdv2_pwm.h"


/*
 * Enable the specific timer
 */
void pwm_timer_en(PwmTimerNum nTimer){

    unsigned int ch_en_val = pwm_timer_status();
    ch_en_val |= PWM_TIMER_EN(nTimer);
    pwm_timer_en_reg(ch_en_val);

}

/*
 * Enable all the timers
 */
void pwm_timer_all_en(){
    pwm_timer_en_reg(PWM_TIMER_EN_ALL);
}

/*
 * Disable the specific timer
 */
void pwm_timer_disable(PwmTimerNum nTimer){

    unsigned int ch_en_val = pwm_timer_status();
    ch_en_val &= PWM_TIMER_DISABLE(nTimer);
    pwm_timer_en_reg(ch_en_val);

}

/*
 * Enable all the timers
 */
void pwm_timer_all_disable(){
    pwm_timer_en_reg(PWM_TIMER_DISABLE_ALL);
}

/*
 * PWM timer configuration
 * Arguments:
 *      - nTimer: number of timer
 *      - inputSource: Select counting source
 *                      0-31 gpio
 *                      32-35 out of timer 0
 *                      ...
 *                      44-47 out of timer 3
 *      - enableIn: count rules
 *                      ADV_TIMER_INMODE_AO         0x0 //event at each clock cycle
 *                      ADV_TIMER_INMODE_IN0        0x1 //event if input signal is 0
 *                      ADV_TIMER_INMODE_IN1        0x2 //event if input signal is 1
 *                      ADV_TIMER_INMODE_RISE       0x3 //event on input signal rising edge
 *                      ADV_TIMER_INMODE_FALL       0x4 //event on input signal falling edge
 *                      ADV_TIMER_INMODE_EDGE       0x5 //event on input signal rising or falling edge
 *                      ADV_TIMER_INMODE_ARM_RISE   0x6 //event on input signal rising edge when armed
 *                      ADV_TIMER_INMODE_ARM_FALL   0x7 //event on input signal falling edge when armed
 *      - FllorRTC:
 *                      ADV_TIMER_USEREF            0x1
 *                      ADV_TIMER_USESIG            0x0
 *      - IncThenDec: action when reaching the TH:
 *                      ADV_TIMER_SAW:     /|/|/| (SAW)
 *                      ADV_TIMER_NOSAW:   /\/\/\ (NOSAW)
 *      - PreScaler
 */
void pwm_timer_conf(PwmTimerNum nTimer, unsigned int inputSource, unsigned int enableIn, unsigned int FllOrRTC, unsigned int IncThenDec, unsigned int PreScaler){
    pwm_timer timer;
    timer.timerConf.SelectInputSource = inputSource;
    timer.timerConf.InputEnableIn = enableIn;
    timer.timerConf.FllOrRTC = FllOrRTC;
    timer.timerConf.IncThenDec = IncThenDec;
    timer.timerConf.PreScaler = PreScaler;
    pwm_timer_config(nTimer, timer.Raw);              // Write the configs, set start bit
}

/*
 *  Configuration the 1 of 16 PWM channels:
 *  Arguments:
 *      - nTimer:   number of timer
 *      - channel:  number of channel
 *      - thCh:     threshold
 *      - actCh:    action of channel
 *                    ADV_TIMER_OP_SET    0       //   	000: Set
 *                    ADV_TIMER_OP_TOGRST 1       //   	001: Toggle then next is Clear
 *                    ADV_TIMER_OP_SETRST 2       //   	010: Set then Clear
 *                    ADV_TIMER_OP_TOG    3       //   	011: Toggle
 *                    ADV_TIMER_OP_RST    4       //   	100: Clear
 *                    ADV_TIMER_OP_TOGSET 5       //   	101: Toggle then next is Set
 *                    ADV_TIMER_OP_RSTSET 6       //   	110: Clear then Set
 *
 */
void pwm_timer_channel_config(PwmTimerNum nTimer, PwmTimerThChannel channel, unsigned int thCh, unsigned int actCh){
    pwm_timer timer;
    timer.ch_ThConfig.chThreshold = thCh;
    timer.ch_ThConfig.chAction = actCh;
    pwm_timer_th_channel_set(nTimer, channel, timer.Raw);
}

/*
 *  Configuration of all 4 channels of 1 timer:
 *  Arguments:
 *      - nTimer:   number of timer
 *      - thCh(x):  threshold
 *      - actCh(x): action of channel
 *                    ADV_TIMER_OP_SET    0       //   	000: Set
 *                    ADV_TIMER_OP_TOGRST 1       //   	001: Toggle then next is Clear
 *                    ADV_TIMER_OP_SETRST 2       //   	010: Set then Clear
 *                    ADV_TIMER_OP_TOG    3       //   	011: Toggle
 *                    ADV_TIMER_OP_RST    4       //   	100: Clear
 *                    ADV_TIMER_OP_TOGSET 5       //   	101: Toggle then next is Set
 *                    ADV_TIMER_OP_RSTSET 6       //   	110: Clear then Set
 *
 */
void pwm_timer_all_channel_config(PwmTimerNum nTimer, unsigned int thCh0, unsigned int actCh0,
                                                      unsigned int thCh1, unsigned int actCh1,
                                                      unsigned int thCh2, unsigned int actCh2,
                                                      unsigned int thCh3, unsigned int actCh3){

    pwm_timer_channel_config(nTimer, PWM_TIMER_TH_CHANNEL0, thCh0, actCh0);
    pwm_timer_channel_config(nTimer, PWM_TIMER_TH_CHANNEL1, thCh1, actCh1);
    pwm_timer_channel_config(nTimer, PWM_TIMER_TH_CHANNEL2, thCh2, actCh2);
    pwm_timer_channel_config(nTimer, PWM_TIMER_TH_CHANNEL3, thCh3, actCh3);
}
