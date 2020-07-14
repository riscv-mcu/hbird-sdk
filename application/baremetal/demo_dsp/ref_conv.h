
#ifndef __REF_CONV_H__
#define __REF_CONV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <riscv_math.h>
#include <ref_common.h>

void ref_conv_f32(float32_t *pSrcA, uint32_t srcALen, float32_t *pSrcB,
                  uint32_t srcBLen, float32_t *pDst);

riscv_status ref_conv_partial_f32(float32_t *pSrcA, uint32_t srcALen,
                                  float32_t *pSrcB, uint32_t srcBLen,
                                  float32_t *pDst, uint32_t firstIndex,
                                  uint32_t numPoints);

void ref_conv_q31(q31_t *pSrcA, uint32_t srcALen, q31_t *pSrcB,
                  uint32_t srcBLen, q31_t *pDst);

void ref_conv_fast_q31(q31_t *pSrcA, uint32_t srcALen, q31_t *pSrcB,
                       uint32_t srcBLen, q31_t *pDst);

riscv_status ref_conv_partial_q31(q31_t *pSrcA, uint32_t srcALen, q31_t *pSrcB,
                                  uint32_t srcBLen, q31_t *pDst,
                                  uint32_t firstIndex, uint32_t numPoints);

riscv_status ref_conv_partial_fast_q31(q31_t *pSrcA, uint32_t srcALen,
                                       q31_t *pSrcB, uint32_t srcBLen,
                                       q31_t *pDst, uint32_t firstIndex,
                                       uint32_t numPoints);

void ref_conv_q15(q15_t *pSrcA, uint32_t srcALen, q15_t *pSrcB,
                  uint32_t srcBLen, q15_t *pDst);

#define ref_conv_opt_q15(pSrcA, srcALen, pSrcB, srcBLen, pDst, pScratch1,      \
                         pScratch2)                                            \
    ref_conv_q15(pSrcA, srcALen, pSrcB, srcBLen, pDst)

void ref_conv_fast_q15(q15_t *pSrcA, uint32_t srcALen, q15_t *pSrcB,
                       uint32_t srcBLen, q15_t *pDst);

void ref_conv_fast_opt_q15(q15_t *pSrcA, uint32_t srcALen, q15_t *pSrcB,
                           uint32_t srcBLen, q15_t *pDst, q15_t *pScratch1,
                           q15_t *pScratch2);

riscv_status ref_conv_partial_q15(q15_t *pSrcA, uint32_t srcALen, q15_t *pSrcB,
                                  uint32_t srcBLen, q15_t *pDst,
                                  uint32_t firstIndex, uint32_t numPoints);

#define ref_conv_partial_opt_q15(pSrcA, srcALen, pSrcB, srcBLen, pDst,         \
                                 firstIndex, numPoints, pScratch1, pScratch2)  \
    ref_conv_partial_q15(pSrcA, srcALen, pSrcB, srcBLen, pDst, firstIndex,     \
                         numPoints)

riscv_status ref_conv_partial_fast_q15(q15_t *pSrcA, uint32_t srcALen,
                                       q15_t *pSrcB, uint32_t srcBLen,
                                       q15_t *pDst, uint32_t firstIndex,
                                       uint32_t numPoints);

riscv_status ref_conv_partial_fast_opt_q15(q15_t *pSrcA, uint32_t srcALen,
                                           q15_t *pSrcB, uint32_t srcBLen,
                                           q15_t *pDst, uint32_t firstIndex,
                                           uint32_t numPoints, q15_t *pScratch1,
                                           q15_t *pScratch2);

void ref_conv_q7(q7_t *pSrcA, uint32_t srcALen, q7_t *pSrcB, uint32_t srcBLen,
                 q7_t *pDst);

#define ref_conv_opt_q7(pSrcA, srcALen, pSrcB, srcBLen, pDst, pScratch1,       \
                        pScratch2)                                             \
    ref_conv_q7(pSrcA, srcALen, pSrcB, srcBLen, pDst)

riscv_status ref_conv_partial_q7(q7_t *pSrcA, uint32_t srcALen, q7_t *pSrcB,
                                 uint32_t srcBLen, q7_t *pDst,
                                 uint32_t firstIndex, uint32_t numPoints);

#define ref_conv_partial_opt_q7(pSrcA, srcALen, pSrcB, srcBLen, pDst,          \
                                firstIndex, numPoints, pScratch1, pScratch2)   \
    ref_conv_partial_q7(pSrcA, srcALen, pSrcB, srcBLen, pDst, firstIndex,      \
                        numPoints)

#ifdef __cplusplus
}
#endif

#endif /** __REF_CONV_H__  */
