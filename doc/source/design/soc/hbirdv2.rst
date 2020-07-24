.. _design_soc_hbirdv2:

HummingBird SoC V2
==================

HummingBird SoC V2 is an evaluation FPGA SoC based on HummingBird RISC-V Core
for customer to evaluate HummingBird Process Core.

.. _design_soc_hbirdv2_overview:

Overview
--------

To easy user to evaluate HummingBird RISC-V Processor Core, the prototype
SoC (called Hummingbird SoC) is provided for evaluation purpose.

This prototype SoC includes:

* Processor Core, it can be RISC-V Core.
* On-Chip SRAMs for instruction and data.
* The SoC buses.
* The basic peripherals, such as UART, GPIO, SPI, I2C, etc.

With this prototype SoC, user can run simulations, map it into the FPGA board,
and run with real embedded application examples.

The SoC diagram can be checked as below :ref:`figure_design_soc_hbirdv2_1`

.. _figure_design_soc_hbirdv2_1:

.. figure:: /asserts/images/hbird_soc_diagram.png
    :width: 80 %
    :align: center
    :alt: HummingBird SoC Diagram

    HummingBird SoC Diagram

The SoC memory map for SoC resources is as below :ref:`figure_design_soc_hbirdv2_2`

.. _figure_design_soc_hbirdv2_2:

.. figure:: /asserts/images/hbird_soc_memory_map.png
    :width: 80 %
    :align: center
    :alt: HummingBird SoC Memory Map

    HummingBird SoC Memory Map

If you want to learn more about this evaluation SoC, please get the
``<Nuclei_Eval_SoC_Intro.pdf>`` from `Nuclei`_.


.. _design_soc_hbirdv2_boards:

Supported Boards
----------------

In HummingBird SDK, we support the following boards based on **HummingBird** SoC, see:

* :ref:`design_board_ddr200t`

.. _design_soc_hbirdv2_usage:

Usage
-----

If you want to use this **HummingBird** SoC in HummingBird SDK, you need to set the
:ref:`develop_buildsystem_var_soc` Makefile variable to ``hbird``.

.. code-block:: shell

    # Choose SoC to be hbird
    # the following command will build application
    # using default hbird SoC based board
    # defined in Build System and application Makefile
    make SOC=hbirdv2 all


.. _Nuclei: https://nucleisys.com/
