==========================
Model Quantization
==========================

**Model quantization** is the process of mapping high-precision weights/activations to a lower precision format, such as BF16/INT8, while maintaining model accuracy. This technique enhances the computational and memory efficiency of the model for deployment on NPU devices. It can be applied post-training, allowing existing models to be optimized without the need for retraining.

The Vitis AI 2025.1_web compiler supports float input models which is implicitly quantized to BF16 format without AMD Quark quantizer. Or, the input float model can be quantized to INT8 format explicitly by AMD Quark, and then compiled by Vitis AI compiler.

Quantization introduces several challenges, primarily revolving around the potential drop in model accuracy. Choosing the right quantization parameters—such as data type, bit-width, scaling factors, and the decision between per-tensor quantization—adds layers of complexity to the design process. The list of operations supported for different quantization types can be found in :doc:`Supported Operations <ops_support>`.

AMD Quark
==========================
**AMD Quark** is a comprehensive cross-platform deep learning toolkit designed to simplify and enhance the quantization of deep learning models. Supporting both PyTorch and ONNX models, Quark empowers developers to optimize their models for deployment on a wide range of hardware backends, achieving significant performance gains without compromising accuracy.

For more challenging model quantization needs AMD Quark supports advanced quantization technique like Fast Finetuning that helps recover the lost accuracy of the quantized model.

For Vitis AI 2025.1_web release, the AMD Quark should only be used to quantize ONNX models, and only *XINT8* quantization configuration should be used. 

Documentation
==========================
The complete documentation for AMD Quark for Vitis AI can be found here: https://quark.docs.amd.com

Installation
==========================

AMD Quark is pre-installed in the docker.

INT8 Examples
==========================
AMD Quark provides default configrations that support INT8 quantization configuration. For example, *XINT8* uses symmetric INT8 activation with power-of-two scales. The quantization configuration can be customized using the *QuantizationConfig* class. The following example shows how to set up the quantization configuration for INT8 quantization:

.. code-block::

    quant_config = get_default_config("XINT8")
    quant_config.activation_type = QuantType.QInt8
    quant_config.optimize_model = False
    quant_config.extra_options["UseRandomData"] = True
    quant_config.extra_options["ConvertBNToConv"] = True
    quant_config.extra_options["ConvertSigmoidToHardSigmoid"] = False
    quant_config.extra_options["ConvertClipToRelu"] = True
    quant_config.extra_options["SplitLargeKernelPool"] = False
    quant_config.extra_options["ReplaceClip6Relu"] = True
    quant_config.extra_options["ConvertReduceMeanToGlobalAvgPool"] = False
    quant_config.extra_options["RemoveQDQConvClip"] = False
    quant_config.extra_options["RemoveQDQConvPRelu"] = False
    quant_config.extra_options["RemoveQDQConvRelu"] = False
    quant_config.extra_options["RemoveQDQConvLeakyRelu"] = False

    quantization_config = Config(global_quant_config=quant_config)
    quantizer = ModelQuantizer(quantization_config)
    print("The configuration of the quantization is {}".format(quantization_config))

You use the `get_default_config('XINT8')` function to get the default configuration for INT8 quantization.
Note: The options used above are mandatory for INT8 quantization using Quark with Vitis AI 2025.1_web

