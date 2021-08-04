##### Put your SoC build configurations below #####

BOARD ?= ddr200t
CORE ?= e203

HBIRD_SDK_SOC_BOARD := $(HBIRD_SDK_SOC)/Board/$(BOARD)
HBIRD_SDK_SOC_COMMON := $(HBIRD_SDK_SOC)/Common

OPENOCD_CFG ?= $(HBIRD_SDK_SOC_BOARD)/openocd_hbirdv2.cfg
LINKER_SCRIPT ?= $(HBIRD_SDK_SOC_BOARD)/Source/GCC/gcc_hbirdv2_$(DOWNLOAD).ld

# File existence check for OPENOCD_CFG and LINKER_SCRIPT
ifeq ($(wildcard $(OPENOCD_CFG)),)
$(error The openocd configuration file $(OPENOCD_CFG) for $(SOC) doesn't exist, please check!)
endif
ifeq ($(wildcard $(LINKER_SCRIPT)),)
$(error The link script file $(LINKER_SCRIPT) for $(SOC) doesn't exist, please check!)
endif

# Set RISCV_ARCH and RISCV_ABI
CORE_UPPER := $(call uc, $(CORE))
include $(HBIRD_SDK_BUILD)/Makefile.core
# you can override SUPPORTED_CORES defined in Makefile.core to limit the COREs used in this SoC
# eg. override SUPPORTED_CORES := n305 n307

CORE_ARCH_ABI := $($(CORE_UPPER)_CORE_ARCH_ABI)
# Check whether CORE is in SUPPORTED_CORES
ifeq ($(filter $(CORE), $(SUPPORTED_CORES)),)
$(error Here we only support these cores: $(SUPPORTED_CORES))
endif
# Check whether CORE_ARCH_ABI is presented for CORE
ifneq ($(words $(CORE_ARCH_ABI)), 2)
$(error There is no coresponding ARCH_ABI setting for CORE $(CORE), please check Makefile.core)
endif

RISCV_ARCH ?= $(word 1, $(CORE_ARCH_ABI))
RISCV_ABI ?= $(word 2, $(CORE_ARCH_ABI))

##### Put your Source code Management configurations below #####

INCDIRS += $(HBIRD_SDK_SOC_COMMON)/Include

C_SRCDIRS += $(HBIRD_SDK_SOC_COMMON)/Source $(HBIRD_SDK_SOC_COMMON)/Source/Drivers \
		$(HBIRD_SDK_SOC_COMMON)/Source/Stubs

ASM_SRCS += $(HBIRD_SDK_SOC_COMMON)/Source/GCC/startup_hbirdv2.S \
		$(HBIRD_SDK_SOC_COMMON)/Source/GCC/intexc_hbirdv2.S

# Add extra board related source files and header files
VALID_HBIRD_SDK_SOC_BOARD := $(wildcard $(HBIRD_SDK_SOC_BOARD))
ifneq ($(VALID_HBIRD_SDK_SOC_BOARD),)
INCDIRS += $(VALID_HBIRD_SDK_SOC_BOARD)/Include
C_SRCDIRS += $(VALID_HBIRD_SDK_SOC_BOARD)/Source
endif
