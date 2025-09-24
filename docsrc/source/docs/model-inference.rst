Running the Compiled Model
==========================

To run the model on the hardware board, the following files are needed:

- The original ONNX model
- The folder containing the compiled model, as well as generated runtime shared libraries
- The JSON config file used to compile the model
- A Python script to run the model

Just like model compilation, model inference is performed using an ONNX Runtime (ORT) inference session.

The ORT inference session should be initialized as follows:

- The Vitis AI Execution Provider must be used; otherwise, the model will be executed on the local CPU.
- The ONNX model should be the same as the one used during the compilation phase.
- The `config_file` provider option should point to the same configuration file as the one used during the compilation phase.
- The `cache_dir` and `cache_key` provider options should point to the folder containing the compiled model. These settings do not have to match the ones used during compilation. The compiled model can be placed in any folder on the Linux filesystem of the HW board. The combination of `cache_dir/cache_key` should simply point to this folder.

If the input ONNX model doesn’t match the compiled model, or if the Vitis AI EP cannot find the compiled model, the model will not be deployed on the NPU.

If the input ONNX model matches the compiled model, the Vitis AI EP will load the compiled model and will be ready to deploy it on the NPU.

Once the ORT inference session is initialized, the model is deployed using the ORT session `run` API. For more information about ONNX Runtime API, refer to the online documentation: https://onnxruntime.ai/docs/api/python/api_summary.html

Upon execution, the subgraphs containing operators supported by the NPU are executed on the NPU by the Vitis AI EP. The remaining subgraphs are executed on the CPU.

The code below can be used as a simple template to deploy models on the NPU:

.. code-block:: python

    import onnxruntime

    onnx_model = ...        # Original ONNX model used during the compilation phase

    provider_options_dict = {
        "config_file": ..., # Original JSON config file during the compilation phase
        "cache_dir":   ..., # Path to the cache directory
        "cache_key":   ..., # Subfolder in the cache directory with the compiled model
    }

    # Create the ORT inference session
    session = onnxruntime.InferenceSession(
        onnx_model,
        providers=["VitisAIExecutionProvider"],
        provider_options=[provider_options_dict]
    )

    # Initialize input tensors
    input_data = {}
    for input in session.get_inputs():
        input_data[input.name] = ...

    # Run model
    outputs = session.run(None, input_data)

