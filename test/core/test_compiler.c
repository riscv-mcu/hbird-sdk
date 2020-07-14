#include <stdlib.h>
#include "ctest.h"
#include "hbird_sdk_soc.h"

CTEST(compiler, unaligned_read16) {
    uint32_t data = 0x12345678;
    unsigned long pdata = (unsigned long)(&data);
    __RWMB();
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)pdata), 0x5678);
    __RWMB();
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)(pdata + 1)), 0x3456);
    __RWMB();
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)(pdata + 2)), 0x1234);
}

CTEST(compiler, unaligned_write16) {
    uint32_t data = 0x12345678;
    unsigned long pdata = (unsigned long)(&data);
    __UNALIGNED_UINT16_WRITE((void *)pdata, 0xABCD);
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)pdata), 0xABCD);
    __UNALIGNED_UINT16_WRITE((void *)(pdata + 1), 0xCDEF);
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)(pdata + 1)), 0xCDEF);
    __UNALIGNED_UINT16_WRITE((void *)(pdata + 2), 0xEF00);
    ASSERT_EQUAL(__UNALIGNED_UINT16_READ((void *)(pdata + 2)), 0xEF00);
}

CTEST(compiler, unaligned_read32) {
    uint32_t data[2] = {0x12345678, 0xABCDEF01};
    unsigned long pdata = (unsigned long)(&data);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)pdata), 0x12345678);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 1)), 0x01123456);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 2)), 0xEF011234);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 3)), 0xCDEF0112);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 4)), 0xABCDEF01);
}

CTEST(compiler, unaligned_write32) {
    uint32_t data[2] = {0x12345678, 0xABCDEF01};
    unsigned long pdata = (unsigned long)(&data);
    __UNALIGNED_UINT32_WRITE((void *)pdata, 0xDEADBEEF);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)pdata), 0xDEADBEEF);
    __UNALIGNED_UINT32_WRITE((void *)(pdata + 1), 0xCDEF1234);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 1)), 0xCDEF1234);
    __UNALIGNED_UINT32_WRITE((void *)(pdata + 2), 0xEF007678);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 2)), 0xEF007678);
    __UNALIGNED_UINT32_WRITE((void *)(pdata + 3), 0x89282678);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 3)), 0x89282678);
    __UNALIGNED_UINT32_WRITE((void *)(pdata + 4), 0xDEADBEAF);
    ASSERT_EQUAL(__UNALIGNED_UINT32_READ((void *)(pdata + 4)), 0xDEADBEAF);
}

CTEST(compiler, compiler_barrier) {
    __COMPILER_BARRIER();
}

CTEST(compiler, usually) {
    int32_t test = 12;
    ASSERT_EQUAL(__USUALLY(test > 0), 1);
    test = -1;
    ASSERT_EQUAL(__USUALLY(test > 0), 0);
}

CTEST(compiler, rarelly) {
    int32_t test = 12;
    ASSERT_EQUAL(__RARELY(test > 0), 1);
    test = -1;
    ASSERT_EQUAL(__RARELY(test > 0), 0);
}

CTEST(compiler, packed_struct) {
    typedef __PACKED_STRUCT al1st {
        uint64_t a;
        uint8_t b;
        uint16_t c;
        uint32_t d;
        uint8_t e;
    } AL1ST;
    ASSERT_EQUAL(sizeof(AL1ST), 16);
}

CTEST(compiler, packed_union) {
    typedef __PACKED_UNION al1un {
        uint8_t a[3];
        uint16_t b;
    } AL1UN;
    ASSERT_EQUAL(sizeof(AL1UN), 3);
}

CTEST(compiler, aligned) {
    uint32_t __ALIGNED(2) data_aligned1;
    uint32_t __ALIGNED(16) data[4];
    uint32_t __ALIGNED(64) data2[4];
    unsigned long p_data = (unsigned long)(&data_aligned1);
    CTEST_LOG("Aligned 2 Byte Data address 0x%x", p_data);
    ASSERT_EQUAL(p_data & (1 - 1), 0);
    p_data = (unsigned long)(&data[0]);
    CTEST_LOG("Aligned 16 Byte Data address 0x%x", p_data);
    ASSERT_EQUAL(p_data & (16 - 1), 0);
    p_data = (unsigned long)(&data2[0]);
    CTEST_LOG("Aligned 64 Byte Data address 0x%x", p_data);
    ASSERT_EQUAL(p_data & (64 - 1), 0);
}

CTEST(compiler, val2fld) {
    #define TEST_Pos    1
    #define TEST_Msk    (0xF<<TEST_Pos)
    uint32_t value = 0x123;

    ASSERT_EQUAL(_VAL2FLD(TEST, value), 0x3<<1);
}

CTEST(compiler, fld2val) {
    #define TEST_Pos    1
    #define TEST_Msk    (0xF<<TEST_Pos)
    uint32_t value = 0x13;

    ASSERT_EQUAL(_FLD2VAL(TEST, value), 0x9);
}


