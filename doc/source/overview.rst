.. _overview:

Overview
========

.. _overview_intro:

Introduction
------------

The **HummingBird RISC-V Software Development Kit (SDK)** is an open-source software platform to
speed up the software development of SoCs based on HummingBird RISC-V Processor Cores.

This HummingBird SDK is built based on the modified version of |NMSIS|, user can access all the APIs provided
by |NMSIS| and also the APIs that provided by HummingBird SDK which mainly for on-board
peripherals access such as GPIO, UART, SPI and I2C, etc.

HummingBird SDK provides a good start base for embedded developers which will help them simplify
software development and improve time-to-market through well-designed software framework.

.. note::

   * The **NMSIS** used in this HummingBird SDK is **modified** for HummingBird RISC-V Core,
     which is not compatiable with **Nuclei NMSIS**, take care.
   * HummingBird SDK is developed based on `Nuclei SDK`_ 0.2.4 release, and will diverge in future.
   * To get a pdf version of this documentation, please click `HBird SDK Document`_

.. _overview_design_arch:

Design and Architecture
-----------------------

The HummingBird SDK general design and architecture are shown in the block diagram as below.

.. _figure_overview_1:

.. figure:: /asserts/images/hbird_sdk_diagram.png
   :width: 80 %
   :align: center
   :alt: HummingBird SDK Design and Architecture Diagram

   HummingBird SDK Design and Architecture Diagram

As :ref:`figure_overview_1` shown, The HummingBird SDK provides the following features:

* :ref:`HummingBird RISC-V Core API<nmsis_core>` service is built on top of a modified version of |NMSIS|,
  so silicon vendors of HummingBird RISC-V processors can easily port their SoCs to HummingBird SDK, and
  quickly evaluate software on their SoC.
* **NMSIS-NN** and **NMSIS-DSP** library can be also used in HummingBird SDK, and the prebuilt libraries are
  included in **NMSIS/Library** folder of HummingBird SDK.
* Mainly support two HummingBird RISC-V Processor based SoCs, :ref:`design_soc_hbird`.
* Provided realtime operation system service via :ref:`design_rtos_freertos`, :ref:`design_rtos_ucosii` and
  :ref:`design_rtos_rtthread`
* Provided bare-metal service for embedded system software beginners and resource-limited use-cases.
* Currently HummingBird SDK didn't define any common device APIs to access GPIO/I2C/SPI/UART devices, it still
  relied on the device/peripheral APIs from firmware libraries from various silicon vendors.
* Applications are logically seperated into three parts:

  - **General applications for all HummingBird RISC-V Processors**: In the HummingBird SDK software code, the applications provided
    are all general applications which can run on all HummingBird RISC-V Processors, with basic UART service to provide ``printf`` function.
  - **HummingBird SoC applications**: These applications are not included in the HummingBird SDK software code, it is
    *maintained seperately*, it will use resource from HummingBird SoC and its evaluation boards to develop applications, which will
    not be compatiable with different boards.

.. _overview_getstarted:

Get Started
-----------

Please refer to :ref:`quickstart` to get started to take a try with HummingBird SDK.

.. _overview_contribute:

Contributing
------------

Contributing to HummingBird SDK is welcomed, if you have any issue or pull request
want to open, you can take a look at :ref:`contribute` section.

.. _overview_copyright:

Copyright
---------

Copyright (c) 2019 - Present, Nuclei System Technology. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the Nuclei System Technology., nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. NY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.. _overview_license:

License
-------

HummingBird SDK is an opensource project licensed by :ref:`Apache License 2.0 <license>`.

.. _Nuclei SDK: https://github.com/nuclei-software/nuclei-sdk
.. _HBird SDK Document: https://doc.nucleisys.com/hbird_sdk/hummingbirdsdk.pdf
