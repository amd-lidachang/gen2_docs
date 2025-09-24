==========================
Frequently Asked Questions
==========================

Hardware
--------

- **Question:** Which hardware platform does this release support?

- **Answer:** This release supports the VEK385 hardware platform.
----

- **Question:** Are prebuilt binaries included with this release?

- **Answer:** Yes. Prebuilt binaries are included to streamline board bring-up and boot processes.
----

- **Question:** Is there support for running binaries via OSPI and SD/USB?
- **Answer:** No. This release supports execution of JTAG-loaded binaries, with the root file system mounted over NFS.
----

- **Question:** What should I do if minicom does not detect the board?
- **Answer:** Ensure the cable driver is installed correctly.
----

- **Question:** My board is not detected at the XSDB prompt. What should I do?
- **Answer:** Verify the board’s switch settings, power cycle the board, and reconnect using XSDB.
----

- **Question:** What should I do if U-Boot is not programmed or there is a boot error in XSDB?
- **Answer:** Run this command in XSDB::

	dev reset

	Then repeat the programming step.
----

- **Question:** What role does TFTP server play in this setup?
- **Answer:** The TFTP server enables the transfer of the Linux image from the host to the board, typically during the U-Boot stage.
----

- **Question:** What is the purpose of the NFS server in this setup?
- **Answer:** The NFS (Network File System) server allows the target board to mount the root file system over the network. This enables the Linux OS to boot directly from a shared host directory, eliminating the need for local storage such as SD, USB, or OSPI.
----

- **Question:** What should I check if the image does not copy at the U-Boot prompt?
- **Answer:** Confirm that the TFTP server is properly configured and running. Ensure port 69 is available and check file permissions.

Software Tools
--------------

- **Question:** Are model compilation tools provided in this release?

- **Answer:** Yes. A Docker-based environment is offered to simplify model compilation and deployment.
----

- **Question:** How do I verify the Docker image has been loaded correctly?

- **Answer:** Run::

	docker images

	Sample output::

		REPOSITORY TAG IMAGE ID CREATED SIZE
		vitis_ai_ve2_docker release_v2025.1_0606 c8c735600427 xx hours ago 33.8GB
----

- **Question:** What should I do if model compilation fails to start or terminates unexpectedly?

- **Answer:** Verify that the compilation environment has been correctly initialized inside the Docker container by running::

	source /opt/xilinx/arm_env.bash

If compilation is not triggered or terminates incorrectly, double-check that all environment variables and paths defined in arm_env.bash are correctly set.

----

- **Question:** How can I resolve the following error when compiling an ONNX model inside the Docker container?

.. code-block::

	INFO: [VAIML-COMPILE 1000] Running /bin/aiebu-asm -t aie2ps -o aie_control.elf -c aiecompiler/Work/ps/ml_asm/merged_control.asm -L aiecompiler/Work/ps/asm -L aiecompiler/Work/ps/ml_asm -L aiecompiler/Work/ps/ctrl_pkt -j external_buffer_id.json > aiebu-asm-flexml.log 2>&1 
	ERROR: [VAIML-COMPILE 1018] ucodegen error. Check my_cache_dir/resnet50-v1-12_quantized/vaiml_par_0/0/ucodegen-flexml.log for details.

- **Answer:** Initialize the environment inside the Docker container, then retry,  by running::

	source /opt/xilinx/arm_env.bash

----

Application
-----------

- **Question:** What data types are supported by the hardware and compiler?
- **Answer:** BF16 and INT8
	
----

- **Question:** Which models have been validated with this release?
- **Answer:** The release has been validated using the ResNet18, and ResNet50 CNN models, and is also compatible with other convolutional and detection models.
----

- **Question:** Are any sample models and scripts provided?
- **Answer:**  Yes, the release includes the ResNet50 ONNX model, along with Python scripts and supporting files. The model must be compiled before deployment on the board.
----

- **Question:** Is there an example of quantizing a model using AMD Quark and compiling the quantized model with Vitis AI?
- **Answer:**  Yes. The release includes a detailed step-by-step example found in :doc:`Quick Start Guide: Quark INT8 Quantization to Vitis AI <quick-start-quark>` using ResNet-50 model that demonstrates:

		Quantizing the model with AMD Quark (XINT8)

		Compiling the quantized model with Vitis AI

		Running inference with the compiled model
----

- **Question:** What output information is displayed after compilation?
- **Answer:**  The output is similar to this::

	[Vitis AI EP] No. of Operators : VAIML 124
	[Vitis AI EP] No. of Subgraphs : VAIML 1
----

- **Question:** How can I check the number of operators running on the CPU vs. the NPU?
- **Answer:**  The console log displays both values, for example::

	[Vitis AI EP] No. of Operators : CPU 10 VAIML 357
	This means 10 operators are assigned to the CPU, and 357 to the NPU.
----

- **Question:** What happens if some operators cannot be mapped to the NPU?
- **Answer:** Any operators that cannot be mapped to the NPU are executed on the CPU instead.
----

- **Question:** Is there a generated report on operator assignments? How do I enable report generation?
- **Answer:** Yes. Set the following environment variable before compilation::

	export XLNX_ONNX_EP_REPORT_FILE=vitisai_ep_report.json
----

- **Question:** What information does the vitisai_ep_report.json file contain?
- **Answer:**
		- Total number of nodes
		- Operator types
		- CPU/NPU assignment
		- Node-level stats: input, applied operation, output
----

If you have additional questions, please contact the support team.
