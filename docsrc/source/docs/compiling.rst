Model Compilation
=================

You can compile the model by executing a Python script that initializes an ONNX Runtime (ORT) inference session with the desired model and the Vitis AI Execution Provider (EP). This process enables the Vitis AI EP to build the model, generating the necessary binaries for execution on the NPU.

Use the following code as a simple template to compile models for the NPU:

.. code-block:: python

    import onnxruntime

    onnx_model = ...           # ONNX model to be compiled

    provider_options_dict = {
        "config_file": ...,    # JSON config file for the Vitis AI compiler
        "cache_dir":   ...,    # Path to the cache directory
        "cache_key":   ...,    # Subfolder in the cache directory for the compiled model
        "target":   ...,       # Target platform for VitisAI execution provider
    }

    session = onnxruntime.InferenceSession(
        onnx_model,
        providers=["VitisAIExecutionProvider"],  # Use the Vitis AI Execution Provider
        provider_options=[provider_options_dict] # The provider options for the Vitis AI EP
    )

.. note::

   Ensure that the working directory inside the Docker container has write permissions so that the generated model is saved successfully.

