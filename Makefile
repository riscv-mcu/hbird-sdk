PROGRAM :=baremetal/helloworld

.PHONY: __help
__help:
	@echo "Help about Build/Run/Debug an HummingBird SDK Application"
	@echo "make [PROGRAM=$(PROGRAM)]  help"
	@echo "Example:"
	@echo "make PROGRAM=application/baremetal/helloworld all"

VALID_PROGRAM=$(wildcard $(PROGRAM))
VALID_PROGRAM_MAKEFILE=$(wildcard $(PROGRAM)/Makefile)

ifeq ($(VALID_PROGRAM_MAKEFILE), )
APP_PROGRAM=application/$(PROGRAM)
VALID_PROGRAM=$(wildcard $(APP_PROGRAM))
VALID_PROGRAM_MAKEFILE=$(wildcard $(APP_PROGRAM)/Makefile)
ifeq ($(VALID_PROGRAM_MAKEFILE), )
$(error No valid Makefile in $(PROGRAM) directory! please check!)
endif
endif

%:
	make -C $(VALID_PROGRAM) $@
