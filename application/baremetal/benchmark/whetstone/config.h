
#ifndef __CONFIG_H__
#define __CONFIG_H__



#define CFG_SIMU 0

/* Predefined macro __riscv_flen is equal to:
 * 64: if D toolchain is used
 * 32: if F toolchain is used
 */

#if __riscv_flen == 64
	#define SPDP double
	#define Precision "Double"
#else //__riscv_flen == 32
	#define SPDP float
	#define Precision "Single"

	#define atan	atanf
	#define sin 	sinf
	#define cos 	cosf
	#define sqrt	sqrtf
	#define exp 	expf
	#define log 	logf
#endif


#endif
