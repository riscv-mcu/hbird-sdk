TARGET = demo_dsp

HBIRD_SDK_ROOT = ../../..
HBIRD_SDK_NMSIS_ROOT ?= $(HBIRD_SDK_ROOT)/NMSIS

SRCDIRS = .

INCDIRS = . $(HBIRD_SDK_NMSIS_ROOT)/DSP/Include

LIBDIRS = $(HBIRD_SDK_NMSIS_ROOT)/Library/DSP/GCC

COMMON_FLAGS :=
PFLOAT ?= 1

# Currently for HummingBird RISC-V Core
# RISC-V DSP instruction is not supported,
# so we can only use library without dsp instructions
$(warning "Use and link with RISC-V DSP disabled library")
COMMON_FLAGS += -DRISCV_ALIGN_ACCESS
LDLIBS = -lnmsis_dsp_$(RISCV_ARCH) -lm

include $(HBIRD_SDK_ROOT)/Build/Makefile.base
