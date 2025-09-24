Inference on Hardware using ONNX Runtime Python APIs
====================================================

Connect to the Board
--------------------

Please refer to the :doc:`board_setup` to setup and boot the VEK385 board.

Configure the Environment
-------------------------

1. After the board has been booted, log in using the username: `root`.

2. Copy `cert.elf` from `amd/vaiml_models` directory in `vitis_ai_2025.1_web_vek385.tar` to the board. `cert.elf` needs to be copied as `cert_ve2.elf`

3. Execute the following commands on the board to configure the environment:

   .. code-block:: bash

      echo 1 > /sys/module/rcupdate/parameters/rcu_cpu_stall_suppress
      export XRT_AIARM=true
      mkdir -p /lib/firmware/amdnpu
      # cert.elf is copied and renamed as cert_ve2.elf
      cp amd/vaiml_models/cert.elf /lib/firmware/amdnpu/cert_ve2.elf
      rmmod aiarm
      modprobe aiarm enable_polling=0
      export LD_LIBRARY_PATH=/usr/lib/python3.12/site-packages/voe/lib/:/usr/lib/python3.12/site-packages/flexmlrt/lib/
      export XLNX_ENABLE_CACHE=0
      export XRT_ELF_FLOW=1

An alternate way is to execute `runtime_env.sh` to configure the environment. This setup script is shared as part of the prebuilt ResNet50 example `/mnt/ResNet50/runtime_env.sh`

Run the Application
-------------------

After copying the compiled model to the board, run the application:

.. code-block:: bash

   python3 <running_script_name>.py

During the execution of the Python script, the ONNX session automatically detects the presence of a pre-compiled model within the current directory, thereby bypassing any model recompilation process.
