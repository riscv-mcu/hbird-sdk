
#ifndef __REF_COMMON_H__
#define __REF_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <riscv_math.h>
#include <stdint.h>
#include <stdlib.h>

  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    REF_Q7 = 0,
    REF_Q15,
    REF_Q31,
    REF_F32,
  } dataType;


#ifndef FLT_MAX
#define FLT_MAX  3.40282347e+38F
#endif

#ifndef DBL_MAX
#define DBL_MAX  1.79769313486231571e+308
#endif

#ifndef FLT_MIN
#define FLT_MIN  1.175494351e-38F
#endif

#ifndef DBL_MIN
#define DBL_MIN  2.22507385850720138e-308
#endif

#define SCHAR_MIN (-128)
    /* mimimum value for an object of type signed char */
#define SCHAR_MAX 127
    /* maximum value for an object of type signed char */
#define UCHAR_MAX 255
    /* maximum value for an object of type unsigned char */
#define SHRT_MIN  (-0x8000)
    /* minimum value for an object of type short int */
#define SHRT_MAX  0x7fff
    /* maximum value for an object of type short int */
#define USHRT_MAX 65535
    /* maximum value for an object of type unsigned short int */
#define INT_MIN   (~0x7fffffff)  /* -2147483648 and 0x80000000 are unsigned */
    /* minimum value for an object of type int */
#define INT_MAX   0x7fffffff
    /* maximum value for an object of type int */
#define UINT_MAX  0xffffffffU
    /* maximum value for an object of type unsigned int */
#define LONG_MIN  (~0x7fffffffL)
    /* minimum value for an object of type long int */
#define LONG_MAX  0x7fffffffL
    /* maximum value for an object of type long int */
#define ULONG_MAX 0xffffffffUL
    /* maximum value for an object of type unsigned long int */


/*
 * Helper Functions
 */
q31_t ref_sat_n(q31_t num, uint32_t bits);

q31_t ref_sat_q31(q63_t num);

q15_t ref_sat_q15(q31_t num);

q7_t ref_sat_q7(q15_t num);

float32_t ref_pow(float32_t a, uint32_t b);

float32_t ref_detrm(float32_t *pSrc, float32_t *temp, uint32_t size);

void ref_cofact(float32_t *pSrc, float32_t *pDst, float32_t *temp,
                uint32_t size);

float64_t ref_detrm64(float64_t *pSrc, float64_t *temp, uint32_t size);

void ref_cofact64(float64_t *pSrc, float64_t *pDst, float64_t *temp,
                  uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /** __REF_COMMON_H__  */
