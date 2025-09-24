ONNX Runtime C++ Application Example
====================================

This tutorial illustrates how to compile an ONNX Runtime C++ application, and run the application on a VEK385 board. 

File Preparation 
-----------------

1. Obtain the ResNet50 example, which includes both Python scripts and C++ source code, packaged in:

	* resnet50_model.tar.gz

2. On your host machine, extract the contents to your working directory and set the appropriate access permissions:

.. code-block::

	tar xvf resnet50_model.tar.gz -C <working directory>
	chmod -R a+w <working directory>

C++ Application Compilation
---------------------------

To build the C++ application, follow these steps:

3. Start the Docker environment as outlined in the  :doc:`docker-setup` instructions. 
   Inside the Docker container, configure the SDK environment::

.. code-block::
	
	unset LD_LIBRARY_PATH
	source /opt/xilinx/arm_sdk/environment-setup-cortexa72-cortexa53-amd-linux

4. Compile and link the host application using the following commands:

.. code-block::

	/opt/xilinx/arm_sdk/sysroots/x86_64-amdedfsdk-linux/usr/bin/aarch64-amd-linux/aarch64-amd-linux-g++   -mcpu=cortex-a72.cortex-a53+crc -mbranch-protection=standard -fstack-protector-strong  -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux  -I/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/include -I/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/include/core/session  -O2 -pipe -g -feliminate-unused-debug-types  -o ve2_ortCppApi_modelrun.o -c ./ve2_ortCppApi_modelrun.cpp

	/opt/xilinx/arm_sdk/sysroots/x86_64-amdedfsdk-linux/usr/bin/aarch64-amd-linux/aarch64-amd-linux-g++   -mcpu=cortex-a72.cortex-a53+crc -mbranch-protection=standard -fstack-protector-strong  -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux  -O2 -pipe -g -feliminate-unused-debug-types  -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed  -Wl,-z,relro,-z,now -rdynamic "ve2_ortCppApi_modelrun.o" -o model-app.elf   -L/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/lib  -Wl,-rpath,/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/lib -lonnxruntime 
	
Compiling the Model 
-------------------

To compile the ResNet50 example, follow the steps:

5. Restart the docker. That is to ensure the environment setting is clean. Inside the docker, run following steps:

.. code-block::

	source /opt/xilinx/arm_env.bash
	cd <working directory>/resnet50_model
	python3 download_ResNet.py
	python3 quantize_xint8.py 
	python3 compile.py
	
Model Deployment with C++ Application
-------------------------------------

To deploy the compiled model with the C++ application:

6. To deploy the compiled model and perform inference on the VEK385 board:

- Ensure the VEK385 board is setup as outlined in the  :doc:`board_setup` instructions.

- Transfer the resnet50_model directory to the board.

- Execute inference using the compiled C++ application

Once the board has been booted up and resnet50_model directory transferred to the board, run the commands below:

.. code-block::

	cd <working directory>/resnet50_model
	./model-app.elf resnet50_quantized_xint8.onnx input0.bin output0.bin

Example output:

.. code-block::

	I20250108 18:49:43.727761   875 vitisai_compile_model.cpp:1157] Vitis AI EP Load ONNX Model Success
	I20250108 18:49:43.727855   875 vitisai_compile_model.cpp:1158] Graph Input Node Name/Shape (1)
	I20250108 18:49:43.727872   875 vitisai_compile_model.cpp:1162] 	 input : [-1x3x224x224]
	I20250108 18:49:43.727887   875 vitisai_compile_model.cpp:1168] Graph Output Node Name/Shape (1)
	I20250108 18:49:43.727897   875 vitisai_compile_model.cpp:1172] 	 output : [-1x1000]
	[Vitis AI EP] No. of Operators : VAIML   490 VITIS_EP_CPU     2 
	[Vitis AI EP] No. of Subgraphs : VAIML     1 
	......
	open : DEV name  /dev/accel/accel0
	Average inference time over 100 runs: 8.56754 ms
	Saved to output0.bin
	
Alternatively, you can run inference using the python implementation:

.. code-block::

	cd <working directory>/resnet50_model
	python runmodel.py

Both `resnet50_model/runmodel.py` (Python) and `resnet50_model/ve2_ortCppApi_modelrun.cpp` (C++) implement the same model inference functionality, and can be cross-referenced to understand the equivalent workflow and code structure in either language.