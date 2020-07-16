.. _design_rtos:

RTOS
====

.. _design_rtos_overview:

Overview
--------

In HummingBird SDK, we have support three most-used RTOSes in the world,
**FreeRTOS**, **UCOSII** and **RT-Thread** from China.

If you want to use RTOS in your application, you can choose one
of the supported RTOSes.

.. note::

    When you want to develop RTOS application in HummingBird SDK, please
    don't reconfigure ``SysTimer`` and ``SysTimer Software Interrupt``,
    since it is already used by RTOS portable code.

.. _design_rtos_freertos:

FreeRTOS
--------

`FreeRTOS`_ is a market-leading real-time operating system (RTOS) for
microcontrollers and small microprocessors.

In our FreeRTOS portable code, we are using ``SysTimer Interrupt`` as RTOS SysTick
Interrupt, and using ``SysTimer Software Interrupt`` to do task switch.

These two interrupts are kept as lowest level, and ``SysTimer Interrupt``
is initialized as core internal interrupt, and ``SysTimer Software Interrupt``
is initialized as core internal interrupt.

If you want to learn about how to use FreeRTOS APIs, you need to go to
its website to learn the FreeRTOS documentation in its website.

In HummingBird SDK, if you want to use **FreeRTOS** in your application, you need
to add ``RTOS = FreeRTOS`` in your application Makefile.

And in your application code, you need to do the following things:

* Add FreeRTOS configuration file -> ``FreeRTOSConfig.h``
* Include FreeRTOS header files

.. note::

    * You can check the ``application\freertos\demo`` for reference
    * Current version of FreeRTOS used in HummingBird SDK is ``V10.3.1``
    * If you want to change the OS ticks per seconds, you can change the ``configTICK_RATE_HZ``
      defined in ``FreeRTOSConfig.h``

More information about FreeRTOS get started, please click
https://www.freertos.org/FreeRTOS-quick-start-guide.html

.. _design_rtos_ucosii:

UCOSII
------

`UCOSII`_ a priority-based preemptive real-time kernel for microprocessors,
written mostly in the programming language C. It is intended for use in embedded systems.

In our UCOSII portable code, we are using ``SysTimer Interrupt`` as RTOS SysTick
Interrupt, and using ``SysTimer Software Interrupt`` to do task switch.

If you want to learn about ``UCOSII``, please click https://www.micrium.com/books/ucosii/

We are using the opensource version of UC-OS2 source code from https://github.com/SiliconLabs/uC-OS2,
with optimized code for HummingBird RISC-V processors.

In HummingBird SDK, if you want to use **UCOSII** in your application, you need
to add ``RTOS = UCOSII`` in your application Makefile.

And in your application code, you need to do the following things:

* Add UCOSII application configuration header file -> ``app_cfg.h`` and ``os_cfg.h``
* Add application hook source file -> ``app_hooks.c``
* Include UCOSII header files

.. note::

    * You can check the ``application\ucosii\demo`` for reference
    * The UCOS-II application configuration template files can also be found in
      https://github.com/SiliconLabs/uC-OS2/tree/master/Cfg/Template
    * Current version of UCOSII used in HummingBird SDK is ``V2.93.00``
    * If you want to change the OS ticks per seconds, you can change the ``OS_TICKS_PER_SEC``
      defined in ``os_cfg.h``


.. warning::

   * For HummingBird SDK release > v0.2.2, the UCOSII source code is replaced using the
     version from https://github.com/SiliconLabs/uC-OS2/, and application development
     for UCOSII is also changed, the ``app_cfg.h``, ``os_cfg.h`` and ``app_hooks.c`` files
     are required in application source code.


.. _design_rtos_rtthread:

RT-Thread
---------

`RT-Thread`_ RT-Thread was born in 2006, it is an open source, neutral,
and community-based real-time operating system (RTOS).

RT-Thread is mainly written in C language, easy to understand and easy
to port(can be quickly port to a wide range of mainstream MCUs and module chips).

It applies object-oriented programming methods to real-time system design,
making the code elegant, structured, modular, and very tailorable.

In our support for RT-Thread, we get the source code of RT-Thread from a project
called `RT-Thread Nano`_, which only provide kernel code of RT-Thread, which is easy
to be intergated with HummingBird SDK.

In our RT-Thread portable code, we are using ``SysTimer Interrupt`` as RTOS SysTick
Interrupt, and using ``SysTimer Software Interrupt`` to do task switch.

And also the ``rt_hw_board_init`` function is implemented in our portable code.

If you want to learn about ``RT-Thread``, please click:

* For Chinese version, click https://www.rt-thread.org/document/site/
* For English version, click https://github.com/RT-Thread/rt-thread

In HummingBird SDK, if you want to use **RT-Thread** in your application, you need
to add ``RTOS = RTThread`` in your application Makefile.

And in your application code, you need to do the following things:

* Add RT-Thread application configuration header file -> ``rtconfig.h``
* Include RT-Thread header files

.. note::

    * In RT-Thread, the ``main`` function is created as a RT-Thread thread,
      so you don't need to do any OS initialization work, it is done before ``main``


.. _FreeRTOS: https://www.freertos.org/
.. _UCOSII: https://www.micrium.com/
.. _RT_Thread: https://www.rt-thread.org/
.. _RT-Thread Nano: https://github.com/RT-Thread/rtthread-nano
