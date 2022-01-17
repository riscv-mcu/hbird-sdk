.. _changelog:

Changelog
=========

V0.1.3
------

This is release version ``0.1.3`` of HBird SDK.

* Build

    - **Important changes** about build system:

      - The SoC and RTOS related makefiles are moving to its own folder, and controlled By
        **build.mk** inside in in the SoC/<SOC> or OS/<RTOS> folders.
      - Middlware component build system is also available now, you can add you own middleware or library
        into ``Components`` folder, such as ``Components/tjpgd`` or ``Components/fatfs``, and you can include
        this component using make variable ``MIDDLEWARE`` in application Makefile, such as ``MIDDLEWARE := fatfs``,
        or ``MIDDLEWARE := tjpgd fatfs``.
      - Each middleware component folder should create a ``build.mk``, which is used to control
        the component build settings and source code management.
      - An extra ``DOWNLOAD_MODE_STRING`` macro is passed to represent the DOWNLOAD mode string.
    - Change openocd ``--pipe`` option to ``-c "gdb_port pipe; log_output openocd.log"``
    - Remove ``-ex "monitor flash protect 0 0 last off"`` when upload or debug program to avoid error
      when openocd configuration file didn't configure a flash
    - Add ``cleanall`` target in **<HBIRD_SDK_ROOT>/Makefile**, you can clean all the applications
      defined by ``EXTRA_APP_ROOTDIRS`` variable
    - Fix ``size`` target of build system

* SoC

    - hbird and hbirdv2 SoC cores only support e203 and e203e now.

V0.1.2
------

This is official ``0.1.2`` of HummingBird SDK.

Here are the main changes since last release:

* SOC

  - More more newlib stub functions for hbird and hbirdv2 SoC

* doc

  - Update changelog
  - Add rt-thread msh application doc

* application

  - Add rt-thread msh application

* Build

  - Add ``RTTHREAD_MSH`` makefile variable which is valid only for RTThread

* OS

  - Add RT-Thread MSH shell component into RT-Thread source code

* CI

  - Add initial github workflow support for building documentation and sdk

V0.1.1
------

This is official ``0.1.1`` of HummingBird SDK.

Here are the main changes since last release:

* SOC

  - More drivers are added to hbirdv2

* doc

  - Update changelog

* application

  - Fix typos in rt-thread application
  - Update freertos application


V0.1.0
------

This is official release ``0.1.0`` of HummingBird SDK.

Here are the main features of this release:

* HummingBird SDK is developed based on **Nuclei SDK version 0.2.4** release.

* Support Windows and Linux development in command line using Make

* Support HummingBird FPGA evaluation board and HummingBird FPGA DDR-200T evaluation board

  - The **HummingBird FPGA evaluation board** is used to run evaluation FPGA bitstream
    of HummingBird E201, E203, E205 processor cores
  - The **HummingBird FPGA DDR-200T evaluation board** is used to run evaluation FPGA bitstream
    of HummingBird E201, E203, E205 processor cores

* Support different download modes *flashxip*, *ilm*, *flash* for HummingBird FPGA evaluation board

* Support different RTOSes such as FreeRTOS, UCOS-II and RT-Thread

* This *hbird-sdk* is forked from `nuclei-sdk`_ , and adapted for opensource HummingBird RISC-V Core.

.. _nuclei-sdk: https://github.com/nuclei-software/nuclei-sdk
