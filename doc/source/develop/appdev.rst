.. _develop_appdev:

Application Development
=======================

.. _develop_appdev_overview:

Overview
--------

Here will describe how to develop an HummingBird SDK application.

To develop a HummingBird SDK application from scratch, you can do the following steps:

1. Create a directory to place your application code.
2. Create **Makefile** in the new created directory, the minimal **Makefile** should look like this

   .. code-block:: makefile
      :linenos:

       TARGET = your_target_name

       HBIRD_SDK_ROOT = path/to/your_hbird_sdk_root

       SRCDIRS = .

       INCDIRS = .

       include $(HBIRD_SDK_ROOT)/Build/Makefile.base

3. Copy or create your application code in new created directory.

   .. note::

      * If you just want to SoC related resource, you can include header file ``hbird_sdk_soc.h`` in your application code.
      * If you just want to SoC and Board related resource, you can include header file ``hbird_sdk_hal.h`` in your application code.
      * For simplity, we recomment you to use ``hbird_sdk_hal.h`` header file

4. Follow :ref:`develop_buildsystem` to change your application Makefile.

.. _develop_appdev_addsrc:

Add Extra Source Code
---------------------

If you want to add extra source code, you can use these makefile variables:

To add all the source code in directories, recursive search is not supported.
  * :ref:`develop_buildsystem_var_srcdirs`: Add C/CPP/ASM source code located
    in the directories defined by this variable.

  * :ref:`develop_buildsystem_var_c_srcdirs`: Add C only source code located
    in the directories defined by this variable.

  * :ref:`develop_buildsystem_var_cxx_srcdirs`: Add CPP only source code located
    in the directories defined by this variable.

  * :ref:`develop_buildsystem_var_asm_srcdirs`: Add ASM only source code located
    in the directories defined by this variable.

To add only selected source code in directory
  * :ref:`develop_buildsystem_var_c_srcs`: Add C only source code files defined by this variable.
  * :ref:`develop_buildsystem_var_cxx_srcs`: Add CPP only source code files defined by this variable.
  * :ref:`develop_buildsystem_var_asm_srcs`: Add ASM only source code files defined by this variable.

.. _develop_appdev_addinc:

Add Extra Include Directory
---------------------------

If you want to add extra include directories, you can use these makefile variables:

* :ref:`develop_buildsystem_var_incdirs`: Include the directories defined by
  this variable for C/ASM/CPP code during compiling.
* :ref:`develop_buildsystem_var_c_incdirs`: Include the directories defined by
  this variable for C only code during compiling.
* :ref:`develop_buildsystem_var_cxx_incdirs`: Include the directories defined by
  this variable for CPP only code during compiling.
* :ref:`develop_buildsystem_var_asm_incdirs`: Include the directories defined by
  this variable for ASM only code during compiling.

.. _develop_appdev_addoptions:

Add Extra Build Options
-----------------------

If you want to add extra build options, you can use these makefile variables:

* :ref:`develop_buildsystem_var_common_flags`: This will add compiling flags
  for C/CPP/ASM source code.
* :ref:`develop_buildsystem_var_cflags`: This will add compiling flags
  for C source code.
* :ref:`develop_buildsystem_var_cxxflags`: This will add compiling flags
  for CPP source code.
* :ref:`develop_buildsystem_var_asmflags`: This will add compiling flags
  for ASM source code.
* :ref:`develop_buildsystem_var_ldflags`: This will add linker flags when linking.
* :ref:`develop_buildsystem_var_ldlibs`: This will add extra libraries need to be linked.
* :ref:`develop_buildsystem_var_libdirs`: This will add extra library directories to be searched by linker.

.. _develop_appdev_optimize_for_codesize:

Optimize For Code Size
----------------------

If you want to optimize your application for code size, you set ``COMMON_FLAGS``
in your application Makefile like this:

.. code-block:: makefile

    COMMON_FLAGS := -Os

If you want to optimize code size even more, you use this link time optimization(LTO) as below:

.. code-block:: makefile

    COMMON_FLAGS := -Os -flto

see :ref:`design_app_demo_plic` for example usage of optimize for code size.

For more details about gcc optimization, please refer to `Options That Control Optimization in GCC`_.

.. _develop_appdev_linkscript:

Change Link Script
------------------

If you want to change the default link script defined by your make configuration(SOC, BOARD, DOWNLOAD).
You can use :ref:`develop_buildsystem_var_linker_script` variable to set your linker script.

.. _develop_appdev_setdefaultmake:

Set Default Make Options
------------------------

Set Default Global Make Options For HummingBird SDK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to change the global Make options for the HummingBird SDK,
you can add the :ref:`develop_buildsystem_makefile_global`.


Set Local Make Options For Your Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you want to change the application level Make options,
you can add the :ref:`develop_buildsystem_makefile_local`.


.. _Options That Control Optimization in GCC: https://gcc.gnu.org/onlinedocs/gcc-9.2.0/gcc/Optimize-Options.html#Optimize-Options
