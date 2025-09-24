Vitis AI EP Options
===================

The `provider_options` parameter enables the configuration of the Vitis AI Execution Provider (EP). The Vitis AI EP supports the following options:

- **cache_dir**
  Optional. The path and name of the cache directory. Setting this option is recommended.

  - Type: String
  - Default: The directory where the Python script creating the ORT inference session is executed from.

- **cache_key**
  Optional. The subfolder in the cache directory where the compiled model is stored. Setting this option is recommended.

  - Type: String
  - Default: Name of file containing the input ONNX model without the extension.

- **encryption_key**
  Optional. 256-bit key used for generating an encrypted compiled model in the cache folder. At runtime, you must use the same key to decrypt the model when loading it from the cache.

  - Type: String of 64 hexadecimal values representing the 256-bit encryption key.
  - Default: None, the model is not encrypted.

- **ai_analyzer_visualization**
  Optional. Enables generation of compile-time analysis data.

  - Type: Boolean
  - Default: False

- **ai_analyzer_profiling**
  Optional. Enables generation of inference-time analysis data.

  - Type: Boolean
  - Default: False

- **config_file**
  Required. Configuration file to pass additional compilation options. For more details, refer to the section about the Vitis AI EP Configuration File.

  - Type: String
  - Default: N/A. This option is required.

- **target**
  Required. Target platform for Vitis AI execution provider.

  - Type: String
  - Default: N/A. This option is required.
