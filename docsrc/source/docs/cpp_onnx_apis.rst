=================================
VitisAI and ONNX Runtime C++ APIs
=================================
`ONNX Runtime <https://onnxruntime.ai/>`__ is a high-performance engine for running deep learning models, supporting both inference and training execution. It provides user-friendly C and C++ APIs for integrating precompiled models into your application workflows.The C++ runtime application and workflow share similarities with the Python implementation, making it easier for users to transition between the two languages.

By compiling models with VitisAI, you can leverage ONNX Runtime's C++ APIs to deploy those models on hardware and perform inference efficiently. The following example demonstrates a typical inference workflow using ONNX Runtime C++ APIs with VitisAI execution provider.

For further details about ONNX Runtime C++ APIs, refer to the official documentation:  
https://onnxruntime.ai/docs/api/c/c_cpp_api.html

Example: Inference Workflow with VitisAI
----------------------------------------

.. code-block::

	#include <onnxruntime_cxx_api.h>
	
	// Initialize environment and session options
	Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "Default");
	Ort::SessionOptions session_options;

	// Configure VitisAI-specific session options
	std::unordered_map<std::string, std::string> options;
	options["config_file"] = "./vitisai_config.json";        // Path to VitisAI configuration file
	options["cacheDir"] = "./my_cache_dir";                  // Directory containing compiled model cache (must match compilation output)
	options["cacheKey"] = "resnet50_quantized_xint8";        // Key for the compiled model cache
	options["target"] = "VAIML";        // Target platform for Vitis AI 

	// Append VitisAI execution provider options to the session
	session_options.AppendExecutionProvider("VitisAI", options);

	// Create an ONNX Runtime session with the specified model and options
	Ort::Session session(env, model_path, session_options);

	// Retrieve input and output tensor names
	Ort::AllocatorWithDefaultOptions allocator;
	auto input_name = session.GetInputNameAllocated(0, allocator);
	const char* input_names[] = { input_name.get() };

	size_t num_outputs = session.GetOutputCount();
	std::vector<const char*> output_names;
	std::vector<Ort::AllocatedStringPtr> output_name_ptrs;
	for (size_t i = 0; i < num_outputs; i++) {
		output_name_ptrs.emplace_back(session.GetOutputNameAllocated(i, allocator));
		output_names.push_back(output_name_ptrs.back().get());
	}

	// Execute model inference
	auto output_tensors = session.Run(
		Ort::RunOptions{nullptr},
		input_names,                 // Array of input names
		&input_tensor,               // Pointer to input tensor
		1,                           // Number of inputs
		output_names.data(),         // Array of output names
		num_outputs                  // Number of outputs
	);

**Note:**  

- Include header file `onnxruntime_cxx_api.h`. This file is located in `/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/include/core/session/` directory.

- Ensure that the `cacheDir` and `cacheKey` options match the results from your VitisAI model compilation.

C++ Host Application Compilation and Linking
--------------------------------------------

To compile and link the C++ application, follow the steps below:

1. Start Docker:
~~~~~~~~~~~~~~~~

Follow :doc:`docker-setup` documentation to start the docker. Once running, set up the SDK inside the docker by executing the following commands:

.. code-block::
	
	unset LD_LIBRARY_PATH
	source /opt/xilinx/arm_sdk/environment-setup-cortexa72-cortexa53-amd-linux

2. Compile the Application
~~~~~~~~~~~~~~~~~~~~~~~~~~

Within docker, navigate to your working directory and compile the application using the g++ compiler. 
This command invokes a cross-compiler for the ARM64 architecture (aarch64-amd-linux-g++), targeting a Xilinx platform based on Cortex-A72 & A53 cores.
The input source file `ve2_ortCppApi_modelrun.cpp` is compiled into an object file `ve2_ortCppApi_modelrun.o`.

.. code-block::

	/opt/xilinx/arm_sdk/sysroots/x86_64-amdedfsdk-linux/usr/bin/aarch64-amd-linux/aarch64-amd-linux-g++   -mcpu=cortex-a72.cortex-a53+crc -mbranch-protection=standard -fstack-protector-strong  -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux  -I/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/include -I/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/include/core/session  -O2 -pipe -g -feliminate-unused-debug-types  -o ve2_ortCppApi_modelrun.o -c ./ve2_ortCppApi_modelrun.cpp

Some important flags used here are 

* `--sysroot=...`: Sets the SDK's root for finding libraries and headers, ensuring cross-compilation uses proper ARM libraries.

* `-I...`: Add specified directories to the header file search path.

3. Link the Application
~~~~~~~~~~~~~~~~~~~~~~~~~~

You can then link the previously created object file (`ve2_ortCppApi_modelrun.o`) into an executable, named `model-app.elf`.
This command includes the ONNX Runtime library (`-lonnxruntime`) and sets up linking path and runtime path.

.. code-block::

	/opt/xilinx/arm_sdk/sysroots/x86_64-amdedfsdk-linux/usr/bin/aarch64-amd-linux/aarch64-amd-linux-g++   -mcpu=cortex-a72.cortex-a53+crc -mbranch-protection=standard -fstack-protector-strong  -O2 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux --sysroot=/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux  -O2 -pipe -g -feliminate-unused-debug-types  -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed  -Wl,-z,relro,-z,now -rdynamic "ve2_ortCppApi_modelrun.o" -o model-app.elf   -L/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/lib  -Wl,-rpath,/opt/xilinx/arm_sdk/sysroots/cortexa72-cortexa53-amd-linux/usr/lib -lonnxruntime 

Some important flags used here are:

* `-L...`: Add to library search path.

* `-Wl,-rpath,...`: Sets the runtime library path in the executable, so it knows where to find shared libraries.

* `-lonnxruntime`: Links against the ONNX Runtime library.

This process will create the necessary binaries for your C++ application, ready for deployment and execution on hardware.
