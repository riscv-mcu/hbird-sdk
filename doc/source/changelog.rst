.. _changelog:

Changelog
=========

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
