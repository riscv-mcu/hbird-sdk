.. _faq:

FAQ
===

Why I can't download application in Windows?
--------------------------------------------

If you met the following issue as below message showed:

.. code-block:: console

    Nuclei OpenOCD, 64-bit Open On-Chip Debugger 0.10.0+dev-00014-g0eae03214 (2019-12-12-07:43)
    Licensed under GNU GPL v2
    For bug reports, read
            http://openocd.org/doc/doxygen/bugs.html
    Remote communication error.  Target disconnected.: Success.
    "monitor" command not supported by this target.
    "monitor" command not supported by this target.
    "monitor" command not supported by this target.
    You can't do that when your target is ``exec'
    "monitor" command not supported by this target.
    "monitor" command not supported by this target.
    "Successfully uploaded hello_world.elf "


Please check whether your driver is installed successfully as the board user manual described,
especially, for **HummingBird Evaluation** boards, you need to download the
**HummingBird Debugger Windows Driver** from https://nucleisys.com/developboard.php, and install it.

.. note::

    The USB driver might lost when you re-plug the USB port, you might need to reinstall the driver.


Why I can't download application in Linux?
------------------------------------------

Please check that whether you have followed the board user manual to setup the USB JTAG drivers correctly.
The windows steps and linux steps are different, please take care.


Why the provided application is not running correctly in my HummingBird Evaluation Board?
-----------------------------------------------------------------------------------------

Please check the following items:

1. Did you program the correct HummingBird Evaluation FPGA bitstream?
2. Did you re-power the board, when you just programmed the board with FPGA bitstream?
3. Did you choose the right **CORE** as the HummingBird Evaluation FPGA bitstream present?
4. If your application is RTOS demos, did you run in ``flashxip`` mode, if yes, it is expected
   due to flash speed is really slow, you'd better try ``ilm`` or ``flash`` mode.
5. If still not working, you might need to check whether the FPGA bitstream is correct or not?
