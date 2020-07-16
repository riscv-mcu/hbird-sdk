.. _design_hbird:

HummingBird RISC-V Processor
============================

HummingBird RISC-V processor core are following and compatible to RISC-V standard architecture,
but there might be some additions and enhancements to the original standard spec.

Click `RISC-V Spec`_ to learn more about Official RISC-V Instruction Set Architecture.

.. _design_hbird_intro:

Introduction
------------

Open source HummingBird RISC-V Processor provides the following RISC-V Cores for AIoT:

* **E200 series:** Designed for ultra-low power consumption and
  embedded scenarios, perfectly replaces the arm Cortex-M series cores.


.. _design_hbird_nmsis:

NMSIS in HummingBird SDK
------------------------

This HummingBird SDK is built based on the **modified** |NMSIS| framework,
user can access :ref:`NMSIS Core API <nmsis_core>`, `NMSIS DSP API`_ and `NMSIS NN API`_
provided by |NMSIS|.

These modified NMSIS-Core APIs are mainly responsible for accessing HummingBird
RISC-V Processor Core.

.. toctree::
   :maxdepth: 3

   core/index.rst

The prebuilt NMSIS-DSP and NMSIS-NN libraries without dsp are also provided in
HummingBird SDK, see ``NMSIS/Library/`` folder.

.. note::

    * To support RT-Thread in HBird-SDK, we have to modify the **startup_<device>.S**,
      to use macro ``RTOS_RTTHREAD`` defined when using RT-Thread as below:

      .. code-block:: c

        #ifdef RTOS_RTTHREAD
            // Call entry function when using RT-Thread
            call entry
        #else
            call main
        #endif

    * In order to support RT-Thread initialization macros ``INIT_XXX_EXPORT``, we also need
      to modify the link script files, add lines after `` *(.rodata .rodata.*)`` as below:

      .. code-block::

        . = ALIGN(4);
        *(.rdata)
        *(.rodata .rodata.*)
        /* RT-Thread added lines begin */
        /* section information for initial. */
        . = ALIGN(4);
        __rt_init_start = .;
        KEEP(*(SORT(.rti_fn*)))
        __rt_init_end = .;
        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        /* RT-Thread added lines end */
        *(.gnu.linkonce.r.*)

.. _design_hbird_soc:

SoC Resource
------------

Regarding the SoC Resource exclude the HummingBird RISC-V Processor Core,
it mainly consists of different peripherals such UART, GPIO, I2C, SPI,
CAN, PWM, DMA, USB and etc.

The APIs to access to the SoC resources are usually defined by the SoC
Firmware Library Package provided by SoC Vendor.

In HummingBird SDK, currently we just required developer to provide the following
common resources:

* A UART used to implement the ``_write`` and ``_read`` stub functions for
  ``printf`` functions
* Common initialization code defined in **System_<Device>.c/h** in each
  SoC support package in HummingBird SDK.
* Before enter to main function, these resources must be initialized:

  - The UART used to print must be initialized as
    ``115200 bps, 8bit data, none parity check, 1 stop bit``
  - PLIC interrupts are disabled and priorities set to 0
  - Global interrupt is disabled


.. note::

    * If you want to learn more about SoC, please click :ref:`design_soc`
    * If you want to learn more about Board, please click :ref:`design_board`
    * If you want to learn more about Peripheral, please click :ref:`design_peripheral`


.. _RISC-V Spec: https://riscv.org/specifications/
.. _NMSIS Core API: https://doc.nucleisys.com/nmsis/core/api/index.html
.. _NMSIS DSP API: https://doc.nucleisys.com/nmsis/dsp/api/index.html
.. _NMSIS NN API: https://doc.nucleisys.com/nmsis/nn/api/index.html
