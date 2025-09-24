**************
Release Notes
**************

Version VitisAI 5.1
===================

Key Components and Features of the VitisAI 5.1 Release:

- Changed the name of the release to VitisAI 5.1
- Source code release of Integrated System Reference Design
- Example Applications to demonstrate
  
  - ml_ort: Demonstrates ML acceleration with ONNX Runtime APIs
  - x_plus_ml_ort: Demonstrates using preprocessing, postprocessing and overlay components with VART APIs and ML with ONNX Runtime APIs
  - x_plus_ml_vart :  Demonstrates using preprocessing, postprocessing and overlay components with VART APIs and ML with VART-ML APIs
  - spatial_mt_ml_ort:  The spatial multi-threading inference application runs ResNet50 and ResNet18 models in separate threads showcasing the spatial loading of models in AI engine using ONNX Runtime APIs
  - temporal_ml_ort: The temporal inference application runs ResNet50 and ResNet18 models sequentially by loading the models in the same single NPU configuration. Runs ML with ONNX Runtime APIs

- Support for OSPI and SD Card Boot Flow
- VART Based APIs to control Pre Processing IPs and perform Post Processing functions and ML components
- Batching inputs for Efficient Inference


Version VitisAI 5.1: Known Issues and Limitations
------------------------------------------------

- Support is limited to 2D CNN models only.
- Models using ONNX opset 17 are recommended for optimal performance.
- Only one model can be executed at any given time.
- Image Processing HLS kernel (pre-processing)

  - is pre-compiled and present in the release packages (xo). Recompilation of this kernel from sources is not supported in this release.
  - For RGBP FLOAT format, kernel times out or hangs if the width of  format exceeds 960 pixels
  - All FLOAT and BF16 formats are supported as only output formats for the kernel  

- VART-ML

  - Supports only VAIML platform with flexmlRT-1.6 backend in this version.
  - Currently, only synchronous inference is implemented.
  - Zero-copy flow remains unoptimized, so performance gains will be minimal.
  - Zero copy is supported on both input and output sides only, mixed configurations (one side zero copy and the other side non-zero copy) are not supported; both tensor types must match.
  - For Zero copy, if the tensor buffer is allocated on same device context as of XDNA, inference will fail with error: DRM_IOCTL_AMDXDNA_SYNC_BO IOCTL. CR: [AIESW-12591] [XRT] DRM_IOCTL_AMDXDNA_SYNC_BO IOCTL ERROR - AECG Jira
  - Returned tensor names differ from those in the ONNX model. CR: [AIESW-10432] [FE] Provide ONNX Tensor names and Quantization parameters - AECG Jira

Version 2025.1_web
===================

Key Components and Features of the 2025.1_web Release:

- Support for AMD Quark Quantized INT8 ONNX models
- Support for INT8 models(currently not optimized for performance).

Version 2025.1_web: Known Issues and Limitations
------------------------------------------------

- Support is limited to 2D CNN models only.
- Models using ONNX opset 17 are recommended for optimal performance.
- Only one model can be executed at any given time.
- Execution is restricted to the provided board image; custom PL or AIE content is not supported.
- While loading VEK385 images in the XSDB terminal, the following message may appear. 
  
  .. code-block::

     Info: Cortex-A78AE #0 (target 17) Stopped at 0xbbf00000 (External Debug Request)

  It does not impact the setup and causes no harm, although it may result in a longer boot time for the images. It'll be fixed in next release.

Version 2025.1
===============

Key Components and Features of the 2025.1 Release:

- Pre-built Docker: Facilitates model quantization and compilation on a Linux Host.
- ONNX Runtime Support: Compatible with ONNX Runtime version 1.22.0.
- NPU Support: Provides support for VE3858 functional NPU IPs.
- Tools : Utilizes Vitis, Vivado, Petalinux, and XRT Tools version 2025.1.
- Model Format Compatibility: Supports ONNX format for 2D Convolutional Neural Networks (CNNs).
- Quantization Options: BF16 quantization for 2D CNN models.
- Inference Execution: Leverages ONNX Runtime Python APIs for inference execution.

Version 2025.1:Known Issues and Limitations
-------------------------------------------

- Support is limited to 2D CNN models only.
- Models using ONNX opset 17 are recommended for optimal performance.
- The standalone use of Quark is not supported.
- Only one model can be executed at any given time.
- Execution is restricted to the provided board image; custom PL or AIE content is not supported.
- While loading VEK385 images in the XSDB terminal, the following message may appear. 
  
  .. code-block::

     Info: Cortex-A78AE #0 (target 17) Stopped at 0xbbf00000 (External Debug Request)

  It does not impact the setup and causes no harm, although it may result in a longer boot time for the images. It'll be fixed in next release.


