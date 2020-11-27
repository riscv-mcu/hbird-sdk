.. _design_soc_hbirdv2:

HummingBird SoC V2
==================

HummingBird SoC V2 is an evaluation FPGA SoC based on HummingBird RISC-V Core
for customer to evaluate HummingBird Process Core.

To get the up to date documentation about this SoC, please click:

* `HummingBird SoC V2 online documentation`_
* `HummingBird SoC V2 project source code`_

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

.. figure:: /asserts/images/hbirdv2_soc_diagram.jpg
    :width: 80 %
    :align: center
    :alt: HummingBird V2 SoC Diagram

    HummingBird V2 SoC Diagram

If you want to learn more about this evaluation SoC,
please click `HummingBird SoC V2 online documentation`_.

.. _design_soc_hbirdv2_boards:

Supported Boards
----------------

In HummingBird SDK, we support the following boards based on **HummingBird** SoC, see:

* :ref:`design_board_ddr200t`
* :ref:`design_board_mcu200t`

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
.. _HummingBird SoC V2 online documentation: https://doc.nucleisys.com/hbirdv2
.. _HummingBird SoC V2 project source code: https://github.com/riscv-mcu/e203_hbirdv2
