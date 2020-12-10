.. _quickstart:

Quick Startup
=============

.. _quickstart_setup_tools_env:

Setup Tools and Environment
---------------------------

To start to use HummingBird SDK, you need to install the following tools:

* For Windows users, please check :ref:`quickstart_setup_tools_env_windows`
* For Linux users, please check :ref:`quickstart_setup_tools_env_linux`

.. _quickstart_setup_tools_env_windows:

Install and Setup Tools in Windows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure you are using at least **Windows 7**, and then you can follow the following steps
to download and install tools for you.

1. Create an ``Nuclei`` folder in your Windows Environment, such as ``D:\Software\Nuclei``

2. Download the following tools from |nuclei_download_center|, please check and follow
   the figure :ref:`figure_quickstart_1`.

   - **Nuclei RISC-V GNU Toolchain for Windows**, see number **1** in the figure :ref:`figure_quickstart_1`
   - **Nuclei OpenOCD for Windows**, see number **2** in the figure :ref:`figure_quickstart_1`
   - **Windows Build Tools**, see number **3** in the figure :ref:`figure_quickstart_1`

.. _figure_quickstart_1:

.. figure:: /asserts/images/nuclei_tools_download_win.png
   :width: 80 %
   :align: center
   :alt: Nuclei Tools need to be downloaded for Windows

   Nuclei Tools need to be downloaded for Windows

3. Setup tools in previously created ``Nuclei`` folder, create ``gcc``, ``openocd`` and ``build-tools`` folders.

   - **Nuclei RISC-V GNU Toolchain for Windows**
      Extract the download **gnu toolchain** into a temp folder, and copy the files into ``gcc`` folder,
      make sure the ``gcc`` directory structure looks like this figure :ref:`figure_quickstart_2`

      .. _figure_quickstart_2:

      .. figure:: /asserts/images/nuclei_tool_gcc_directory.png
         :width: 80 %
         :align: center
         :alt: Nuclei RISC-V GCC Toolchain directory structure of gcc

         Nuclei RISC-V GCC Toolchain directory structure of gcc


   - **Nuclei OpenOCD for Windows**
      Extract the download **openocd** tool into a temp folder, and copy the files into ``openocd`` folder,
      make sure the ``openocd`` directory structure looks like this figure :ref:`figure_quickstart_3`

      .. _figure_quickstart_3:

      .. figure:: /asserts/images/nuclei_tool_openocd_directory.png
         :width: 80 %
         :align: center
         :alt: Nuclei OpenOCD directory structure of openocd

         Nuclei OpenOCD directory structure of openocd


   - **Windows Build Tools**
      Extract the download **build-tools** tool into a temp folder, and copy the files into ``build-tools`` folder,
      make sure the ``build-tools`` directory structure looks like this figure :ref:`figure_quickstart_4`

      .. _figure_quickstart_4:

      .. figure:: /asserts/images/nuclei_tool_build-tools_directory.png
         :width: 80 %
         :align: center
         :alt: Nuclei Windows Build Tools directory structure of build-tools

         Nuclei Windows Build Tools directory structure of build-tools


.. _quickstart_setup_tools_env_linux:

Install and Setup Tools in Linux
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure you are using **Centos or Ubuntu 64 bit**, and then you can follow the following steps
to download and install tools for you.

1. Create an ``Nuclei`` folder in your Linux Environment, such as ``~/Software/Nuclei``

2. Download the following tools from |nuclei_download_center|, please check and follow
   the figure :ref:`figure_quickstart_5`.

   - **Nuclei RISC-V GNU Toolchain for Linux**, for **CentOS or Ubuntu < 18.04** click number **1-1**,
     for **Ubuntu >=18.04** click number **1-2** in the figure :ref:`figure_quickstart_5`
   - **Nuclei OpenOCD for Linux**, see number **2-1** for 64bit version in the figure :ref:`figure_quickstart_5`
   - **Make >= 3.82**: Install ``Make`` using ``sudo apt-get install make`` in Ubuntu,
     or ``sudo yum install make`` in CentOS.


.. _figure_quickstart_5:

.. figure:: /asserts/images/nuclei_tools_download_linux.png
   :width: 80 %
   :align: center
   :alt: Nuclei Tools need to be downloaded for Linux

   Nuclei Tools need to be downloaded for Linux


3. Setup tools in previously created ``Nuclei`` folder, create ``gcc`` and ``openocd`` folders.
   Please follow similar steps described in **Step 3** in :ref:`quickstart_setup_tools_env_windows`
   to extract and copy necessary files.

    .. note::

       * Only ``gcc`` and ``openocd`` are required for Linux.
       * Extract the downloaded Linux tools, not the windows version.


.. _quickstart_get_set_hbird_sdk:

Get and Setup HummingBird SDK
-----------------------------

The source code of HummingBird SDK is maintained in |github| and |gitee|.

* We mainly maintained github version, and gitee version is mirrored, just for fast access in China.
* Check source code in |github_hbird_sdk|.
* Stable version of HummingBird SDK is maintained in **master** version, if you want release version of **HummingBird SDK**,
  please check in |github_hbird_sdk_release|.

**Here are the steps to clone the latest source code from Github:**

* Make sure you have installed Git tool, see https://git-scm.com/download/
* Then open your terminal, and make sure git command can be accessed
* Run ``git clone https://github.com/riscv-mcu/hbird-sdk hbird-sdk`` to clone source code
  into ``hbird-sdk`` folder

  .. note::

      - If you have no internet access, you can also use pre-downloaded ``hbird-sdk`` code,
        and use it.
      - If the backup repo is not up to date, you can import github repo in gitee by yourself, see
        https://gitee.com/projects/import/url

* Create tool environment config file for HummingBird SDK

  - **Windows**
     Create ``setup_config.bat`` in ``hbird-sdk`` folder, and open this file
     your editor, and paste the following content, assuming you followed
     :ref:`quickstart_setup_tools_env_windows` and install tools into ``D:\Software\Nuclei``,
     otherwise please use your correct tool root path.

     .. code-block:: bat

         set NUCLEI_TOOL_ROOT=D:\Software\Nuclei

  - **Linux**
     Create ``setup_config.sh`` in ``hbird-sdk`` folder, and open this file
     your editor, and paste the following content, assuming you followed
     :ref:`quickstart_setup_tools_env_linux` and install tools into ``~/Software/Nuclei``,
     otherwise please use your correct tool root path.

     .. code-block:: shell

         NUCLEI_TOOL_ROOT=~/Software/Nuclei


.. _quickstart_buildrundebug_app:

Build, Run and Debug Sample Application
---------------------------------------

Assume you have followed steps in :ref:`quickstart_get_set_hbird_sdk` to clone
source code and create ``setup_config.bat`` and ``setup_config.sh``.

To build, run and debug application, you need to open command terminal in ``hbird-sdk``
folder.

* For **Windows** users, you can open windows command terminal and cd to ``hbird-sdk`` folder,
  then run the following commands to setup build environment for HummingBird SDK, the output will
  be similar as this screenshot :ref:`figure_quickstart_6`:

  .. code-block:: bat
     :linenos:

     setup.bat
     echo %PATH%
     where riscv-nuclei-elf-gcc openocd make rm
     make help

  .. _figure_quickstart_6:

  .. figure:: /asserts/images/hbird_sdk_open_cmd.png
     :width: 80 %
     :align: center
     :alt: Setup Build Environment for HummingBird SDK in Windows Command Line

     Setup Build Environment for HummingBird SDK in Windows Command Line

* For **Linux** users, you can open Linux bash terminal and cd to ``hbird-sdk`` folder,
  then run the following commands to setup build environment for HummingBird SDK, the output will
  be similar as this screenshot :ref:`figure_quickstart_7`:

  .. code-block:: shell
     :linenos:

     source setup.sh
     echo $PATH
     which riscv-nuclei-elf-gcc openocd make rm
     make help

  .. _figure_quickstart_7:

  .. figure:: /asserts/images/hbird_sdk_open_shell.png
     :width: 80 %
     :align: center
     :alt: Setup Build Environment for HummingBird SDK in Linux Bash

     Setup Build Environment for HummingBird SDK in Linux Bash


.. note::

    * Only first line ``setup.bat`` or ``source setup.sh`` are required before build, run or debug application.
      The ``setup.bat`` and ``setup.sh`` are just used to append Nuclei RISC-V GCC Toolchain, OpenOCD and Build-Tools
      binary paths into environment variable **PATH**
    * line 2-4 are just used to check whether build environment is setup correctly, especially the **PATH** of
      Nuclei Tools are setup correctly, so we can use the ``riscv-nuclei-elf-xxx``, ``openocd``, ``make`` and ``rm``
      tools
    * If you know how to append Nuclei RISC-V GCC Toolchain, OpenOCD and Build-Tools binary paths to **PATH** variable
      in your OS environment, you can also put the downloaded Nuclei Tools as you like, and no need to run ``setup.bat``
      or ``source setup.sh``


Here for a quick startup, this guide will take board :ref:`design_board_hbird_eval`
for example to demostrate how to setup hardware, build run and debug application in Windows.

The demo application, we will take ``application/baremetal/helloworld`` for example.

First of all, please reuse previously setuped build environment command terminal.

Run ``cd application/baremetal/helloworld`` to cd the ``helloworld`` example folder.

Hardware Preparation
~~~~~~~~~~~~~~~~~~~~

Please check :ref:`design_board` and find your board's page, and follow **Setup** section
to setup your hardware, mainly **JTAG debugger driver setup and on-board connection setup**.

* Power on the **HummingBird** board, and use Micro-USB data cable to connect the board and your PC,
  make sure you have setup the JTAG driver correctly, and you can see JTAG port and serial port.
* Open a UART terminal tool such as |teraterm| or |minicom|, and minitor the serial port of the Board,
  the UART baudrate is *115200 bps*

Build Application
~~~~~~~~~~~~~~~~~

We need to build application for this board :ref:`design_board_hbird_eval` using this command line:

.. code-block:: shell

    make SOC=hbird BOARD=hbird_eval CORE=e203 all

Here is the sample output of this command:

.. code-block::

    Current Configuration: RISCV_ARCH=rv32imac RISCV_ABI=ilp32 SOC=hbird BOARD=hbird_eval CORE=e203 DOWNLOAD=ilm
    Assembling :  ../../../SoC/hbird/Common/Source/GCC/intexc_hbird.S
    Assembling :  ../../../SoC/hbird/Common/Source/GCC/startup_hbird.S
    Compiling  :  ../../../SoC/hbird/Common/Source/Drivers/hbird_gpio.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Drivers/hbird_uart.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/close.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/fstat.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/gettimeofday.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/isatty.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/lseek.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/read.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/sbrk.c
    Compiling  :  ../../../SoC/hbird/Common/Source/Stubs/write.c
    Compiling  :  ../../../SoC/hbird/Common/Source/hbird_common.c
    Compiling  :  ../../../SoC/hbird/Common/Source/system_hbird.c
    Compiling  :  hello_world.c
    Linking    :  hello_world.elf
    text	   data	    bss	    dec	    hex	filename
    7944	    112	   2440	  10496	   2900	hello_world.elf


As you can see, that when the application is built successfully, the elf will be generated
and will also print the size information of the ``hello_world.elf``.

.. note::

    * In order to make sure that there is no application build before, you can run
      ``make SOC=hbird BOARD=hbird_eval CORE=e203 clean`` to clean previously built
      objects and build dependency files.
    * About the make variable or option(**SOC**, **BOARD**) passed to make command, please refer
      to :ref:`develop_buildsystem`.

Run Application
~~~~~~~~~~~~~~~

If the application is built successfully for this board :ref:`design_board_hbird_eval`,
then you can run it using this command line:

.. code-block:: shell

    make SOC=hbird BOARD=hbird_eval CORE=e203 upload

Here is the sample output of this command:

.. code-block::

   "Download and run hello_world.elf"
    riscv-nuclei-elf-gdb hello_world.elf -ex "set remotetimeout 240" \
            -ex "target remote | openocd --pipe -f ../../../SoC/hbird/Board/hbi
            --batch -ex "monitor reset halt" -ex "monitor halt" -ex "monitor fl
    resume" -ex "monitor shutdown" -ex "quit"
    D:\Nuclei\gcc\bin\riscv-nuclei-elf-gdb.exe: warning: Couldn't determine a p
    Nuclei OpenOCD, 64-bit Open On-Chip Debugger 0.10.0+dev-00014-g0eae03214 (2
    Licensed under GNU GPL v2
    For bug reports, read
            http://openocd.org/doc/doxygen/bugs.html
    system_default_interrupt_handler (mcause=3735928559, sp=<optimized out>) at88
    188         printf("MTVAL : 0x%lx\r\n", __RV_CSR_READ(CSR_MBADADDR));
    JTAG tap: riscv.cpu tap/device found: 0x1e200a6d (mfg: 0x536 (Nuclei System
    halted at 0x8000050c due to debug interrupt
    cleared protection for sectors 0 through 63 on flash bank 0
    
    Loading section .init, size 0xc4 lma 0x80000000
    Loading section .text, size 0x1c6e lma 0x80000100
    Loading section .rodata, size 0x1ec lma 0x80001d70
    Loading section .data, size 0x70 lma 0x80001f5c
    Start address 0x80000000, load size 8078
    Transfer rate: 45 KB/sec, 2019 bytes/write.
    halted at 0x80000004 due to step
    shutdown command invoked
    A debugging session is active.
    
            Inferior 1 [Remote target] will be detached.
    
    Quit anyway? (y or n) [answered Y; input not from terminal]
    [Inferior 1 (Remote target) detached]


As you can see the application is uploaded successfully using ``openocd`` and ``gdb``,
then you can check the output in your UART terminal, see :ref:`figure_quickstart_8`.

.. _figure_quickstart_8:

.. figure:: /asserts/images/hbird_app_helloworld_uart.png
    :width: 80 %
    :align: center
    :alt: HummingBird SDK Hello World Application UART Output

    HummingBird SDK Hello World Application UART Output


Debug Application
~~~~~~~~~~~~~~~~~

If the application is built successfully for this board :ref:`design_board_hbird_eval`,
then you can debug it using this command line:

.. code-block:: shell

    make SOC=hbird BOARD=hbird_eval CORE=e203 debug


1. The program is not loaded automatically when you enter to debug state, just in case you want to
   debug the program running on the board.

   .. code-block::

     "Download and debug hello_world.elf"
     riscv-nuclei-elf-gdb hello_world.elf -ex "set remotetimeout 240" \
             -ex "target remote | openocd --pipe -f ../../../SoC/hbird/Board/hbi
     D:\Nuclei\gcc\bin\riscv-nuclei-elf-gdb.exe: warning: Couldn't determine a p
     GNU gdb (GDB) 8.3.0.20190516-git
     Copyright (C) 2019 Free Software Foundation, Inc.
     License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.htm
     This is free software: you are free to change and redistribute it.
     There is NO WARRANTY, to the extent permitted by law.
     Type "show copying" and "show warranty" for details.
     This GDB was configured as "--host=i686-w64-mingw32 --target=riscv-nuclei-e
     Type "show configuration" for configuration details.
     For bug reporting instructions, please see:
     <http://www.gnu.org/software/gdb/bugs/>.
     Find the GDB manual and other documentation resources online at:
         <http://www.gnu.org/software/gdb/documentation/>.
     
     For help, type "help".
     Type "apropos word" to search for commands related to "word"...
     --Type <RET> for more, q to quit, c to continue without paging--
     Reading symbols from hello_world.elf...
     Remote debugging using | openocd --pipe -f ../../../SoC/hbird/Board/hbird_e
     Nuclei OpenOCD, 64-bit Open On-Chip Debugger 0.10.0+dev-00014-g0eae03214 (2
     Licensed under GNU GPL v2
     For bug reports, read
             http://openocd.org/doc/doxygen/bugs.html
     system_default_interrupt_handler (mcause=3735928559, sp=<optimized out>)
         at ../../../SoC/hbird/Common/Source/system_hbird.c:188
     188         printf("MTVAL : 0x%lx\r\n", __RV_CSR_READ(CSR_MBADADDR));

2. If you want to load the built application, you can type ``load`` to load the application.

   .. code-block::

      (gdb) load
      Loading section .init, size 0x266 lma 0x8000000
      Loading section .text, size 0x2e9c lma 0x8000280
      Loading section .rodata, size 0x1f0 lma 0x8003120
      Loading section .data, size 0x70 lma 0x8003310
      Start address 0x800015c, load size 13154
      Transfer rate: 7 KB/sec, 3288 bytes/write.

3. If you want to set a breakpoint at *main*, then you can type ``b main`` to set a breakpoint.

   .. code-block::

      (gdb) b main
      Breakpoint 1 at 0x8001b04: file hello_world.c, line 85.

4. If you want to set more breakpoints, you can do as you like.

5. Then you can type ``c``, then the program will stop at **main**

   .. code-block::

      (gdb) c
      Continuing.
      Note: automatically using hardware breakpoints for read-only addresses.

      Breakpoint 1, main () at hello_world.c:85
      85          srand(__get_rv_cycle()  | __get_rv_instret() | __RV_CSR_READ(CSR_MCYCLE));


6. Then you can step it using ``n`` (short of next) or ``s`` (short of step)

   .. code-block::

      (gdb) n
      86          uint32_t rval = rand();
      (gdb) n
      87          rv_csr_t misa = __RV_CSR_READ(CSR_MISA);
      (gdb) s
      89          printf("MISA: 0x%lx\r\n", misa);
      (gdb) n
      90          print_misa();
      (gdb) n
      92          printf("Hello World!\r\n");
      (gdb) n
      93          printf("Hello World!\r\n");

7. If you want to quit debugging, then you can press ``CTRL - c``, and type ``q`` to quit debugging.

   .. code-block::

      (gdb) Quit
      (gdb) q
      A debugging session is active.

              Inferior 1 [Remote target] will be detached.

      Quit anyway? (y or n) y
      Detaching from program: D:\workspace\Sourcecode\hbird-sdk\application\baremetal\helloworld\hello_world.elf, Remote target
      Ending remote debugging.
      [Inferior 1 (Remote target) detached]

.. note::

   * More about how to debug using gdb, you can refer to the `GDB User Manual`_.
   * If you want to debug using Nuclei Studio, you can open Nuclei Studio, and create a debug configuration,
     and choose the application elf, and download and debug in IDE.


Create helloworld Application
-----------------------------

If you want to create your own ``helloworld`` application, it is also very easy.

There are several ways to achieve it, see as below:

* **Method 1:** You can find a most similar sample application folder and copy it, such as
  ``application/baremetal/helloworld``, you can copy and rename it as ``application/baremetal/hello``

  - Open the ``Makefile`` in ``application/baremetal/hello``

     1. Change ``TARGET = hello_world`` to ``TARGET = hello``

  - Open the ``hello_world.c`` in ``application/baremetal/hello``, and replace the content using code below:

     .. code-block:: c
        :linenos:

        // See LICENSE for license details.
        #include <stdio.h>
        #include <time.h>
        #include <stdlib.h>
        #include "hbird_sdk_soc.h"

        int main(void)
        {
            printf("Hello World from HummingBird RISC-V Processor!\r\n");
            return 0;
        }

  - Save all the changes, and then you can follow the steps described
    in :ref:`quickstart_buildrundebug_app` to run or debug this new application.

* **Method 2:** You can also do it from scratch, with just create simple ``Makefile`` and ``main.c``

  - Create new folder named ``hello`` in ``application/baremetal``
  - Create two files named ``Makefile`` and ``main.c``
  - Open ``Makefile`` and edit the content as below:

     .. code-block:: makefile
        :linenos:

        TARGET = hello

        HBIRD_SDK_ROOT = ../../..

        SRCDIRS = .

        INCDIRS = .

        include $(HBIRD_SDK_ROOT)/Build/Makefile.base

  - Open ``main.c`` and edit the content as below:

     .. code-block:: c
        :linenos:

        // See LICENSE for license details.
        #include <stdio.h>
        #include <time.h>
        #include <stdlib.h>
        #include "hbird_sdk_soc.h"

        int main(void)
        {
            printf("Hello World from HummingBird RISC-V Processor!\r\n");
            return 0;
        }

  - Save all the changes, and then you can follow the steps described
    in :ref:`quickstart_buildrundebug_app` to run or debug this new application.

.. note::

    * Please refer to :ref:`develop_appdev` and :ref:`develop_buildsystem` for more information.
    * If you want to access SoC related APIs, please use ``hbird_sdk_soc.h`` header file.
    * If you want to access SoC and board related APIs, please use ``hbird_sdk_hal.h`` header file.
    * For simplified application development, you can use ``hbird_sdk_hal.h`` directly.

Advanced Usage
--------------

For more advanced usage, please follow the items as below:

* Click :ref:`design` to learn about HummingBird SDK Design and Architecture, Board and SoC support documentation.
* Click :ref:`develop` to learn about HummingBird SDK Build System and Application Development.
* Click :ref:`design_app` to learn about each application usage and expected output.

.. note::

    * If you met some issues in using this guide, please check :ref:`faq`,
      if still not solved, please :ref:`contribute_submit_issue`.

    * If you want to develop HummingBird SDK application in Nuclei Studio, you can also easily integrate the source code with it.

       1. Add required source code folders, and header file folders in IDE

       2. Check the compiler and linker options using extra **V=1** passed with *make*, and adapt the options in IDE

       3. Add extra macros definition and include folders in project configurations

       4. Build and debug project in IDE

.. _GDB User Manual: https://www.gnu.org/software/gdb/documentation/
