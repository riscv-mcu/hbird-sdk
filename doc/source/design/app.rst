.. _design_app:

Application
===========

.. _design_app_overview:

Overview
--------

In HummingBird SDK, we just provided applications which can
run in different boards without any changes in code to
demostrate the baremetal service, freertos service and
ucosii service features.

The provided applications can be divided into three categories:

* Bare-metal applications: Located in ``application/baremetal``

* FreeRTOS applications: Located in ``application/freertos``

* UCOSII applications: Located in ``application/ucosii``

If you want to develop your own application in HummingBird SDK, please click
:ref:`develop_appdev` to learn more about it.

The following applications are running using RV-STAR board.

Bare-metal applications
-----------------------

helloworld
~~~~~~~~~~

This `helloworld application`_ is used to print hello world, and also
will check this RISC-V CSR **MISA** register value.

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the helloworld directory
    cd application/baremetal/helloworld
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 12:24:22
    Download Mode: FLASHXIP
    CPU Frequency 109323529 Hz
    MISA: 0x40901105
    MISA: RV32IMACUX
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!
    Hello World!


demo_timer
~~~~~~~~~~

This `demo_timer application`_ is used to demostrate how to use
the CORE TIMER API including the Timer Interrupt and Timer Software Interrupt.

* Both interrupts are registered as non-vector interrupt.
* First the timer interrupt will run for 10 times
* Then the software timer interrupt will start to run for 10 times


**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the demo_timer directory
    cd application/baremetal/demo_timer
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 12:52:37
    Download Mode: FLASHXIP
    CPU Frequency 108794117 Hz
    init timer and start
    MTimer IRQ handler 1
    MTimer IRQ handler 2
    MTimer IRQ handler 3
    MTimer IRQ handler 4
    MTimer IRQ handler 5
    MTimer IRQ handler 6
    MTimer IRQ handler 7
    MTimer IRQ handler 8
    MTimer IRQ handler 9
    MTimer IRQ handler 10
    MTimer SW IRQ handler 1
    MTimer SW IRQ handler 2
    MTimer SW IRQ handler 3
    MTimer SW IRQ handler 4
    MTimer SW IRQ handler 5
    MTimer SW IRQ handler 6
    MTimer SW IRQ handler 7
    MTimer SW IRQ handler 8
    MTimer SW IRQ handler 9
    MTimer SW IRQ handler 10
    MTimer msip and mtip interrupt test finish and pass

.. _design_app_demo_plic:

demo_plic
~~~~~~~~~~

This `demo_plic application`_ is used to demostrate how to use
the PLIC API and Interrupt.

.. note::

    In this application's Makefile, we provided comments in Makefile about optimize
    for code size.

    If you want to optimize this application for code size, you can set the ``COMMON_FLAGS``
    variable to the following values, we recommend to use ``-Os -flto``.

    .. list-table:: Code size optimization for demo_plic on RV-STAR target
       :widths: 60 20 20 20 20
       :header-rows: 1

       * - COMMON_FLAGS
         - text(bytes)
         - data(bytes)
         - bss(bytes)
         - total(bytes)
       * -
         - 13724
         - 112
         - 2266
         - 16102
       * - -flto
         - 13598
         - 112
         - 2266
         - 15976
       * - -Os
         - 9690
         - 112
         - 2264
         - 12066
       * - -Os -flto
         - 9132
         - 112
         - 2264
         - 11508
       * - -Os -msave-restore  -fno-unroll-loops
         - 9714
         - 112
         - 2264
         - 12090
       * - -Os -msave-restore  -fno-unroll-loops -flto
         - 9204
         - 112
         - 2264
         - 11580

* The timer interrupt and timer software interrupt are used
* The timer interrupt is registered as non-vector interrupt
* The timer software interrupt is registered as vector interrupt,
  and we enable its preemptive feature by using ``SAVE_IRQ_CSR_CONTEXT``
  and ``RESTORE_IRQ_CSR_CONTEXT`` in timer software interrupt handler
* The timer interrupt is triggered periodly
* The timer software interrupt is triggered in timer interrupt handler using
  ``SysTimer_SetSWIRQ`` function.
* In the application code, there is a macro called ``SWIRQ_INTLEVEL_HIGHER`` to
  control the timer software interrupt working feature:

  - If **SWIRQ_INTLEVEL_HIGHER=1**, the timer software interrupt level is higher then
    timer interrupt level, so when timer software interrupt is triggerred, then timer
    software interrupt will be processed immediately, and timer interrupt will be preempted
    by timer software interrupt.

  - If **SWIRQ_INTLEVEL_HIGHER=0**, the timer software interrupt level is lower then
    timer interrupt level, so when timer software interrupt is triggerred, then timer
    software interrupt will be processed after timer interrupt, and timer interrupt will
    not be preempted by timer software interrupt.

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the demo_plic directory
    cd application/baremetal/demo_plic
    # Change macro SWIRQ_INTLEVEL_HIGHER value in demo_plic.c
    # to see different working mode of this demo
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output(SWIRQ_INTLEVEL_HIGHER=1) as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 16:35:58
    Download Mode: FLASHXIP
    CPU Frequency 108794117 Hz
    Initialize timer and start timer interrupt periodly
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 0 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run during timer interrupt
    [IN SOFTWARE INTERRUPT]software interrupt hit 0 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    [IN TIMER INTERRUPT]timer interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 1 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run during timer interrupt
    [IN SOFTWARE INTERRUPT]software interrupt hit 1 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    [IN TIMER INTERRUPT]timer interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 2 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run during timer interrupt
    [IN SOFTWARE INTERRUPT]software interrupt hit 2 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    [IN TIMER INTERRUPT]timer interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 3 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run during timer interrupt
    [IN SOFTWARE INTERRUPT]software interrupt hit 3 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    [IN TIMER INTERRUPT]timer interrupt end


**Expected output(SWIRQ_INTLEVEL_HIGHER=0) as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 16:35:58
    Download Mode: FLASHXIP
    CPU Frequency 108794117 Hz
    Initialize timer and start timer interrupt periodly
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 0 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run when timer interrupt finished
    [IN TIMER INTERRUPT]timer interrupt end
    [IN SOFTWARE INTERRUPT]software interrupt hit 0 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 1 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run when timer interrupt finished
    [IN TIMER INTERRUPT]timer interrupt end
    [IN SOFTWARE INTERRUPT]software interrupt hit 1 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 2 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run when timer interrupt finished
    [IN TIMER INTERRUPT]timer interrupt end
    [IN SOFTWARE INTERRUPT]software interrupt hit 2 times
    [IN SOFTWARE INTERRUPT]software interrupt end
    -------------------
    [IN TIMER INTERRUPT]timer interrupt hit 3 times
    [IN TIMER INTERRUPT]trigger software interrupt
    [IN TIMER INTERRUPT]software interrupt will run when timer interrupt finished
    [IN TIMER INTERRUPT]timer interrupt end
    [IN SOFTWARE INTERRUPT]software interrupt hit 3 times
    [IN SOFTWARE INTERRUPT]software interrupt end


demo_dsp
~~~~~~~~

This `demo_dsp application`_ is used to demostrate how to NMSIS-DSP API.

* Mainly show how we can use DSP library without dsp instructions and header files.
* It mainly demo the ``riscv_conv_xx`` functions and its reference functions

.. note::

    * For other HummingBird Processor Core based SoC, please check whether it has DSP
      feature enabled to decide which kind of **NMSIS-DSP** library to use.
    * Even our NMSIS-DSP library with DSP disabled are also optimized, so it can
      also provide good performance in some functions.

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the demo_dsp directory
    cd application/baremetal/demo_dsp
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar DSP_ENABLE=OFF clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar DSP_ENABLE=OFF upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Jun 18 2020, 17:43:31
    Download Mode: FLASHXIP
    CPU Frequency 108270000 Hz
    CSV, riscv_conv_q31, 1225418
    CSV, ref_conv_q31, 2666240
    SUCCESS, riscv_conv_q31
    CSV, riscv_conv_q15, 289940
    CSV, ref_conv_q15, 311158
    SUCCESS, riscv_conv_q15
    CSV, riscv_conv_q7, 463
    CSV, ref_conv_q7, 846
    SUCCESS, riscv_conv_q7
    CSV, riscv_conv_fast_q15, 106293
    CSV, ref_conv_fast_q15, 247938
    SUCCESS, riscv_conv_fast_q15
    CSV, riscv_conv_fast_q31, 490539
    CSV, ref_conv_fast_q31, 2215917
    SUCCESS, riscv_conv_fast_q31
    CSV, riscv_conv_opt_q15, 217250
    CSV, ref_conv_opt_q15, 311162
    SUCCESS, riscv_conv_opt_q15
    CSV, riscv_conv_opt_q7, 714
    CSV, ref_conv_opt_q7, 842
    SUCCESS, riscv_conv_opt_q7
    CSV, riscv_conv_fast_opt_q15, 137252
    CSV, ref_conv_fast_opt_q15, 249958
    SUCCESS, riscv_conv_fast_opt_q15
    all test are passed. Well done!


coremark
~~~~~~~~

This `coremark benchmark application`_ is used to run EEMBC CoreMark Software.

EEMBC CoreMark Software is a product of EEMBC and is provided under the terms of the
CoreMark License that is distributed with the official EEMBC COREMARK Software release.
If you received this EEMBC CoreMark Software without the accompanying CoreMark License,
you must discontinue use and download the official release from www.coremark.org.

In HummingBird SDK, we provided code and Makefile for this ``coremark`` application.
You can also optimize the ``COMMON_FLAGS`` defined in coremark application Makefile
to get different score number.

* By default, this application runs for 500 iterations, you can also change this in Makefile.
  e.g. Change this ``-DITERATIONS=500`` to value such as ``-DITERATIONS=5000``
* macro **PERFORMANCE_RUN=1** is defined
* **PFLOAT = 1** is added in its Makefile to enable float value print

.. note::

   * Since for each SoC platforms, the CPU frequency is different, so user need to change
     the ``ITERATIONS`` defined in Makefile to proper value to let the coremark run at least
     10 seconds
   * For example, for the ``gd32vf103`` based boards supported in HummingBird SDK, we suggest
     to change ``-DITERATIONS=500`` to ``-DITERATIONS=5000``

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the coremark directory
    cd application/baremetal/benchmark/coremark
    # change ITERATIONS value in Makefile for gd32vf103 based board to 5000
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Mar 30 2020, 18:08:53
    Download Mode: FLASHXIP
    CPU Frequency 107190000 Hz
    Start to run coremark for 5000 iterations
    2K performance run parameters for coremark.
    CoreMark Size    : 666
    Total ticks      : 1622809457
    Total time (secs): 15.139593
    Iterations/Sec   : 330.259868
    Iterations       : 5000
    Compiler version : GCC9.2.0
    Compiler flags   : -O2 -flto -funroll-all-loops -finline-limit=600 -ftree-dominator-opts -fno-if-conversion2 -fselective-scheduling -fno-code-hoisting -fno-common -funroll-loops -finline-functions -falign-functions=4 -falign-jumps=4 -falign-loops=4
    Memory location  : STACK
    seedcrc          : 0xe9f5
    [0]crclist       : 0xe714
    [0]crcmatrix     : 0x1fd7
    [0]crcstate      : 0x8e3a
    [0]crcfinal      : 0xbd59
    Correct operation validated. See readme.txt for run and reporting rules.
    CoreMark 1.0 : 330.259868 / GCC9.2.0 -O2 -flto -funroll-all-loops -finline-limit=600 -ftree-dominator-opts -fno-if-conversion2 -fselective-scheduling -fno-code-hoisting -fno-common -funroll-loops -finline-functions -falign-functions=4 -falign-jumps=4 -falign-loops=4 / STACK


    Print Personal Added Addtional Info to Easy Visual Analysis

        (Iterations is: 5000
        (total_ticks is: 1622809457
    (*) Assume the core running at 1 MHz
        So the CoreMark/MHz can be caculated by:
        (Iterations*1000000/total_ticks) = 3.081076 CoreMark/MHz

dhrystone
~~~~~~~~~

This `dhrystone benchmark application`_ is used to run DHRYSTONE Benchmark Software.

The Dhrystone benchmark program has become a popular benchmark for CPU/compiler performance measurement,
in particular in the area of minicomputers, workstations, PC's and microprocesors.

* It apparently satisfies a need for an easy-to-use integer benchmark;
* it gives a first performance indication which is more meaningful than MIPS numbers which,
  in their literal meaning (million instructions per second), cannot be used across different
  instruction sets (e.g. RISC vs. CISC).
* With the increasing use of the benchmark, it seems necessary to reconsider the benchmark and
  to check whether it can still fulfill this function.

In HummingBird SDK, we provided code and Makefile for this ``dhrystone`` application.
You can also optimize the ``COMMON_FLAGS`` defined in dhrystone application Makefile
to get different score number.

* **PFLOAT = 1** is added in its Makefile to enable float value print
* You can change ``Number_Of_Runs`` in ``dhry_1.c`` line 134 to increate or decrease
  number of iterations

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the dhrystone directory
    cd application/baremetal/benchmark/dhrystone
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 14:23:55
    Download Mode: FLASHXIP
    CPU Frequency 108801980 Hz

    Dhrystone Benchmark, Version 2.1 (Language: C)

    Program compiled without 'register' attribute

    Please give the number of runs through the benchmark:
    Execution starts, 500000 runs through Dhrystone
    Execution ends

    Final values of the variables used in the benchmark:

    Int_Glob:            5
            should be:   5
    Bool_Glob:           1
            should be:   1
    Ch_1_Glob:           A
            should be:   A
    Ch_2_Glob:           B
            should be:   B
    Arr_1_Glob[8]:       7
            should be:   7
    Arr_2_Glob[8][7]:    500010
            should be:   Number_Of_Runs + 10
    Ptr_Glob->
      Ptr_Comp:          536883352
            should be:   (implementation-dependent)
      Discr:             0
            should be:   0
      Enum_Comp:         2
            should be:   2
      Int_Comp:          17
            should be:   17
      Str_Comp:          DHRYSTONE PROGRAM, SOME STRING
            should be:   DHRYSTONE PROGRAM, SOME STRING
    Next_Ptr_Glob->
      Ptr_Comp:          536883352
            should be:   (implementation-dependent), same as above
      Discr:             0
            should be:   0
      Enum_Comp:         1
            should be:   1
      Int_Comp:          18
            should be:   18
      Str_Comp:          DHRYSTONE PROGRAM, SOME STRING
            should be:   DHRYSTONE PROGRAM, SOME STRING
    Int_1_Loc:           5
            should be:   5
    Int_2_Loc:           13
            should be:   13
    Int_3_Loc:           7
            should be:   7
    Enum_Loc:            1
            should be:   1
    Str_1_Loc:           DHRYSTONE PROGRAM, 1'ST STRING
            should be:   DHRYSTONE PROGRAM, 1'ST STRING
    Str_2_Loc:           DHRYSTONE PROGRAM, 2'ND STRING
            should be:   DHRYSTONE PROGRAM, 2'ND STRING

     (*) User_Cycle for total run through Dhrystone with loops 500000:
    223500116
           So the DMIPS/MHz can be caculated by:
           1000000/(User_Cycle/Number_Of_Runs)/1757 = 1.273270 DMIPS/MHz

whetstone
~~~~~~~~~

This `whetstone benchmark application`_ is used to run C/C++ Whetstone Benchmark Software
(Single or Double Precision).

The Fortran Whetstone programs were the first general purpose benchmarks that set industry
standards of computer system performance. Whetstone programs also addressed the question
of the efficiency of different programming languages, an important issue not covered by
more contemporary standard benchmarks.

In HummingBird SDK, we provided code and Makefile for this ``whetstone`` application.
You can also optimize the ``COMMON_FLAGS`` defined in whetstone application Makefile
to get different score number.

* **PFLOAT = 1** is added in its Makefile to enable float value print
* Extra **LDFLAGS := -lm** is added in its Makefile to include the math library


**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the whetstone directory
    cd application/baremetal/benchmark/whetstone
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 14:50:15
    Download Mode: FLASHXIP
    CPU Frequency 109069306 Hz

    ##########################################
    Single Precision C Whetstone Benchmark Opt 3 32 Bit
    Calibrate
           1.96 Seconds          1   Passes (x 100)
           9.81 Seconds          5   Passes (x 100)

    Use 5  passes (x 100)

              Single Precision C/C++ Whetstone Benchmark

    Loop content                  Result              MFLOPS      MOPS   Seconds

    N1 floating point -1.12475013732910156         1.053              0.091
    N2 floating point -1.12274742126464844         1.053              0.638
    N3 if then else    1.00000000000000000               108527.617    0.000
    N4 fixed point    12.00000000000000000                   5.630    0.280
    N5 sin,cos etc.    0.49909299612045288                   0.109    3.829
    N6 floating point  0.99999982118606567         1.082              2.493
    N7 assignments     3.00000000000000000                 419.794    0.002
    N8 exp,sqrt etc.   0.75110614299774170                   0.075    2.492

    MWIPS                                              5.089              9.825


    MWIPS/MHz                                          0.046              9.825


FreeRTOS applications
---------------------

demo
~~~~

This `freertos demo application`_ is show basic freertos task functions.

* Two freertos tasks are created
* A software timer is created

In HummingBird SDK, we provided code and Makefile for this ``freertos demo`` application.

* **RTOS = FreeRTOS** is added in its Makefile to include FreeRTOS service
* The **configTICK_RATE_HZ** in ``FreeRTOSConfig.h`` is set to 200, you can change it
  to other number according to your requirement.

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the freertos demo directory
    cd application/freertos/demo
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb HummingBird SDK Build Time: Feb 21 2020, 14:56:00
    Download Mode: FLASHXIP
    CPU Frequency 109058823 Hz
    Before StartScheduler
    task_1
    task1_running.....
    task_2
    task2_running.....
    timers Callback
    timers Callback
    task1_running.....
    task2_running.....
    timers Callback
    timers Callback
    task1_running.....
    task2_running.....
    timers Callback
    timers Callback


UCOSII applications
-------------------

demo
~~~~

This `ucosii demo application`_ is show basic ucosii task functions.

* 4 tasks are created
* 1 task is created first, and then create 3 other tasks and then suspend itself

In HummingBird SDK, we provided code and Makefile for this ``ucosii demo`` application.

* **RTOS = UCOSII** is added in its Makefile to include UCOSII service
* The **OS_TICKS_PER_SEC** in ``os_cfg.h`` is by default set to 200, you can change it
  to other number according to your requirement.

.. note:

   * For HummingBird SDK release > v0.2.2, the UCOSII source code is replaced using the
     version from https://github.com/SiliconLabs/uC-OS2/, and application development
     for UCOSII is also changed, the ``app_cfg.h``, ``os_cfg.h`` and ``app_hooks.c`` files
     are required in application source code.

**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the ucosii demo directory
    cd application/ucosii/demo
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Feb 21 2020, 15:00:35
    Download Mode: FLASHXIP
    CPU Frequency 108524271 Hz
    Start ucosii...
    create start task success
    start all task...
    task3 is running... 1
    task2 is running... 1
    task1 is running... 1
    task3 is running... 2
    task2 is running... 2
    task3 is running... 3
    task2 is running... 3
    task1 is running... 2
    task3 is running... 4
    task2 is running... 4
    task3 is running... 5
    task2 is running... 5
    task1 is running... 3
    task3 is running... 6
    task2 is running... 6
    task3 is running... 7
    task2 is running... 7
    task1 is running... 4
    task3 is running... 8
    task2 is running... 8
    task3 is running... 9
    task2 is running... 9
    task1 is running... 5
    task3 is running... 10
    task2 is running... 10
    task3 is running... 11
    task2 is running... 11
    task1 is running... 6
    task3 is running... 12
    task2 is running... 12


RT-Thread applications
----------------------

demo
~~~~

This `rt-thread demo application`_ is show basic rt-thread thread functions.

* main function is a pre-created thread by RT-Thread
* main thread will create 5 test threads using the same function ``thread_entry``

In HummingBird SDK, we provided code and Makefile for this ``rtthread demo`` application.

* **RTOS = RTThread** is added in its Makefile to include RT-Thread service
* The **RT_TICK_PER_SECOND** in ``rtconfig.h`` is by default set to `200`, you can change it
  to other number according to your requirement.


**How to run this application:**

.. code-block:: shell

    # Assume that you can set up the Tools and HummingBird SDK environment
    # cd to the rtthread demo directory
    cd application/rtthread/demo
    # Clean the application first
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar clean
    # Build and upload the application
    make SOC=gd32vf103 BOARD=gd32vf103v_rvstar upload

**Expected output as below:**

.. code-block:: console

    HummingBird SDK Build Time: Apr 14 2020, 10:14:30
    Download Mode: FLASHXIP
    CPU Frequency 108270000 Hz

    \ | /
    - RT -     Thread Operating System
    / | \     3.1.3 build Apr 14 2020
    2006 - 2019 Copyright by rt-thread team
    Main thread count: 0
    thread 0 count: 0
    thread 1 count: 0
    thread 2 count: 0
    thread 3 count: 0
    thread 4 count: 0
    thread 0 count: 1
    thread 1 count: 1
    thread 2 count: 1
    thread 3 count: 1
    thread 4 count: 1
    Main thread count: 1
    thread 0 count: 2
    thread 1 count: 2
    thread 2 count: 2
    thread 3 count: 2
    thread 4 count: 2
    thread 0 count: 3
    thread 1 count: 3
    thread 2 count: 3
    thread 3 count: 3
    thread 4 count: 3
    Main thread count: 2
    thread 0 count: 4
    thread 1 count: 4


.. _helloworld application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/baremetal/helloworld
.. _demo_timer application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/baremetal/demo_timer
.. _demo_plic application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/baremetal/demo_plic
.. _demo_dsp application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/baremetal/demo_dsp
.. _coremark benchmark application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/benchmark/coremark
.. _dhrystone benchmark application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/benchmark/dhrystone
.. _whetstone benchmark application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/benchmark/whetstone
.. _freertos demo application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/freertos/demo
.. _ucosii demo application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/ucosii/demo
.. _rt-thread demo application: https://github.com/Nuclei-Software/nuclei-sdk/tree/master/application/rtthread/demo
