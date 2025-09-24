Batching Inputs for Efficient Inference
=======================================

Batching involves processing multiple input samples together in a single operation instead of one at a time. This boosts overall system efficiency and throughput by better using hardware resources, though it may add a small delay per request.

The Vitis AI compiler supports two types of batching to fit your workload:

- Static Batching: Fixed batch size decided when the model is built. You must always provide the exact number of inputs (e.g., 6). This method is very efficient but inflexible.

- Dynamic Batching: Allows varying batch sizes at runtime for more flexibility. The model accepts inputs of different batch sizes, managed by configurations created during compilation.

Static Batching 
---------------

Static batching fixes the batch size when the model is built or exported (typically 6 for VAI 5.1). Every inference request must provide exactly this number of inputs. Deviating from this fixed batch size results in errors. Therefore, static batching is highly efficient but requires fixed input sizes.

.. note::
   For Vitis AI 5.1 Bash, use a fixed batch size of 6 for static models. 

Dynamic Batching
----------------

Dynamic batching enables variable batch sizes during inference, allowing the batch dimension to be dynamic. The ONNX model input can have shapes like [batch_size, 3, 224, 224] or [?, 3, 224, 224]. Using optimization levels O2 or O3, the compiler creates a single NPU configuration supporting dynamic batch sizes. 
For enhanced performance, specifying device_batch_size: <N> during compilation generates N separate NPU configurations to process input feature maps efficiently.

.. note::
   In VAI 5.1 Bash, the maximum supported `device_batch_size` is 6.

Input feature maps (IFMs) and Device Batch Size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The number of input samples (IFM num_samples) can be any dynamic value, structured as a tensor with shape [num_samples, 3, 224, 224]. During compilation, specifying the device_batch_size (N) instructs the compiler to create N separate NPU configurations, assuming the hardware can accommodate this.  
If the total input samples are divisible by N, batches are evenly partitioned into groups of N. If not, the last batch contains fewer than N samples, is handled by padding to size N to accommodate processing. 

.. note::
   For VAI 5.1 bash, the maximum value supported for device_batch_size is 6. 

Limitations of Dynamic Batch Support
------------------------------------

- Alternating batch sizes within inputs (e.g., one input with batch size 6 and another with batch size 1) are not supported.
- Dynamic batch sizes combined with other dynamic output shapes are currently not fully supported.
- Multiple input tensors are not supported.
- Batch size defined in dimension 1 instead of dimension 0 is unsupported.
- Outputs split into multiple segments causing varying batch sizes (e.g., reducing from 6 to 1) are not supported.


ResNet 50 INT8 Example
----------------------

Prerequisites
^^^^^^^^^^^^^
Before building and deploying the example, check the system requirements in the :doc:`system_requirements` section.

Model Preparation
~~~~~~~~~~~~~~~~~~

- A ResNet50 dynamic batch model with a variable batch size (e.g., [?, 3, 224, 224]) is used in this example.

Model Compilation
~~~~~~~~~~~~~~~~~

Models are compiled for the NPU by creating an ONNX inference session using the Vitis AI Execution Provider (VAI EP).

Example Python snippet to load a dynamic batch model:

.. code-block::

    import onnxruntime

    # Path to the quantized ONNX model with dynamic batch support
    onnx_quant_model = "model_dynamic/resnet50_quantized_xint8_dynamic.onnx"

    # Configuration options for the Vitis AI Execution Provider
    provider_options_dict_quant = {
        "config_file": 'vitisai_config.json',        # Path to Vitis AI configuration file
        "cache_dir": 'vek385_cache_dir',             # Directory to store compiled model cache
        "cache_key": 'resnet50_xint8_batch_6',       # Unique identifier for cached compilation
        "ai_analyzer_visualization": True,            # Enable visualization output for analysis
        "ai_analyzer_profiling": True,               # Enable profiling data collection
        "target": "VAIML"                            # Target platform for Vitis AI ML
    }

    # Create ONNX Runtime inference session with Vitis AI Execution Provider
    # This compiles the model for NPU execution during session creation
    npu_quant_session = ort.InferenceSession(
        onnx_quant_model,                            # Input ONNX model path
        providers=["VitisAIExecutionProvider"],      # Use Vitis AI EP for NPU acceleration
        provider_options=[provider_options_dict_quant]  # Pass configuration options
    )

Use Vitis AI configuration file vitisai_config.json with "device_batch_size" option enabled. For more details on Vitis AI configuration file, see :doc:`hello_world`

.. code-block::
    {
        // Define compilation passes to be executed in sequence
        "passes": [
            {
                // Initialization pass - sets up the compilation environment
                "name": "init",
                "plugin": "vaip-pass_init"
            },
            {
                // Main partitioning pass - identifies and optimizes subgraphs for NPU
                "name": "vaiml_partition",
                "plugin": "vaip-pass_vaiml_partition",
                "vaiml_config": {
                    "device": "ve2",                        // Target device (VE2 NPU)
                    "device_batch_size": 6,                 // Create 6 NPU configurations for dynamic batching
                    "keep_outputs": true,                   // Preserve intermediate outputs for debugging
                    "optimize_level": 2,                    // Optimization level (0-3, higher = more aggressive)
                    "threshold_gops_percent": 20,           // Minimum GOPS percentage to partition to NPU
                    "ai_analyzer_visualization": true,      // Generate visualization files for analysis
                    "ai_analyzer_profiling": true,          // Enable profiling data collection
                    "logging_level": "info"                 // Set logging verbosity level
                }
            }
        ],
        // Default target platform
        "target": "VAIML",
        // Define target configurations and their associated passes
        "targets": [
            {
                "name": "VAIML",                           // Target name for Vitis AI ML platform
                "pass": [
                    "init",                                 // Execute initialization pass
                    "vaiml_partition"                       // Execute partitioning pass
                ]
            }
        ]
    }


The number of operators accelerated on the NPU is displayed at the end of the compilation process. The output should look as follows:

.. code-block::
    [Vitis AI EP] No. of Operators : VAIML   490 VITIS_EP_CPU     2
    [Vitis AI EP] No. of Subgraphs : VAIML     1

Run Inference
~~~~~~~~~~~~~~

Run inference specifying the total batch size as follows:

``python3 run.py --onnx_batch_size <N>``

For example, set N=65 for 65 input samples.
The script below creates inputs of the correct shape, runs the model, and outputs inference time.

.. code-block::

    import numpy as np
    import onnxruntime as ort
    import time
    import argparse

    # Parse command line arguments for dynamic batch size setting
    parser = argparse.ArgumentParser(description="Dynamic batched ResNet50 inference with a N-wide overlay.")
    parser.add_argument("--onnx_batch_size", type=int, default=6, help="Total number of samples to process.")
    args = parser.parse_args()

    N = args.onnx_batch_size  # Number of input feature map (IFM) samples for inference

    # Path to the ONNX model with dynamic batch size support
    onnx_quant_model = "model_dynamic/resnet50_quantized_xint8_dynamic.onnx"

    # Vitis AI execution provider configuration options
    provider_options_dict_quant = {
        "config_file": 'vitisai_vek385_batchSize_config.json',
        "cache_dir": 'vek385_cache_dir_dock_0918',
        "cache_key": 'resnet50_xint8_batch_size6',
        "ai_analyzer_visualization": True,
        "ai_analyzer_profiling": True,
        "target": "VAIML"
    }

    # Create an ONNX Runtime session with Vitis AI Execution Provider for NPU inference
    npu_quant_session = ort.InferenceSession(
        onnx_quant_model,
        providers=["VitisAIExecutionProvider"],
        provider_options=[provider_options_dict_quant]
    )

    def benchmark_model(session, num_samples, runs=1):
        """
        Run inference on the specified number of samples and measure average inference time.

        Args:
            session: ONNX Runtime inference session.
            num_samples: Total number of input samples in the batch.
            runs: Number of times to run inference for averaging.
        """
        # Create a random input tensor with shape [num_samples, 3, 224, 224]
        input_shape_full = (num_samples, 3, 224, 224)
        full_input = np.random.rand(*input_shape_full).astype(np.float32)

        # Save the generated input to a .npy file for inspection or reuse
        np.save("input.npy", full_input)

        # Start timing the inference runs
        start_time = time.time()

        for _ in range(runs):
            # Run the model inference on the full batch input
            outputs = session.run(None, {session.get_inputs()[0].name: full_input})

        # Calculate the average inference time over all runs
        end_time = time.time()
        avg_time = (end_time - start_time) / runs

        # Save the outputs to a .npy file (supporting multiple outputs)
        output_to_save = outputs[0] if isinstance(outputs, (list, tuple)) else outputs
        np.save("output.npy", output_to_save)

        print('Inference time for total samples {}: {:.3f} ms'.format(num_samples, avg_time * 1000))

    # Execute benchmarking function with specified batch size
    benchmark_model(npu_quant_session, N)


Console Output during Inference
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block::

    open : DEV name  /dev/accel/accel0
    Partition ID:   6144
        Start Col:    0
        Num Cols:     24
        Partition Fd: 7
    DEBUG1: [VAIML-CUSTOMOP] DEBUG: MyCustomOp created for /mnt/telluride-n-batch/resnet-50/vek385_cache_dir_dock_0918/resnet50_xint8_dynamic_batch_size6/vaiml_par_0
    DEBUG1: [VAIML-CUSTOMOP] ai_analyzer_profiling: 1; override_batch_size: 0; device_batch_size: 1; total_batches: 1; enable_update_initializer:0
    DEBUG1: [VAIML-CUSTOMOP] Number of inputs: 1
    DEBUG1: [VAIML-CUSTOMOP] Running batch: 0
    DEBUG1: [VAIML-CUSTOMOP] Input 0
    DEBUG1: [VAIML-CUSTOMOP]     Data type: int8
    DEBUG1: [VAIML-CUSTOMOP]     Data type byte size: 1
    DEBUG1: [VAIML-CUSTOMOP]     Shape: 65 3 224 224
    DEBUG1: [VAIML-CUSTOMOP]     Elements per batch: 9784320
    DEBUG1: [VAIML-CUSTOMOP]     Data buffer size: 9784320
    DEBUG1: [VAIML-CUSTOMOP] Number of outputs: 1
    DEBUG1: [VAIML-CUSTOMOP] Output 0
    DEBUG1: [VAIML-CUSTOMOP]     Shape: -1 1000
    DEBUG1: [VAIML-CUSTOMOP]     Resolved dynamic shape: 65 1000
    DEBUG1: [VAIML-CUSTOMOP]     Elements: 65000
    DEBUG1: [VAIML-CUSTOMOP]     Data buffer size: 65000
    DEBUG1: [VAIML-CUSTOMOP]     Data type: int8
    DEBUG1: [VAIML-CUSTOMOP]     num of elements: 65000
    DEBUG1: [VAIML-CUSTOMOP]     total batches: 1
    DEBUG1: [VAIML-CUSTOMOP]     Data size: 65000
    DEBUG1: [VAIML-CUSTOMOP] DEBUG: Running multi-in-out forwardImp for unified partition
    DEBUG1: [VAIML-CUSTOMOP]     Finish VAIML Compute;
    Inference time for total samples 65: 130.54203987121582 ms
    DEBUG1: [VAIP-VAIML-PASS] VAIP Profiling data exported to: record_timer_vaip_vaiml_par_0.json

