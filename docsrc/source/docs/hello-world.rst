
Hello World Example
===================

This tutorial illustrates how to compile an ONNX model with the Vitis AI flow, and deploy it on a VEK385 board. It uses `resnet18_bf16_aiemlv2_Jun.zip` file which can be downloaded from `this link <https://account.amd.com/en/forms/downloads/amd-end-user-license-xef.html?filename=resnet18_bf16_aiemlv2_Jun.zip>`__.


Requirements
------------

To build the example and deploy it on board, the following software and hardware are required:

- Host machine with python and docker support
- VEK385 board

For more details, refer to the :doc:`system_requirements` section of this documentation.


Compilation & Deployment Flow
-----------------------------

1. On the host machine, download the tutorial and ensure write access to the tutorial directory:

.. code-block::

	unzip resnet18_bf16_aiemlv2_Jun.zip
	chmod a+w resnet18_bf16


2. Obtain the Docker image with Vitis AI tools pre-installed, and start a container with the tutorial folder mounted into the container:

.. code-block::

	#Load the Docker image onto the host machine:
	docker load -i <Docker Name>.tgz
	#Get the docker “REPOSITORY” and “TAG” to be used:
	docker images
	#Start the docker container with necessary directories mounted:
	docker run -it --rm -v /<HostDir>/resnet18_bf16:/resnet18_bf16  <Docker REPOSITORY:TAG> "bash"

.. note::

	The -v option specifies the host directory to be mapped into the directory inside the docker. Make sure the folder to be written inside the docker has write access to anyone.

3. Inside the docker, parepare the environment for Vitis AI compilation:

.. code-block::

	source /opt/xilinx/arm_env.bash


4. Inside the docker, install python packages required by the example, change directory to the tutorial folder, download Resnet18 model from Hugging Face and export it to ONNX model. This will save the output model to ``models/resnet18.a1_in1k.onnx``:

.. code-block::

	cd /resnet18_bf16
	/usr/bin/python -m pip install -r requirements.txt
	/usr/bin/python export_to_onnx.py

.. note::

	Inside the docker, ``/usr/bin/python`` should be explicitly used to execute the python scripts.


5. Inside the docker, compile the ONNX model with Vitis AI flow:

.. code-block::

	/usr/bin/python compile.py

.. note::

	It takes a few minutes to compile the model.

The input ONNX model name is hardcoded in ``compile.py``.

The number of operators accelerated on the NPU is displayed at the end of the compilation process. The output should look as follows:

.. code-block::

	[Vitis AI EP] No. of Operators : VAIML    49
	[Vitis AI EP] No. of Subgraphs : VAIML     1

6. Follow :doc:`board_setup` to boot up the AIE-ML v2 board, and run following commands in the board to setup environment:

.. code-block::

	echo 1 > /sys/module/rcupdate/parameters/rcu_cpu_stall_suppress
	export XRT_AIARM=true
	mkdir -p /lib/firmware/amdnpu
	#Get cert.elf from vaiml_models in vitis_ai_2025.1_web_vek385.tar
	cp cert.elf /lib/firmware/amdnpu/cert_ve2.elf
	rmmod aiarm
	modprobe aiarm enable_polling=0
	export LD_LIBRARY_PATH=/usr/lib/python3.12/site-packages/voe/lib/:/usr/lib/python3.12/site-packages/flexmlrt/lib/
	export XLNX_ENABLE_CACHE=0
	export XRT_ELF_FLOW=1

7. Run following commands in the board to copy the whole directory ``resnet18_bf16`` to the board (scp example provided), and execute the inference:

.. code-block::

	scp -r <USER NAME>@<HOST MACHINE>:/<path to resnet18_bf16> .
	cd resnet18_bf16
	python runmodel.py

The input ONNX model name is hardcoded in ``runmodel.py``.

The ONNX session will detect the presence of a pre-compiled model in the current directory and use this pre-compiled model for inference instead of compiling the ONNX source model.

The script runs 4 inferences of the model and displays the messages similar to the ones shown below:

.. code-block::

	INFO: [VAIP-VAIML-PASS] Found partition context JSON: my_cache_dir/resnet18.a1_in1k/context.json. Skip partitioning.
	[Vitis AI EP] No. of Operators : VAIML    49
	[Vitis AI EP] No. of Subgraphs : VAIML     1
	open : DEV name  /dev/accel/accel0
	Running 4 inferences, comparing CPU and NPU outputs
	Iteration   1: Max absolute difference = 0.187699, Root mean squared error = 0.073115
	Iteration   2: Max absolute difference = 0.223925, Root mean squared error = 0.080473
	Iteration   3: Max absolute difference = 0.283239, Root mean squared error = 0.094143
	Iteration   4: Max absolute difference = 0.214051, Root mean squared error = 0.079027	
	Inference Done!


Essential Concepts
------------------

This section covers some essential concepts in Vitis AI model compilation and inference. By learning these concepts and example codes, the flow can be extended to other ONNX models.

Input Models
~~~~~~~~~~~~

The ONNX model serves as the input for model compilation, which aims to accelerate operators on the NPU. Therefore, ensure the ONNX model is properly prepared using supported machine learning frameworks.

Model Compilation
~~~~~~~~~~~~~~~~~

Models are compiled for the NPU by creating an ONNX inference session using the Vitis AI Execution Provider (VAI EP). The example python code can be found in `compile.py`.

.. code-block:: python

	import onnxruntime

	provider_options_dict = {
	    "config_file": 'vitisai_config.json',
	    "cache_dir":   'my_cache_dir',
	    "cache_key":   'resnet18.a1_in1k',
	}

	print(f"Creating ORT inference session for model models/resnet18.a1_in1k.onnx")
	session = onnxruntime.InferenceSession(
	    'models/resnet18.a1_in1k.onnx',
	    providers=["VitisAIExecutionProvider"],
	    provider_options=[provider_options_dict]
	)


The example configuration file ``vitisai_config.json`` contains options for Vitis AI compiler:

.. code-block:: json

	{
	 "passes": [
	     {
	         "name": "init",
	         "plugin": "vaip-pass_init"
	     },
	     {
	         "name": "vaiml_partition",
	         "plugin": "vaip-pass_vaiml_partition",
	         "vaiml_config": {
	            "device": "ve2",
	            "optimize_level": 2,
	            "threshold_gops_percent": 20,
	            "logging_level": "info"				
	        }
	     }
	 ],
	 "target": "VAIML",
	 "targets": [
	   {
	        "name": "VAIML",
	        "pass": [
	            "init",
	            "vaiml_partition"
	        ]
	    }
	  ]
	}

The value ``ve2`` for the ``device`` option indicates that the compilation targets the AIE-ML v2 device.


Model Deployment
~~~~~~~~~~~~~~~~

To execute the compiled model on hardware, transfer the compiled binaries and the original ONNX model file to the target board. The compiled ONNX graph is automatically partitioned into multiple subgraphs by the Vitis AI Execution Provider (EP). The subgraph(s) containing operators supported by the NPU are executed on the NPU. The remaining subgraph(s) are executed on the CPU. This graph partitioning and deployment technique across CPU and NPU is fully automated by the VAI EP and is totally transparent to the end-user.

Model execution is performed using a Python script that establishes an ONNX Runtime (ORT) inference session. This session is initialized with the target ONNX model and configured to utilize the Vitis AI Execution Provider (EP). Upon execution, the ORT session leverages the Vitis AI EP, which utilizes the compiled model binaries in the specified directory and deploys the ONNX subgraph(s) on the NPU and the CPU.

The example python code for deploying on the hardware can be found in ``runmodel.py``. It creates an ORT ``InferenceSession`` for CPU and NPU and runs inferences. And then compute the RMSE (Root Mean Square Error) between the CPU and NPU results:

.. code-block:: python

	import numpy as np
	import onnxruntime as ort

	provider_options_dict = {
	    "config_file": 'vitisai_config.json',
	    "cache_dir":   'my_cache_dir',
	    "cache_key":   'resnet18.a1_in1k',
		"target": "VAIML"
	}

	print(f"Creating ORT inference session for model models/resnet18.a1_in1k.onnx")

	onnx_model="models/resnet18.a1_in1k.onnx"
	# CPU session to compute reference values
	cpu_session = ort.InferenceSession(
	    onnx_model,
	)
	# NPU session
	npu_session = ort.InferenceSession(
	    onnx_model,
	    providers=["VitisAIExecutionProvider"],
	    provider_options=[provider_options_dict]
	)

	num_iter = 4
	print(f"Running {num_iter} inferences, comparing CPU and NPU outputs")
	for i in range(num_iter):
	    # Generate random data
	    input_data = {}
	    for input in npu_session.get_inputs():
	        fixed_shape = [1 if isinstance(dim, str) else dim for dim in input.shape]
	        input_data[input.name] = np.random.rand(*fixed_shape).astype(np.float32)

	    # Compute CPU results (reference values)
	    cpu_outputs = cpu_session.run(None, input_data)
	    # Compute NPU results
	    try:
	        npu_outputs = npu_session.run(None, input_data)
	    except Exception as e:
	        print(f"Failed to run on NPU: {e}")
	        sys.exit(1)

	    # Compare CPU and NPU results
	    max_diff = np.max(np.abs(cpu_outputs[0] - npu_outputs[0]))
	    rmse = np.sqrt(np.mean((cpu_outputs[0] - npu_outputs[0]) ** 2))
	    print(f'Iteration {i+1:3d}: Max absolute difference = {max_diff:.6f}, Root mean squared error = {rmse:.6f}')

	print("Inference Done!")

Summary
-------

By completing this tutorial, you learned:

1. The Vitis AI compilation flow with ResNet-18 example.

2. The deployment of Vitis AI compiled model on the board.
