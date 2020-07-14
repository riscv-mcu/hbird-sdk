#ifndef CORE_PORTME_H
#define CORE_PORTME_H

#include "hbird_sdk_soc.h"
//Bob: put some macro here such that the IDE SDK do not need to specify the macro specially
//#define FLAGS_STR "-O3 -fno-common -funroll-loops -finline-functions  -falign-functions=4 -falign-jumps=4 -falign-loops=4 -funswitch-loops -fpeel-loops -fgcse-sm -fgcse-las"
//#define FLAGS_STR "-O2 -fno-common -funroll-loops -finline-functions -falign-functions=4 -falign-jumps=4 -falign-loops=4"
#ifndef FLAGS_STR
    #define FLAGS_STR "-O2 -funroll-all-loops -finline-limit=600 -ftree-dominator-opts -fno-if-conversion2 -fselective-scheduling -fno-code-hoisting -fno-common -funroll-loops -finline-functions -falign-functions=4 -falign-jumps=4 -falign-loops=4"
#endif

#ifndef PERFORMANCE_RUN
#define PERFORMANCE_RUN 1
#endif

#ifndef ITERATIONS
#define ITERATIONS 100
#endif

#ifndef FESDK_CORE_PORTME_H
#define FESDK_CORE_PORTME_H

#include <stdint.h>
#include <stddef.h>

#define HAS_FLOAT 1
#define HAS_TIME_H 1
#define USE_CLOCK 1
#define HAS_STDIO 1
#define HAS_PRINTF 1
#define SEED_METHOD SEED_VOLATILE
#define CORE_TICKS uint64_t
#define ee_u8 uint8_t
#define ee_u16 uint16_t
#if defined(__riscv_xlen) && (__riscv_xlen == 64)
// Trick used for RISC-V 64-bit coremark:
// Defining ee_u32 to be signed int instead of unsigned int,
// as 32-bit values on a 64-bit RISC-V must always be signed extended,
// so this avoids some useless sign extension shifts while still giving the correct result
// See https://forums.sifive.com/t/how-can-i-repeat-the-coremark-score/1947/3
#define ee_u32 int32_t
#else
#define ee_u32 uint32_t
#endif
#define ee_s16 int16_t
#define ee_s32 int32_t
#define ee_ptr_int uintptr_t
#define ee_size_t size_t
#define COMPILER_FLAGS FLAGS_STR

#define align_mem(x) (void *)(((ee_ptr_int)(x) + sizeof(ee_u32) - 1) & -sizeof(ee_u32))

#ifdef __GNUC__
# define COMPILER_VERSION "GCC"__VERSION__
#else
# error
#endif

#define MEM_METHOD MEM_STACK
#define MEM_LOCATION "STACK"

#define MAIN_HAS_NOARGC 0
#define MAIN_HAS_NORETURN 0

#define MULTITHREAD 1
#define USE_PTHREAD 0
#define USE_FORK 0
#define USE_SOCKET 0

#define default_num_contexts MULTITHREAD

typedef int core_portable;
static void portable_init(core_portable *p, int *argc, char *argv[]) {}
static void portable_fini(core_portable *p) {}

#if !defined(PROFILE_RUN) && !defined(PERFORMANCE_RUN) && !defined(VALIDATION_RUN)
#if (TOTAL_DATA_SIZE==1200)
#define PROFILE_RUN 1
#elif (TOTAL_DATA_SIZE==2000)
#define PERFORMANCE_RUN 1
#else
#define VALIDATION_RUN 1
#endif
#endif

#endif

#endif
