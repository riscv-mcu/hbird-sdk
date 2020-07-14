#include <stdlib.h>
#include <stdio.h>
#include "ctest.h"
#include "hbird_sdk_soc.h"

#if defined(__FPU_PRESENT) && __FPU_PRESENT > 0

CTEST(fpu, CSR) {
    CTEST_LOG("FCSR 0x%x", __get_FCSR());
    CTEST_LOG("FRM 0x%x", __get_FRM());
    CTEST_LOG("FFLAGS 0x%x", __get_FFLAGS());
    ASSERT_EQUAL(__get_FCSR(), __get_FRM() << 5 | (__get_FFLAGS()));
    rv_csr_t old_fcsr = __get_FCSR();
    rv_csr_t newval = FFLAGS_AE_NX | (FRM_RNDMODE_DYN<<5);
    __set_FCSR(newval);
    ASSERT_EQUAL(__get_FCSR(), newval);
    ASSERT_EQUAL(__get_FRM(), FRM_RNDMODE_DYN);
    ASSERT_EQUAL(__get_FFLAGS(), FFLAGS_AE_NX);
    __set_FCSR(old_fcsr);

    __set_FRM(FRM_RNDMODE_RUP);
    ASSERT_EQUAL(__get_FRM(), FRM_RNDMODE_RUP);
    __set_FFLAGS(FFLAGS_AE_NV);
    ASSERT_EQUAL(__get_FFLAGS(), FFLAGS_AE_NV);
    ASSERT_EQUAL(__get_FCSR(), FFLAGS_AE_NV | (FRM_RNDMODE_RUP << 5));
    __set_FCSR(old_fcsr);
    CTEST_LOG("After operation");
    CTEST_LOG("FCSR 0x%x", __get_FCSR());
    CTEST_LOG("FRM 0x%x", __get_FRM());
    CTEST_LOG("FFLAGS 0x%x", __get_FFLAGS());
}

CTEST(fpu, enable_disable) {
    __disable_FPU();
    ASSERT_EQUAL(__RV_CSR_READ(CSR_MSTATUS) & MSTATUS_FS, 0);
    __enable_FPU();
    ASSERT_EQUAL(__RV_CSR_READ(CSR_MSTATUS) & MSTATUS_FS, MSTATUS_FS);
}

CTEST(fpu, flwfsw) {
    uint32_t data[2] = {0xdeadbeef, 0x12345678};
    uint32_t regf0 = 0x87876767;
    uint32_t temp = 0;
    uint32_t memory[5] = {111, 2222, 33333, 44444, 555555};

    CTEST_LOG("Current f0, data0 is 0x%x, 0x%x", regf0, data[0]);
    __RV_FLW(FREG(0), data, 0);
    CTEST_LOG("Current f0, data0 is 0x%x, 0x%x", regf0, data[0]);
    __RV_FSW(FREG(0), &regf0, 0);
    CTEST_LOG("Current f0, data0 is 0x%x, 0x%x", regf0, data[0]);
    ASSERT_EQUAL(regf0, data[0]);

    __RV_FLW(FREG(0), memory, 0);
    __RV_FSW(FREG(0), &temp, 0);
    ASSERT_EQUAL(memory[0], temp);
    __RV_FLW(FREG(1), memory, 4);
    __RV_FSW(FREG(1), &temp, 0);
    ASSERT_EQUAL(memory[1], temp);
    __RV_FLW(FREG(2), &memory[2], 0);
    __RV_FSW(FREG(2), &temp, 0);
    ASSERT_EQUAL(memory[2], temp);
    __RV_FLW(FREG(4), memory, 4*4);
    __RV_FSW(FREG(4), &temp, 0);
    ASSERT_EQUAL(memory[4], temp);
}

#if __FPU_PRESENT == 2
CTEST(fpu, fldfsd) {
    double data[2] = {1.234, 2.456};
    double regf0[1] = {0.1};
    uint64_t temp = 0;
    uint64_t memory[5] = {111, 2222, 33333, 44444, 555555};

    //CTEST_LOG("Current f0, data0 is %f, %f", (float)regf0[0], (float)data[0]);
    __RV_FLD(FREG(0), data, 0);
    //CTEST_LOG("Current f0, data0 is %f, %f", (float)regf0[0], (float)data[0]);
    __RV_FSD(FREG(0), regf0, 0);
    //CTEST_LOG("Current f0, data0 is %f, %f", (float)regf0[0], (float)data[0]);
    ASSERT_EQUAL(regf0[0], data[0]);

    __RV_FLD(FREG(0), memory, 0);
    __RV_FSD(FREG(0), &temp, 0);
    ASSERT_EQUAL(memory[0], temp);
    __RV_FLD(FREG(1), memory, 8);
    __RV_FSD(FREG(1), &temp, 0);
    ASSERT_EQUAL(memory[1], temp);
    __RV_FLD(FREG(2), &memory[2], 0);
    __RV_FSD(FREG(2), &temp, 0);
    ASSERT_EQUAL(memory[2], temp);
    __RV_FLD(FREG(4), memory, 8*4);
    __RV_FSD(FREG(4), &temp, 0);
    ASSERT_EQUAL(memory[4], temp);
}
#endif

CTEST(fpu, FSTOREFLOAD) {
#if __FPU_PRESENT == 1
    uint32_t temp = 0;
    uint32_t memory[5] = {111, 2222, 33333, 44444, 555555};
#elif __FPU_PRESENT == 2
    uint64_t temp = 0;
    uint64_t memory[5] = {111, 2222, 33333, 44444, 555555};
#endif

    __RV_FLOAD(FREG(0), memory, 0);
    __RV_FSTORE(FREG(0), &temp, 0);
    ASSERT_EQUAL(memory[0], temp);
    __RV_FLOAD(FREG(1), memory, FPREGBYTES);
    __RV_FSTORE(FREG(1), &temp, 0);
    ASSERT_EQUAL(memory[1], temp);
    __RV_FLOAD(FREG(2), &memory[2], 0);
    __RV_FSTORE(FREG(2), &temp, 0);
    ASSERT_EQUAL(memory[2], temp);
    __RV_FLOAD(FREG(4), memory, FPREGBYTES*4);
    __RV_FSTORE(FREG(4), &temp, 0);
    ASSERT_EQUAL(memory[4], temp);
}

CTEST(fpu, fpucontext) {
    SAVE_FPU_CONTEXT();
    RESTORE_FPU_CONTEXT();
}
#endif
