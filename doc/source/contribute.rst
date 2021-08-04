.. _contribute:

Contributing
============

Contributing to HummingBird SDK project is always welcome.

You can always do a lot of things to help HummingBird SDK project
improve and grow stronger.

* :ref:`contribute_portsoc`
* :ref:`contribute_submit_issue`
* :ref:`contribute_submit_pr`

.. _contribute_portsoc:

Port your HummingBird SoC into HummingBird SDK
----------------------------------------------

If you want to port you HummingBird RISC-V Processor Core based Board to HummingBird SDK,
you need to follow these steps:

Assume your SoC name is ``ncstar``, based on HummingBird RISC-V core **e203**, and **RISCV_ARCH**
is ``rv32imafc``, **RISCV_ABI** is ``ilp32f``, and you made a new board called ``ncstar_eval``,
and this SoC only support **FlashXIP** download mode.

Make sure the SoC name and Board name used in this HummingBird SDK is all in lowercase.

1. Create a folder named ``ncstar`` under **SoC** directory.

   * Create folder named ``Board`` and ``Common`` under ``ncstar``
   * Create directory structure under ``ncstar/Common`` like below:

     .. code-block:: text

        <ncstar/Common>
        ├── Include
        │   ├── peripheral_or_device_headers.h
        │   ├── ......
        │   ├── ncstar.h
        │   ├── hbird_sdk_soc.h
        │   └── system_ncstar.h
        └── Source
            ├── Drivers
            │   ├── peripheral_or_device_sources.c
            │   └── ......
            ├── GCC
            │   ├── intexc_ncstar.S
            │   └── startup_ncstar.S
            ├── Stubs
            │   ├── clock_getres.c
            │   ├── clock_gettime.c
            │   ├── clock_settime.c
            │   ├── close.c
            │   ├── execve.c
            │   ├── exit.c
            │   ├── fork.c
            │   ├── fstat.c
            │   ├── getpid.c
            │   ├── gettimeofday.c
            │   ├── isatty.c
            │   ├── kill.c
            │   ├── link.c
            │   ├── lseek.c
            │   ├── open.c
            │   ├── read.c
            │   ├── sbrk.c
            │   ├── stat.c
            │   ├── times.c
            │   ├── unlink.c
            │   ├── wait.c
            │   └── write.c
            ├── ncstar_soc.c
            └── system_ncstar.c


     .. note::

         * The folder names must be exactly the same as the directory structure showed
         * **peripheral_or_device_sources.c** means the SoC peripheral driver source code files,
           such as uart, gpio, i2c, spi driver sources, usually get from the SoC firmware library,
           it should be placed in **Drivers** folder.
         * **peripheral_or_device_headers.h** means the SoC peripheral driver header files,
           such  as uart, gpio, i2c, spi driver headers, usually get from the SoC firmware library,
           it should be placed in **Include** folder.
         * The **Stubs** folder contains the stub code files for newlib c library porting code,
           mainly ``_write``, ``_read``, ``_sbrk`` stub function
         * The **GCC** folder contains *startup* and *exeception/interrupt* assemble code,
           if your board share the same linker script files, you can also put link script files here,
           the linker script files name rules can refer to previously supported *hbirdv2* SoC.
         * The **hbird_sdk_soc.h** file is very important, it is a HummingBird RISC-V SoC Header file used
           by common application which can run accoss different SoC, it should include the SoC device
           header file ``ncstar.h``

   * Create directory structure under ``ncstar/Board`` like below:

     .. code-block:: text

        <ncstar/Board>
        └── ncstar_eval
            ├── Include
            │   ├── ncstar_eval.h
            │   └── hbird_sdk_hal.h
            ├── openocd_ncstar.cfg
            └── Source
                ├── GCC
                │   └── gcc_ncstar_flashxip.ld
                └── ncstar_eval.c

     .. note::

         * The **ncstar_eval** is the board folder name, if you have a new board,
           you can create a new folder in the same level
         * **Include** folder contains the board related header files
         * **Source** folder contains the board related source files
         * **GCC** folder is optional, if your linker script for the board is different
           to the SoC, you need to put your linker script here
         * **openocd_ncstar.cfg** file is the board related openocd debug configuration file
         * **ncstar_eval.h** file contains board related definition or APIs and also include
           the **SoC** header file, you can refer to previously supported board such as ``hbird_eval``
         * **hbird_sdk_hal.h** is very important, it includes the **ncstar_eval.h** header file.
           This file is used in application as entry header file to access board and SoC resources.


2. Create Makefiles related to ``ncstar`` in :ref:`HummingBird SDK build system <develop_buildsystem>`

   * Create **SoC/ncstar/build.mk**, the file content should be like this:

     .. code-block:: Makefile

        ##### Put your SoC build configurations below #####

        BOARD ?= ncstar_eval

        # override DOWNLOAD and CORE variable for NCSTAR SoC
        # even though it was set with a command argument
        override CORE := n307
        override DOWNLOAD := flashxip

        HBIRD_SDK_SOC_BOARD := $(HBIRD_SDK_SOC)/Board/$(BOARD)
        HBIRD_SDK_SOC_COMMON := $(HBIRD_SDK_SOC)/Common

        #no ilm on NCSTAR SoC
        LINKER_SCRIPT ?= $(HBIRD_SDK_SOC_BOARD)/Source/GCC/gcc_ncstar_flashxip.ld
        OPENOCD_CFG ?= $(HBIRD_SDK_SOC_BOARD)/openocd_ncstar.cfg

        RISCV_ARCH ?= rv32imac
        RISCV_ABI ?= ilp32

        ##### Put your Source code Management configurations below #####

        INCDIRS += $(HBIRD_SDK_SOC_COMMON)/Include

        C_SRCDIRS += $(HBIRD_SDK_SOC_COMMON)/Source \
                     $(HBIRD_SDK_SOC_COMMON)/Source/Drivers \
                     $(HBIRD_SDK_SOC_COMMON)/Source/Stubs

        ASM_SRCS += $(HBIRD_SDK_SOC_COMMON)/Source/GCC/startup_ncstar.S \
                     $(HBIRD_SDK_SOC_COMMON)/Source/GCC/intexc_ncstar.S

        # Add extra board related source files and header files
        VALID_HBIRD_SDK_SOC_BOARD := $(wildcard $(HBIRD_SDK_SOC_BOARD))
        ifneq ($(VALID_HBIRD_SDK_SOC_BOARD),)
        INCDIRS += $(VALID_HBIRD_SDK_SOC_BOARD)/Include
        C_SRCDIRS += $(VALID_HBIRD_SDK_SOC_BOARD)/Source
        endif


3. If you have setup the source code and build system correctly, then you can test
   your SoC using the common applications, e.g.

   .. code-block:: shell

      # Test helloworld application for ncstar_eval board
      ## cd to helloworld application directory
      cd application/baremetal/helloworld
      ## clean and build helloworld application for ncstar_eval board
      make SOC=ncstar BOARD=ncstar_eval clean all
      ## connect your board to PC and install jtag driver, open UART terminal
      ## set baudrate to 115200bps and then upload the built application
      ## to the ncstar_eval board using openocd, and you can check the
      ## run messsage in UART terminal
      make SOC=ncstar BOARD=ncstar_eval upload


.. note::

   * You can always refer to previously supported SoCs for reference,
     such as the ``hbird`` SoC.
   * The ``hbird`` SoC is a FPGA based evaluation platform, it have
     ``ilm`` and ``dlm``, so it support three
     :ref:`download modes <develop_buildsystem_var_download>`
   * The **hbird_sdk_soc.h** must be created in SoC include directory, it must
     include the device header file <device>.h and SoC firmware library header files.
   * The **hbird_sdk_hal.h** must be created in Board include directory, it must
     include **hbird_sdk_soc.h** and board related header files.


.. _contribute_submit_issue:

Submit your issue
-----------------

If you find any issue related to HummingBird SDK project,
you can open an issue in https://github.com/riscv-mcu/hbird-sdk/issues


.. _contribute_submit_pr:

Submit your pull request
------------------------

If you want to contribute your code to HummingBird SDK project,
you can open an pull request in https://github.com/riscv-mcu/hbird-sdk/pulls

Regarding to code style, please refer to :ref:`develop_codestyle`.

.. _contribute_git_guide:

Git commit guide
----------------

If you want to contribute your code, make sure you follow the guidance
of git commit, see here https://chris.beams.io/posts/git-commit/ for details

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 80 characters or less
* Refer github issues and pull requests liberally using ``#``
* Write the commit message with an category name and colon:

    - soc: changes related to soc
    - board: changes related to board support packages
    - nmsis: changes related to NMSIS
    - build: changes releated to build system
    - library: changes related to libraries
    - rtos: changes related to rtoses
    - test: changes related to test cases
    - doc: changes related to documentation
    - ci: changes related to ci environment
    - application: changes related to applications
    - misc: changes not categorized
    - env: changes related to environment

