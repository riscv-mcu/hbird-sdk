.. _develop_buildsystem:

Build System based on Makefile
==============================

HummingBird SDK's build system is based on Makefile, user can build,
run ordebug application in Windows and Linux.

.. _develop_buildsystem_structure:

Makefile Structure
------------------

HummingBird SDK's Makefiles mainly placed in **<HBIRD_SDK_ROOT>/Build** directory and
an extra *Makefile* located in **<HBIRD_SDK_ROOT>/Makefile**.

This extra **<HBIRD_SDK_ROOT>/Makefile** introduce a new Make variable called
**PROGRAM** to provide the ability to build or run application in **<HBIRD_SDK_ROOT>**.

For example, if you want to *rebuild and upload* application **application/baremetal/timer_test**,
you can run ``make PROGRAM=application/baremetal/timer_test clean upload`` to achieve it.


The **<HBIRD_SDK_ROOT>/Build** directory content list as below:

.. code-block:: text

    gmsl/
    Makefile.base
    Makefile.conf
    Makefile.core
    Makefile.components
    Makefile.files
    Makefile.global  -> Created by user
    Makefile.misc
    Makefile.rtos
    Makefile.rules
    Makefile.soc

The file or directory is used explained as below:

.. _develop_buildsystem_makefile_base:

Makefile.base
~~~~~~~~~~~~~

This **Makefile.base** file is used as HummingBird SDK build system entry file,
application's Makefile need to include this file to use all the features of
HummingBird SDK build system.

It will expose Make variables or options such as **BOARD** or **SOC** passed
by ``make`` command, click :ref:`develop_buildsystem_exposed_make_vars`
to learn more.

This file will include optional :ref:`develop_buildsystem_makefile_global`
and :ref:`develop_buildsystem_makefile_local` which allow user to set custom
global Makefile configurations and local application Makefile configurations.

This file will include the following makefiles:

* :ref:`develop_buildsystem_gmsl`: additional library functions provided via gmsl
* :ref:`develop_buildsystem_makefile_misc`: misc functions and OS check helpers
* :ref:`develop_buildsystem_makefile_conf`: main Makefile configuration entry
* :ref:`develop_buildsystem_makefile_rules`: make rules of this build system

.. _develop_buildsystem_gmsl:

gmsl
~~~~

The **gmsl** directory consist of the `GNU Make Standard Library (GMSL)`_,
which is an a library of functions to be used with GNU Make's $(call) that
provides functionality not available in standard GNU Make.

We use this **gmsl** tool to make sure we help us achieve some linux command
which is only supported in Linux.

.. _develop_buildsystem_makefile_misc:

Makefile.misc
~~~~~~~~~~~~~

This **Makefile.misc** file mainly provide these functions:

* Define **get_csrcs**, **get_asmsrcs**, **get_cxxsrcs** and **check_item_exist** make functions

  - **get_csrcs**: Function to get ``*.c or *.C`` source files from a list of directories, no ability to
    do recursive match. e.g. ``$(call get_csrcs, csrc csrc/abc)`` will return c source files in
    ``csrc`` and ``csrc/abc`` directories.
  - **get_asmsrcs**: Function to get ``*.s or *.S`` source files from a list of directories, no ability to
    do recursive match. e.g. ``$(call get_asmsrcs, asmsrc asmsrc/abc)`` will return asm source files in
    ``asmsrc`` and ``asmsrc/abc`` directories.
  - **get_cxxsrcs**: Function to get ``*.cpp or *.CPP`` source files from a list of directories, no ability
    to do recursive match. e.g. ``$(call get_cxxsrcs, cppsrc cppsrc/abc)`` will return cpp source files in
    ``cppsrc`` and ``cppsrc/abc`` directories.
  - **check_item_exist**: Function to check if item existed in a set of items. e.g.
    ``$(call check_item_exist, flash, flash ilm flashxip)`` will check ``flash`` whether existed in
    ``flash ilm flashxip``, if existed, return ``flash``, otherwise return empty.

* Check and define OS related functions, and also a set of trace print functions.

.. _develop_buildsystem_makefile_conf:

Makefile.conf
~~~~~~~~~~~~~

This **Makefile.conf** file will define the following items:

* Toolchain related variables used during compiling
* Debug related variables
* Include :ref:`develop_buildsystem_makefile_files` and :ref:`develop_buildsystem_makefile_rtos`
* Collect all the C/C++/ASM compiling and link options

.. _develop_buildsystem_makefile_components:

Makefile.components
~~~~~~~~~~~~~~~~~~~

This **Makefile.components** will include ``build.mk`` Makefiles of selected components defined
via makefile variable :ref:`develop_buildsystem_var_middleware`, the Makefiles are placed in
the sub-folders of **<HBIRD_SDK_ROOT>/Components/**.

A valid middleware component should be organized like this, take ``fatfs`` as example :

.. code-block::

    Components/fatfs/
    ├── build.mk
    ├── documents
    ├── LICENSE.txt
    └── source


For example, if there are two valid middleware components in **<HBIRD_SDK_ROOT>/Components/**, called
``fatfs`` and ``tjpgd``, and you want to use them in your application, then you can set ``MIDDLEWARE``
like this ``MIDDLEWARE := fatfs tjpgd``, then the application will include these two middlewares into
build process.

.. _develop_buildsystem_makefile_rules:

Makefile.rules
~~~~~~~~~~~~~~

This **Makefile.rules** file will do the following things:

* Collect all the sources during compiling
* Define all the rules used for building, uploading and debugging
* Print help message for build system


.. _develop_buildsystem_makefile_files:

Makefile.files
~~~~~~~~~~~~~~

This **Makefile.files** file will do the following things:

* Define common C/C++/ASM source and include directories
* Define common C/C++/ASM macros
* Include **Makefile.files.<SOC>** which will include all the source
  code related to the :ref:`develop_buildsystem_var_soc` and
  :ref:`develop_buildsystem_var_board`

  - **Makefile.files.hbird**: Used to include source code for
    :ref:`design_soc_hbird`


.. _develop_buildsystem_makefile_soc:

Makefile.soc
~~~~~~~~~~~~

This **Makefile.soc** will include valid makefiles located in
**<HBIRD_SDK_ROOT>/SoC/<SOC>/build.mk** according to
the :ref:`develop_buildsystem_var_soc` makefile variable setting.

It will define the following items:

* **DOWNLOAD** and **CORE** variables

  - For :ref:`design_soc_hbird`, we can support all the modes defined in
    :ref:`develop_buildsystem_var_download`, and **CORE** list defined in
    :ref:`develop_buildsystem_makefile_core`
  - For :ref:`design_soc_hbirdv2`, we can support all the modes defined in
    :ref:`develop_buildsystem_var_download`, and **CORE** list defined in
    :ref:`develop_buildsystem_makefile_core`

* Linker script used according to the **DOWNLOAD** mode settings
* OpenOCD debug configuration file used for the SoC and Board
* Some extra compiling or debugging options

A valid SoC should be organized like this, take ``hbirdv2`` as example:

.. code-block::

    SoC/hbirdv2
    ├── Board
    │   └── hbird_fpga_eval
    │       ├── Include
    │       │   ├── board_hbird_fpga_eval.h
    │       │   └── hbird_sdk_hal.h
    │       ├── Source
    │       │   └── GCC
    │       └── openocd_hbirdv2.cfg
    ├── build.mk
    └── Common
        ├── Include
        │   ├── hbirdv2.h
        │   ├── ... ...
        │   ├── hbirdv2_uart.h
        │   ├── hbird_sdk_soc.h
        │   └── system_hbirdv2.h
        └── Source
            ├── Drivers
            │   ├── ... ...
            │   └── hbirdv2_uart.c
            ├── GCC
            │   ├── intexc_hbirdv2.S
            │   └── startup_hbirdv2.S
            ├── Stubs
            │   ├── read.c
            │   ├── ... ...
            │   └── write.c
            ├── hbirdv2_common.c
            └── system_hbirdv2.c

.. _develop_buildsystem_makefile_rtos:

Makefile.rtos
~~~~~~~~~~~~~

This **Makefile.rtos** will include **<HBIRD_SDK_ROOT>/OS/<RTOS>/build.mk**
according to our :ref:`develop_buildsystem_var_rtos` variable.

A valid rtos should be organized like this, take ``UCOSII`` as example:

.. code-block::

    OS/UCOSII/
    ├── arch
    ├── build.mk
    ├── license.txt
    ├── readme.md
    └── source


If no :ref:`develop_buildsystem_var_rtos` is chosen, then RTOS
code will not be included during compiling, user will develop
baremetal application.

If **FreeRTOS**, **UCOSII** or **RTThread** RTOS is chosen, then FreeRTOS
UCOSII, or RTThread source code will be included during compiling, and extra
compiler option ``-DRTOS_$(RTOS_UPPER)`` will be passed, then user can develop RTOS application.

For example, if ``FreeRTOS`` is selected, then ``-DRTOS_FREERTOS`` compiler option
will be passed.

.. _develop_buildsystem_makefile_core:

Makefile.core
~~~~~~~~~~~~~

This **Makefile.core** is used to define the RISC-V ARCH and ABI used during
compiling of the CORE list supported.

If you want to add a new **CORE**, you need to add a new line before **SUPPORTED_CORES**,
and append the new **CORE** to **SUPPORTED_CORES**.

For example, if you want to add a new **CORE** called **e207**, and the **e207**'s
**ARCH** and **ABI** are ``rv32imafdc`` and ``ilp32d``, then you can add a new line
like this ``E207_CORE_ARCH_ABI = rv32imafdc ilp32d``, and append **e207** to **SUPPORTED_CORES**
like this ``SUPPORTED_CORES = e201 e201e e203 e205 e205f e205fd e207``

.. note::

   * The appended new **CORE** need to lower-case, e.g. *e207*
   * The new defined variable **E207_CORE_ARCH_ABI** need to be all upper-case.


.. _develop_buildsystem_makefile_global:

Makefile.global
~~~~~~~~~~~~~~~

This **Makefile.global** file is an optional file, and will not be tracked by git,
user can create own **Makefile.global** in **<HBIRD_SDK_ROOT>/Build** directory.

In this file, user can define custom **SOC**, **BOARD**, **DOWNLOAD** options to
overwrite the default configuration.

For example, if you will use only the :ref:`design_board_hbird_eval`, you can
create the **<HBIRD_SDK_ROOT>/Build/Makefile.global** as below:

.. code-block:: Makefile

    SOC ?= hbird
    BOARD ?= hbird_eval
    DOWNLOAD ?= flashxip

.. note::

    * If you add above file, then you can build, run, debug application without passing
      **SOC**, **BOARD** and **DOWNLOAD** variables using make command for
      :ref:`design_board_hbird_eval` board, e.g.

      - Build and run application for :ref:`design_board_hbird_eval`: ``make run``
      - Debug application for :ref:`design_board_hbird_eval`: ``make debug``

    * If you create the **Makefile.global** like above sample code, you will also be able
      to use HummingBird SDK build system as usually, it will only change the default **SOC**,
      **BOARD** and **DOWNLOAD**, but you can still override the default variable using
      make command, such as ``make SOC=hbird BOARD=hbird_eval DOWNLOAD=ilm``

.. _develop_buildsystem_makefile_local:

Makefile.local
~~~~~~~~~~~~~~

As the :ref:`develop_buildsystem_makefile_global` is used to override the default Makefile
configurations, and the **Makefile.local** is used to override application level Makefile
configurations, and also this file will not be tracked by git.

User can create ``Makefile.local`` file in any of the application folder, placed together with
the application Makefile, for example, you can create ``Makefile.local`` in ``application/baremetal/helloworld``
to override default make configuration for this **helloworld** application.

If you want to change the default board for **helloworld** to use :ref:`design_board_hbird_eval`,
you can create ``application/baremetal/helloworld/Makefile.local`` as below:

.. code-block:: Makefile

    SOC ?= hbird
    BOARD ?= hbird_eval
    DOWNLOAD ?= flashxip

.. note::

    * This local make configuration will override global and default make configuration.
    * If you just want to change only some applications' makefile configuration, you can
      add and update ``Makefile.local`` for those applications.


.. _develop_buildsystem_make_targets:

Makefile targets of make command
--------------------------------

Here is a list of the :ref:`table_dev_buildsystem_4`.

.. _table_dev_buildsystem_4:

.. list-table:: Make targets supported by HummingBird SDK Build System
   :widths: 20 80
   :header-rows: 1
   :align: center

   * - target
     - description
   * - help
     - display help message of HummingBird SDK build system
   * - info
     - display selected configuration information
   * - all
     - build application with selected configuration
   * - clean
     - clean application with selected configuration
   * - dasm
     - build and dissemble application with selected configuration
   * - bin
     - build and generate application binary with selected configuration
   * - upload
     - build and upload application with selected configuration
   * - run_openocd
     - run openocd server with selected configuration
   * - run_gdb
     - build and start gdb process with selected configuration
   * - debug
     - build and debug application with selected configuration

.. note::

   * The selected configuration is controlled by
     :ref:`develop_buildsystem_exposed_make_vars`
   * For ``run_openocd`` and ``run_gdb`` target, if you want to
     change a new gdb port, you can pass the variable
     :ref:`develop_buildsystem_var_gdb_port`


.. _develop_buildsystem_exposed_make_vars:

Makefile variables passed by make command
-----------------------------------------

In HummingBird SDK build system, we exposed the following Makefile variables
which can be passed via make command.

* :ref:`develop_buildsystem_var_soc`
* :ref:`develop_buildsystem_var_board`
* :ref:`develop_buildsystem_var_download`
* :ref:`develop_buildsystem_var_core`
* :ref:`develop_buildsystem_var_simulation`
* :ref:`develop_buildsystem_var_gdb_port`
* :ref:`develop_buildsystem_var_v`
* :ref:`develop_buildsystem_var_silent`

.. note::

   * These variables can also be used and defined in application Makefile
   * If you just want to fix your running board of your application, you can
     just define these variables in application Makefile, if defined, then
     you can simply use ``make clean``, ``make upload`` or ``make debug``, etc.


.. _develop_buildsystem_var_soc:

SOC
~~~

**SOC** variable is used to declare which SoC is used in application during compiling.

You can easily find the supported SoCs in the **<HBIRD_SDK_ROOT>/SoC** directory.

Currently we support the following SoCs, see :ref:`table_dev_buildsystem_1`.

.. _table_dev_buildsystem_1:

.. list-table:: Supported SoCs
   :widths: 10, 60
   :header-rows: 1
   :align: center

   * - **SOC**
     - Reference
   * - hbird
     - :ref:`design_soc_hbird`
   * - hbirdv2
     - :ref:`design_soc_hbirdv2`

.. _develop_buildsystem_var_board:

BOARD
~~~~~

**Board** variable is used to declare which Board is used in application during compiling.

The **BOARD** variable should match the supported boards of chosen **SOC**.
You can easily find the supported Boards in the **<HBIRD_SDK_ROOT>/<SOC>/Board/** directory.

* :ref:`table_dev_buildsystem_2`
* :ref:`table_dev_buildsystem_3`

Currently we support the following Boards.


.. _table_dev_buildsystem_2:

.. list-table:: Supported Boards when SOC=hbird
   :widths: 10 60
   :header-rows: 1
   :align: center

   * - **BOARD**
     - Reference
   * - hbird_eval
     - :ref:`design_board_hbird_eval`


.. _table_dev_buildsystem_3:

.. list-table:: Supported Boards when SOC=hbirdv2
   :widths: 10 60
   :header-rows: 1
   :align: center

   * - **BOARD**
     - Reference
   * - hbird_ddr_200t
     - :ref:`design_board_ddr200t`
   * - hbird_mcu_200t
     - :ref:`design_board_mcu200t`

.. note::

    * If you only specify **SOC** variable in make command, it will use default **BOARD**
      and **CORE** option defined in Makefile.soc.<SOC>

.. _develop_buildsystem_var_download:

DOWNLOAD
~~~~~~~~

**DOWNLOAD** variable is used to declare the download mode of the application,
currently it has these modes supported as described in table
:ref:`table_dev_buildsystem_5`

.. _table_dev_buildsystem_5:

.. list-table:: Supported download modes
   :widths: 10 70
   :header-rows: 1
   :align: center

   * - **DOWNLOAD**
     - Description
   * - ilm
     - | Program will be download into ilm/ram and
       | run directly in ilm/ram, program lost when poweroff
   * - flash
     - | Program will be download into flash, when running,
       | program will be copied to ilm/ram and run in ilm/ram
   * - flashxip
     - Program will to be download into flash and run directly in Flash

.. note::

    * :ref:`design_soc_hbird` support all the download modes.
    * **flashxip** mode in :ref:`design_soc_hbird` is very slow due to
      the CORE frequency is very slow, and Flash speed is slow

.. _develop_buildsystem_var_core:

CORE
~~~~

**CORE** variable is used to declare the HummingBird RISC-V processor core
of the application.

Currently it has these cores supported as described in table
:ref:`table_dev_buildsystem_6`.

.. _table_dev_buildsystem_6:

.. table:: Supported HummingBird RISC-V Processor cores
   :widths: 20 20 20
   :align: center

   ========  ========== =======
   **CORE**  **ARCH**   **ABI**
   e203e     rv32eac    ilp32e
   e203      rv32imac   ilp32
   ========  ========== =======

.. _develop_buildsystem_var_simulation:

SIMULATION
~~~~~~~~~~

If **SIMULATION=1**, it means the program is optimized for hardware simulation environment.

Currently if **SIMULATION=1**, it will pass compile option **-DCFG_SIMULATION**,
application can use this **CFG_SIMULATION** to optimize program for hardware
simulation environment.

.. note::

   * Currently the benchmark applications in **application/baremetal/benchmark** used this optimization

.. _develop_buildsystem_var_gdb_port:

GDB_PORT
~~~~~~~~

.. note::

    * This new variable **GDB_PORT** is added in HummingBird SDK since version ``0.2.4``

This variable is not used usually, by default the **GDB_PORT** variable is ``3333``.

If you want to change a debug gdb port for openocd and gdb when run ``run_openocd`` and
``run_gdb`` target, you can pass a new port such as ``3344`` to this variable.

For example, if you want to debug application using run_openocd and
run_gdb and specify a different port other than ``3333``.

You can do it like this, take ``hbird_eval`` board for example, such as port ``3344``:

* Open openocd server: ``make SOC=hbird BOARD=hbird_eval CORE=e203 GDB_PORT=3344 run_openocd``

* connect gdb with openocd server: ``make SOC=hbird BOARD=hbird_eval CORE=e203 GDB_PORT=3344 run_gdb``


BANNER
~~~~~~

If **BANNER=0**, when program is rebuilt, then the banner message print in console will not be print,
banner print is default enabled via ``HBIRD_BANNER=1`` in ``hbird_sdk_hal.h``.

when ``BANNER=0``, an macro ``-DHBIRD_BANNER=0`` will be passed in Makefile.

The banner message looks like this:

.. code-block:: c

    HummingBird SDK Build Time: Jul 23 2021, 10:22:50
    Download Mode: ILM
    CPU Frequency 15999959 Hz

.. _develop_buildsystem_var_v:

V
~

If **V=1**, it will display compiling message in verbose including compiling options.

By default, no compiling options will be displayed in make console message just to print
less message and make the console message cleaner. If you want to see what compiling option
is used, please pass **V=1** in your make command.

.. _develop_buildsystem_var_silent:

SILENT
~~~~~~

If **SILENT=1**, it will not display any compiling messsage.

If you don't want to see any compiling message, you can pass **SILENT=1** in your make command.

.. _develop_buildsystem_app_make_vars:

Makefile variables used only in Application Makefile
----------------------------------------------------

The following variables should be used in application Makefile at your demand,
e.g. ``application/baremetal/timer_test/Makefile``.

* :ref:`develop_buildsystem_var_target`
* :ref:`develop_buildsystem_var_hbird_sdk_root`
* :ref:`develop_buildsystem_var_rtos`
* :ref:`develop_buildsystem_var_middleware`
* :ref:`develop_buildsystem_var_pfloat`
* :ref:`develop_buildsystem_var_newlib`
* :ref:`develop_buildsystem_var_nogc`
* :ref:`develop_buildsystem_var_rtthread_msh`

.. _develop_buildsystem_var_target:

TARGET
~~~~~~

This is a necessary variable which must be defined in application Makefile.

It is used to set the name of the application, it will affect the generated
target filenames.

.. _develop_buildsystem_var_hbird_sdk_root:

HBIRD_SDK_ROOT
~~~~~~~~~~~~~~

This is a necessary variable which must be defined in application Makefile.

It is used to set the path of HummingBird SDK Root, usually it should be set as
relative path, but you can also set absolute path to point to HummingBird SDK.

.. _develop_buildsystem_var_rtos:

RTOS
~~~~

**RTOS** variable is used to choose which RTOS will be used in this application.

You can easily find the supported RTOSes in the **<HBIRD_SDK_ROOT>/OS** directory.

* If **RTOS** is not defined, then baremetal service will be enabled with this application.
  See examples in ``application/baremetal``.
* If **RTOS** is set the the following values, RTOS service will be enabled with this application.

  - ``FreeRTOS``: FreeRTOS service will be enabled, you can include FreeRTOS header files now, and
    use FreeRTOS API, for ``FreeRTOS`` application, you need to have an ``FreeRTOSConfig.h`` header file
    prepared in you application. See examples in ``application/freertos``.
  - ``UCOSII``: UCOSII service will be enabled, you can include UCOSII header files now, and
    use UCOSII API, for ``UCOSII`` application, you need to have ``app_cfg.h``, ``os_cfg.h``
    and ``app_hooks.c`` files prepared in you application. See examples in ``application/ucosii``.
  - ``RTThread``: RT-Thread service will be enabled, you can include RT-Thread header files now, and
    use RT-Thread API, for ``UCOSII`` application, you need to have an ``rtconfig.h`` header file
    prepared in you application. See examples in ``application/rtthread``.


.. _develop_buildsystem_var_middleware:

MIDDLEWARE
~~~~~~~~~~

**MIDDLEWARE** variable is used to select which middlewares should be used in this application.

You can easily find the available middleware components in the **<HBIRD_SDK_ROOT>/Components** directory.

* If **MIDDLEWARE** is not defined, not leave empty, no middlware package will be selected.
* If **MIDDLEWARE** is defined with more than 1 string, such as ``fatfs tjpgd``, then these two
  middlewares will be selected.

.. _develop_buildsystem_var_pfloat:

PFLOAT
~~~~~~

**PFLOAT** variable is used to enable floating point value print when using the newlib nano(**NEWLIB=nano**).

If you don't use newlib nano, this variable will have no affect.

.. _develop_buildsystem_var_newlib:

NEWLIB
~~~~~~

**NEWLIB** variable is used to select which newlib version will be chosen.

If **NEWLIB=nano**, then newlib nano will be selected. About newlib, please
visit https://sourceware.org/newlib/README.

If **NEWLIB=**, then normal newlib will be used.


.. _develop_buildsystem_var_nogc:

NOGC
~~~~

**NOGC** variable is used to control whether to enable gc sections to reduce program
code size or not, by default GC is enabled to reduce code size.

When GC is enabled, these options will be added:

* Adding to compiler options: ``-ffunction-sections -fdata-sections``
* Adding to linker options: ``-Wl,--gc-sections -Wl,--check-sections``

If you don't want disable this GC feature, you can set **NOGC=1**, GC feature will
remove sections for you, but sometimes it might remove sections that are useful,
e.g. For HummingBird SDK test cases, we use ctest framework, and we need to set **NOGC=1**
to disable GC feature.

.. _develop_buildsystem_var_rtthread_msh:

RTTHREAD_MSH
~~~~~~~~~~~~

**RTTHREAD_MSH** variable is valid only when **RTOS** is set to **RTThread**.

When **RTTHREAD_MSH** is set to **1**:

* The RTThread MSH component source code will be included
* The MSH thread will be enabled in the background
* Currently the msh getchar implementation is using a weak function implemented
  in ``rt_hw_console_getchar`` in ``OS/RTTThread/libcpu/risc-v/nuclei/cpuport.c``

.. _develop_buildsystem_app_build_vars:

Build Related Makefile variables used only in Application Makefile
------------------------------------------------------------------

If you want to specify additional compiler flags, please follow this guidance
to modify your application Makefile.

HummingBird SDK build system defined the following variables to control the
build options or flags.

* :ref:`develop_buildsystem_var_incdirs`
* :ref:`develop_buildsystem_var_c_incdirs`
* :ref:`develop_buildsystem_var_cxx_incdirs`
* :ref:`develop_buildsystem_var_asm_incdirs`
* :ref:`develop_buildsystem_var_srcdirs`
* :ref:`develop_buildsystem_var_c_srcdirs`
* :ref:`develop_buildsystem_var_cxx_srcdirs`
* :ref:`develop_buildsystem_var_asm_srcdirs`
* :ref:`develop_buildsystem_var_c_srcs`
* :ref:`develop_buildsystem_var_cxx_srcs`
* :ref:`develop_buildsystem_var_asm_srcs`
* :ref:`develop_buildsystem_var_common_flags`
* :ref:`develop_buildsystem_var_cflags`
* :ref:`develop_buildsystem_var_cxxflags`
* :ref:`develop_buildsystem_var_asmflags`
* :ref:`develop_buildsystem_var_ldflags`
* :ref:`develop_buildsystem_var_ldlibs`
* :ref:`develop_buildsystem_var_libdirs`
* :ref:`develop_buildsystem_var_linker_script`

.. _develop_buildsystem_var_incdirs:

INCDIRS
~~~~~~~

This **INCDIRS** is used to pass C/CPP/ASM include directories.

e.g. To include current directory ``.`` and ``inc`` for C/CPP/ASM

.. code-block:: makefile

    INCDIRS = . inc


.. _develop_buildsystem_var_c_incdirs:

C_INCDIRS
~~~~~~~~~

This **C_INCDIRS** is used to pass C only include directories.

e.g. To include current directory ``.`` and ``cinc`` for C only

.. code-block:: makefile

    C_INCDIRS = . cinc


.. _develop_buildsystem_var_cxx_incdirs:

CXX_INCDIRS
~~~~~~~~~~~

This **CXX_INCDIRS** is used to pass CPP only include directories.

e.g. To include current directory ``.`` and ``cppinc`` for CPP only

.. code-block:: makefile

    CXX_INCDIRS = . cppinc


.. _develop_buildsystem_var_asm_incdirs:

ASM_INCDIRS
~~~~~~~~~~~

This **ASM_INCDIRS** is used to pass ASM only include directories.

e.g. To include current directory ``.`` and ``asminc`` for ASM only

.. code-block:: makefile

    ASM_INCDIRS = . asminc


.. _develop_buildsystem_var_srcdirs:

SRCDIRS
~~~~~~~

This **SRCDIRS** is used to set the source directories used to search
the C/CPP/ASM source code files, it will not do recursively.

e.g. To search C/CPP/ASM source files in directory ``.`` and ``src``

.. code-block:: makefile

    SRCDIRS = . src


.. _develop_buildsystem_var_c_srcdirs:

C_SRCDIRS
~~~~~~~~~

This **C_SRCDIRS** is used to set the source directories used to search
the C only source code files(*.c, *.C), it will not do recursively.

e.g. To search C only source files in directory ``.`` and ``csrc``

.. code-block:: makefile

    C_SRCDIRS = . csrc


.. _develop_buildsystem_var_cxx_srcdirs:

CXX_SRCDIRS
~~~~~~~~~~~

This **CXX_SRCDIRS** is used to set the source directories used to search
the CPP only source code files(*.cpp, *.CPP), it will not do recursively.

e.g. To search CPP only source files in directory ``.`` and ``cppsrc``

.. code-block:: makefile

    CXX_SRCDIRS = . cppsrc


.. _develop_buildsystem_var_asm_srcdirs:

ASM_SRCDIRS
~~~~~~~~~~~

This **ASM_SRCDIRS** is used to set the source directories used to search
the ASM only source code files(*.s, *.S), it will not do recursively.

e.g. To search ASM only source files in directory ``.`` and ``asmsrc``

.. code-block:: makefile

    ASM_SRCDIRS = . asmsrc


.. _develop_buildsystem_var_c_srcs:

C_SRCS
~~~~~~

If you just want to include a few of C source files in directories, you can use this
**C_SRCS** variable.

e.g. To include ``main.c`` and ``src/hello.c``

.. code-block:: makefile

    C_SRCS = main.c src/hello.c

.. _develop_buildsystem_var_cxx_srcs:

CXX_SRCS
~~~~~~~~

If you just want to include a few of CPP source files in directories, you can use this
**CXX_SRCS** variable.

e.g. To include ``main.cpp`` and ``src/hello.cpp``

.. code-block:: makefile

    CXX_SRCS = main.cpp src/hello.cpp


.. _develop_buildsystem_var_asm_srcs:

ASM_SRCS
~~~~~~~~

If you just want to include a few of ASM source files in directories, you can use this
**ASM_SRCS** variable.

e.g. To include ``asm.s`` and ``src/test.s``

.. code-block:: makefile

    ASM_SRCS = asm.s src/test.s

.. _develop_buildsystem_var_common_flags:

COMMON_FLAGS
~~~~~~~~~~~~

This **COMMON_FLAGS** variable is used to define common compiler flags to all c/asm/cpp compiler.

For example, you can add a newline ``COMMON_FLAGS += -O3 -funroll-loops -fpeel-loops``
in your application Makefile and these options will be passed to C/ASM/CPP compiler.


.. _develop_buildsystem_var_cflags:

CFLAGS
~~~~~~

Different to **COMMON_FLAGS**, this **CFLAGS** variable is used to define common compiler flags to C compiler only.

For example, you can add a newline ``CFLAGS += -O3 -funroll-loops -fpeel-loops``
in your application Makefile and these options will be passed to C compiler.

.. _develop_buildsystem_var_cxxflags:

CXXFLAGS
~~~~~~~~

Different to **COMMON_FLAGS**, this **CXXFLAGS** variable is used to define common compiler flags to cpp compiler only.

For example, you can add a newline ``CXXFLAGS += -O3 -funroll-loops -fpeel-loops``
in your application Makefile and these options will be passed to cpp compiler.

.. _develop_buildsystem_var_asmflags:

ASMFLAGS
~~~~~~~~

Different to **COMMON_FLAGS**, this **ASMFLAGS** variable is used to define common compiler flags to asm compiler only.

For example, you can add a newline ``ASMFLAGS += -O3 -funroll-loops -fpeel-loops``
in your application Makefile and these options will be passed to asm compiler.

.. _develop_buildsystem_var_ldflags:

LDFLAGS
~~~~~~~

This **LDFLAGS** is used to pass extra linker flags, for example,
if you want to link extra math library, you can add a newline
``LDFLAGS += -lm`` in you application Makefile.

Libraries (-lfoo) could also be added to the LDLIBS variable instead.

.. _develop_buildsystem_var_ldlibs:

LDLIBS
~~~~~~

This **LDLIBS** variable is library flags or names given to compilers
when they are supposed to invoke the linker.

Non-library linker flags, such as -L, should go in the **LDFLAGS** variable.

.. _develop_buildsystem_var_libdirs:

LIBDIRS
~~~~~~~

This **LIBDIRS** variable is used to store the library directories, which could
be used together with **LDLIBS**.

For example, if you have a library located in **$(HBIRD_SDK_ROOT)/Library/DSP/libnmsis_dsp_rv32imac.a**,
and you want to link it, then you can define these lines:

.. code-block:: makefile

   LDLIBS = -lnmsis_dsp_rv32imac
   LIBDIRS = $(HBIRD_SDK_ROOT)/Library/DSP

.. _develop_buildsystem_var_linker_script:

LINKER_SCRIPT
~~~~~~~~~~~~~

This **LINKER_SCRIPT** variable could be used to set the link script of the application.

By default, there is no need to set this variable, since the build system will define
a default linker script for application according to the build configuration. If you want
to define your own linker script, you can set this variable.

For example, ``LINKER_SCRIPT := gcc.ld``.


.. _GNU Make Standard Library (GMSL): http://sourceforge.net/projects/gmsl/
