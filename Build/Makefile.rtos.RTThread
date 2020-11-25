C_SRCDIRS += $(HBIRD_SDK_RTOS)/src $(HBIRD_SDK_RTOS)/libcpu/risc-v/nuclei
ifeq ($(RTTHREAD_MSH), 1)
	C_SRCDIRS += $(HBIRD_SDK_RTOS)/components/finsh
endif

ASM_SRCDIRS += $(HBIRD_SDK_RTOS)/libcpu/risc-v/nuclei

INCDIRS += $(HBIRD_SDK_RTOS)/libcpu/risc-v/nuclei \
	$(HBIRD_SDK_RTOS)/include \
	$(HBIRD_SDK_RTOS)/include/libc
ifeq ($(RTTHREAD_MSH), 1)
	INCDIRS += $(HBIRD_SDK_RTOS)/components/finsh
endif
