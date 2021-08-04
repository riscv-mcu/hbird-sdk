.. _design_overview:

Overview
========

HummingBird SDK is developed based on Modified **NMSIS**, all the SoCs supported in it
are following the Modified NMSIS-Core Device Templates Guidance.

So this HummingBird SDK can be treated as a software guide for how to use NMSIS.

The build system we use in HummingBird SDK is ``Makefile``, it support both Windows
and Linux, and when we develop HummingBird SDK build system, we keep it simple, so
it make developer can easily port this HummingBird SDK software code to other IDEs.

Click :ref:`overview` to learn more about the HummingBird SDK project overview.

For example, we have ported HummingBird SDK to use Segger embedded Studio and PlatformIO.


Directory Structure
-------------------

To learn deeper about HummingBird SDK project, the directory structure is a good start point.

Below, we will describe our design about the HummingBird SDK directory structure:

Here is the directory structure for this HummingBird SDK.

.. code-block::

    $HBIRD_SDK_ROOT
    ├── application
    │   ├── baremetal
    │   ├── freertos
    │   ├── ucosii
    │   └── rtthread
    ├── Build
    │   ├── gmsl
    │   ├── Makefile.base
    │   ├── Makefile.conf
    │   ├── Makefile.components
    │   ├── Makefile.core
    │   ├── Makefile.files
    │   ├── Makefile.global
    │   ├── Makefile.misc
    │   ├── Makefile.rtos
    │   ├── Makefile.rules
    │   └── Makefile.soc
    ├── doc
    │   ├── build
    │   ├── source
    │   ├── Makefile
    │   └── requirements.txt
    ├── NMSIS
    │   ├── Core
    │   ├── DSP
    │   ├── NN
    │   └── Library
    ├── OS
    │   ├── FreeRTOS
    │   ├── UCOSII
    │   └── RTThread
    ├── SoC
    │   ├── hbird
    │   └── hbirdv2
    ├── test
    │   ├── core
    │   ├── ctest.h
    │   ├── LICENSE
    │   └── README.md
    ├── LICENSE
    ├── Makefile
    ├── NMSIS_VERSION
    ├── README.md
    ├── setup.bat
    └── setup.sh


* **application**

  This directory contains all the application softwares for this HummingBird SDK.

  The application code can be divided into mainly 4 parts, which are:

  - **Baremetal** applications, which will provide baremetal applications without any OS usage, these applications will be placed in *application/baremetal/* folder.
  - **FreeRTOS** applications, which will provide FreeRTOS applications using FreeRTOS RTOS, placed in *application/freertos/* folder.
  - **UCOSII** applications, which will provide UCOSII applications using UCOSII RTOS, placed in *application/ucosii/* folder.
  - **RTThread** applications, which will provide RT-Thread applications using RT-Thread RTOS, placed in *application/rtthread/* folder.

* **SoC**

  This directory contains all the supported SoCs for this HummingBird SDK, the directory name for SoC and its boards should always in lower case.

  Here we mainly support HummingBird processor cores running in Hummingbird FPGA evaluation board, the support package placed in *SoC/hbird/* and *SoC/hbirdv2/*.

  In each SoC's include directory, *hbird_sdk_soc.h* must be provided, and include the soc header file, for example, *SoC/hbird/Common/Include/hbird_sdk_soc.h*.

  In each SoC Board's include directory, *hbird_sdk_hal.h* must be provided, and include the board header file, for example, *SoC/hbird/Board/hbird_eval/Include/hbird_sdk_hal.h*.

* **Build**

  This directory contains the key part of the build system based on Makefile for HummingBird SDK.

* **NMSIS**

  This directory contains the **modified NMSIS** header files, which is widely used in this HummingBird SDK,
  you can check the *NMSIS_VERSION* file to know the current *NMSIS* version used in **HBird-SDK**.

  We will also sync the changes in NMSIS project when it provided a new release.

* **OS**

  This directory provided two RTOS package we suppported which are **FreeRTOS** and **UCOSII**.

* **LICENSE**

  HummingBird SDK license file.

* **NMSIS_VERSION**

  NMSIS Version file. It will show current NMSIS version used in HummingBird SDK.

* **Makefile**

  An external Makefile just for build, run, debug application without cd to any coresponding application directory, such as *application/baremetal/helloworld/*.

* **setup.sh**

  HummingBird SDK environment setup script for **Linux**. You need to create your own `setup_config.sh`.

  .. code-block:: shell

     NUCLEI_TOOL_ROOT=/path/to/your_tool_root

  In the **$NUCLEI_TOOL_ROOT** for **Linux**, you need to have Nuclei RISC-V GNU GCC toolchain and OpenOCD installed as below.

  .. code-block:: console

     $NUCLEI_TOOL_ROOT
     ├── gcc
     │   ├── bin
     │   ├── include
     │   ├── lib
     │   ├── libexec
     │   ├── riscv-nuclei-elf
     │   └── share
     └── openocd
         ├── bin
         ├── contrib
         ├── distro-info
         ├── OpenULINK
         ├── scripts
         └── share

* **setup.bat**

  HummingBird SDK environment setup bat script for **Windows**. You need to create your own `setup_config.bat`.

  .. code-block:: bat

     set NUCLEI_TOOL_ROOT=\path\to\your_tool_root

  In the **%NUCLEI_TOOL_ROOT%** for **Windows**, you need to have Nuclei RISC-V GNU GCC toolchain, necessary Windows build tools and OpenOCD installed as below.

  .. code-block:: console

     %NUCLEI_TOOL_ROOT%
     ├── build-tools
     │   ├── bin
     │   ├── gnu-mcu-eclipse
     │   └── licenses
     ├── gcc
     │   ├── bin
     │   ├── include
     │   ├── lib
     │   ├── libexec
     │   ├── riscv-nuclei-elf
     │   └── share
     └── openocd
         ├── bin
         ├── contrib
         ├── distro-info
         ├── OpenULINK
         ├── scripts
         └── share


Project Components
------------------

This HummingBird SDK project components is list as below:

* :ref:`design_hbird`: How HummingBird RISC-V Processor Core is used in HummingBird SDK
* :ref:`design_soc`: How HummingBird RISC-V processor code based SoC device is supported in HummingBird SDK
* :ref:`design_board`: How HummingBird RISC-V based SoC's Board is supported in HummingBird SDK
* :ref:`design_peripheral`: How to use the peripheral driver in HummingBird SDK
* :ref:`design_rtos`: What RTOSes are supported in HummingBird SDK
* :ref:`design_app`: How to use pre-built applications in HummingBird SDK
