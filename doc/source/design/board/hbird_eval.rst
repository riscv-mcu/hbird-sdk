.. _design_board_hbird_eval:

HummingBird Evaluation Kit
==========================

.. _design_board_hbird_eval_overview:

Overview
--------

Nuclei have customized a FPGA evaluation board (called Hummingbird Evaluation Kit),
which can be programmed with HummingBird SoC FPGA bitstream.

.. _figure_design_board_hbird_eval_1:

.. figure:: /asserts/images/hbird_eval_board.jpg
    :width: 80 %
    :align: center
    :alt: HummingBird FPGA Evaluation Kit

    HummingBird FPGA Evaluation Kit

Click `HummingBird FPGA Evaluation Kit Board Documents`_ to access the documents
of this board.

.. _design_board_hbird_eval_setup:

Setup
~~~~~

Follow the guide in `HummingBird FPGA Evaluation Kit Board Documents`_ to setup the board,
make sure the following items are set correctly:

* Use **Hummingbird debugger** to connect the **MCU-JTAG** on board to your PC
  in order to download and debug programs and monitor the UART message.
* Power on the Board using USB doggle.
* The HummingBird SoC FPGA bitstream with HummingBird RISC-V evaluation core inside
  is programmed to this board.
* Following steps in board user manual to setup JTAG drivers for your development environment

.. _design_board_hbird_eval_use:

How to use
~~~~~~~~~~

For **HummingBird Evaluation board**:

* **DOWNLOAD** support all the modes list in :ref:`develop_buildsystem_var_download`
* **CORE** support all the cores list in :ref:`develop_buildsystem_var_core`

To run this application in HummingBird Evaluation board in HummingBird SDK,
you just need to use this **SOC** and **BOARD** variables.

.. code-block:: shell

    # Clean the application with DOWNLOAD=ilm CORE=e203
    make SOC=hbird BOARD=hbird_eval DOWNLOAD=ilm CORE=e203 clean
    # Build the application with DOWNLOAD=ilm CORE=e203
    make SOC=hbird BOARD=hbird_eval DOWNLOAD=ilm CORE=e203 all
    # Upload the application using openocd and gdb with DOWNLOAD=ilm CORE=e203
    make SOC=hbird BOARD=hbird_eval DOWNLOAD=ilm CORE=e203 upload
    # Debug the application using openocd and gdb with DOWNLOAD=ilm CORE=e203
    make SOC=hbird BOARD=hbird_eval DOWNLOAD=ilm CORE=e203 debug

.. note::

   * You can change the value passed to **CORE** according to
     the HummingBird RISC-V Core the HummingBird SoC you have.
   * You can also change the value passed to **DOWNLOAD** to run
     program in different modes.
   * The FreeRTOS and UCOSII demos maybe not working in ``flashxip``
     download mode in HummingBird board due to program running in Flash is really too slow.
     If you want to try these demos, please use ``ilm`` or ``flash``
     download mode.

.. _HummingBird FPGA Evaluation Kit Board Documents: https://nucleisys.com/developboard.php
