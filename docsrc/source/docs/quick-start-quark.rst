
Quick Start Guide: Quark INT8 Quantization to Vitis AI
======================================================

`Model Quantization <model_quantization.rst>`_ section gives an overview of Versal AI Edge Gen 2 quantization using the AMD Quark tool.

This section demonstrates how to perform INT8 quantization using AMD Quark, and using the quantized INT8 model in Vitis AI. 

For BF16 quantization, Quark does not need to be invoked explicitly. The Vitis AI compiler will automatically handle the FP32 to BF16 quantization process.

Basic Example: Quantizing ResNet50
----------------------------------

The following steps outline the process for quantizing a ResNet50 ONNX model. 

	**1. Download the ONNX Model**
	
		On your host machine, download the ResNet50 ONNX float model from the `onnx/models <https://github.com/onnx/models>`__ onnx/models repository:

		.. code-block::

			cd <Working Path>
			wget -P models https://github.com/onnx/models/raw/new-models/vision/classification/resnet/model/resnet50-v1-12.onnx

	**2. Prepare Calibration Data & Validation Data**
	
	Create a folder for calibration data and download sample images (PNG or JPG). For example, use images from `microsoft/onnxruntime-inference-examples <https://github.com/microsoft/onnxruntime-inference-examples/tree/main/quantization/image_classification/cpu/test_images>`__ as a quick start.

	.. code-block::

		mkdir calib_data
		wget -O calib_data/daisy.jpg https://github.com/microsoft/onnxruntime-inference-examples/blob/main/quantization/image_classification/cpu/test_images/daisy.jpg?raw=true
		chmod -R a+w <Working Path>

	And prepare some pictures for validation:

	.. code-block::

		mkdir val_data
		wget -O val_data/daisy.jpg https://github.com/microsoft/onnxruntime-inference-examples/blob/main/quantization/image_classification/cpu/test_images/daisy.jpg?raw=true
		wget -O val_data/rose.jpg https://github.com/microsoft/onnxruntime-inference-examples/blob/main/quantization/image_classification/cpu/test_images/rose.jpg?raw=true
		wget -O val_data/tulip.jpg https://github.com/microsoft/onnxruntime-inference-examples/blob/main/quantization/image_classification/cpu/test_images/tulip.jpg?raw=true

	**3. Launch Vitis AI Docker**
	
	Refer to the Vitis AI 2025.1 Versal AI Edge Gen 2 Documentation `Docker Setup <docker-setup.rst>`__ for details. Start the Docker container:

	.. code-block::

		docker run -it --rm -v <Working Path>:<Path in Docker>  <Docker REPOSITORY>:<Docker TAG> "bash"
	

	**4. Set Up the Environment Inside Docker**
	
	Setup environment:

	.. code-block::

		source /opt/xilinx/arm_env.bash

	**5. Create the Quantization Script**
	
	Inside the docker, create a file *quantize.py* with the following contents:

	.. code-block::

		import os
		import cv2
		import numpy as np
		import onnx
		from torchvision import transforms
		from onnxruntime.quantization import CalibrationDataReader
	
		def get_model_input_name(input_model_path: str) -> str:
			model = onnx.load(input_model_path)
			model_input_name = model.graph.input[0].name
			return model_input_name
	
		class ImageDataReader(CalibrationDataReader):
	
			def __init__(self, calibration_image_folder: str, input_name: str):
				self.enum_data = None
	
				self.input_name = input_name
	
				self.data_list = self._preprocess_images(
						calibration_image_folder)
	
			def _preprocess_images(self, image_folder: str):
				data_list = []
				img_names = [f for f in os.listdir(image_folder) if f.endswith('.png') or f.endswith('.jpg')]
				for name in img_names:
					input_image = cv2.imread(os.path.join(image_folder, name))
					# Resize the input image. Because the size of Resnet50 is 224.
					input_image = cv2.resize(input_image, (224, 224))
					input_data = np.array(input_image).astype(np.float32)
					# Custom Pre-Process
					input_data = input_data.transpose(2, 0, 1)
					input_size = input_data.shape
					if input_size[1] > input_size[2]:
						input_data = input_data.transpose(0, 2, 1)
					input_data = np.expand_dims(input_data, axis=0)
					input_data = input_data / 255.0
					data_list.append(input_data)
	
				return data_list
	
			def get_next(self):
				if self.enum_data is None:
					self.enum_data = iter([{self.input_name: data} for data in self.data_list])
				return next(self.enum_data, None)
	
			def rewind(self):
				self.enum_data = None
	
		from quark.onnx.quantization.config import Config, get_default_config
		from quark.onnx import ModelQuantizer
		from onnxruntime.quantization import QuantType 
	
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

		# Set up quantization with a specified configuration
		quantization_config = Config(global_quant_config=quant_config)
		quantizer = ModelQuantizer(quantization_config)

		float_model_path = "models/resnet50-v1-12.onnx"
		quantized_model_path = "models/resnet50-v1-12_quantized.onnx"
		calib_data_path = "calib_data"
		model_input_name = get_model_input_name(float_model_path)
		calib_data_reader = ImageDataReader(calib_data_path, model_input_name)

		# Quantize the ONNX model and save to specified path
		quantizer.quantize_model(float_model_path, quantized_model_path, calibration_data_reader=calib_data_reader)

	**6. Run Quark Quantizer**
	
	
	Use the *quantize.py* created above and run quantization:

	.. code-block::

		python3 quantize.py

	Example output:

	.. code-block::

		┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
		┃ Op Type              ┃ Float Model                          ┃
		┡━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
		│ Conv                 │ 53                                   │
		│ BatchNormalization   │ 53                                   │
		│ Relu                 │ 49                                   │
		│ MaxPool              │ 1                                    │
		│ Add                  │ 16                                   │
		│ GlobalAveragePool    │ 1                                    │
		│ Flatten              │ 1                                    │
		│ Gemm                 │ 1                                    │
		├──────────────────────┼──────────────────────────────────────┤
		│ Quantized model path │ models/resnet50-v1-12_quantized.onnx │
		└──────────────────────┴──────────────────────────────────────┘
		┏━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓
		┃ Op Type           ┃ Activation ┃ Weights  ┃ Bias     ┃
		┡━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━┩
		│ Conv              │ INT8(53)   │ INT8(53) │ INT8(53) │
		│ Relu              │ INT8(49)   │          │          │
		│ MaxPool           │ INT8(1)    │          │          │
		│ Add               │ INT8(16)   │          │          │
		│ GlobalAveragePool │ INT8(1)    │          │          │
		│ Flatten           │ INT8(1)    │          │          │
		│ Gemm              │ INT8(1)    │ INT8(1)  │ INT8(1)  │
		└───────────────────┴────────────┴──────────┴──────────┘

	The output quantized model is saved to *models/resnet50-v1-12_quantized.onnx*. And then go next steps to do Vitis AI compilation.

	**Note:** The *ImageDataReader* function in *quantize.py* is specific to ResNet50 model. For other models, it needs to be modified according to the model requirements.    

	**7. Compile the Quantized Model in Vitis AI**
	
	Create the file *compile.py* with the following contents:

	.. code-block::

		import onnxruntime
	
		provider_options_dict = {
			"config_file": 'vitisai_config.json',
			"cache_dir":   'my_cache_dir',
			"cache_key":   'resnet50-v1-12_quantized',
			"target": "VAIML"
		}
	   
		session = onnxruntime.InferenceSession(
			'models/resnet50-v1-12_quantized.onnx',
			providers=["VitisAIExecutionProvider"],
			provider_options=[provider_options_dict]
		)   

	Create configuration file *vitisai_config.json* with:

	.. code-block::

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
					"keep_outputs": true,
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

	Run Vitis AI compilation with the following command:

	.. code-block::

		python3 compile.py

	It takes time to compile the model. After compilation, the example output:

	.. code-block::

		[Vitis AI EP] No. of Operators : VAIML   490 VITIS_EP_CPU     2 
		[Vitis AI EP] No. of Subgraphs : VAIML     1 

	**8. Run Inference**
	
	Create the file *runmodel_pre_cpu.py* with the following contents:

	.. code-block::

		import numpy as np
		import onnxruntime as ort
		import os
		import cv2
		from torchvision import transforms
		
		onnx_model='models/resnet50-v1-12.onnx'
		onnx_model_xint8 ='models/resnet50-v1-12_quantized.onnx'
		
		provider_options_dict = {
		    "config_file": 'vitisai_config.json',
		    "cache_dir":   'my_cache_dir',
		    "cache_key":   'resnet50-v1-12_quantized',
		}
		
		# CPU session
		cpu_session = ort.InferenceSession(
		    onnx_model,
		    providers=["CPUExecutionProvider"]
		) 
		
		# CPU session with XINT8 quantized model
		cpu_session_xint8 = ort.InferenceSession(
		    onnx_model_xint8,
		    providers=["CPUExecutionProvider"]
		) 
		
		# You can define your preprocess method
		def preprocess_image(image_path):
		    transform = transforms.Compose([
		        transforms.ToPILImage(),
		        transforms.Resize((224, 224)),
		        transforms.ToTensor(),
		        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
		    ])
		
		    image = cv2.imread(image_path)
		    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
		    image = transform(image)
		    image = image.unsqueeze(0)
		    image = image.numpy()
		    return image
		
		input_folder="val_data"
		def run_inference(session, output_dir="output_cpu"):
		    files = sorted([f for f in os.listdir(input_folder) if f.endswith(".jpg")])
		    input_name = session.get_inputs()[0].name
		    runs=0
		    for i,f in enumerate(files):
		        runs+=1
		        fp = os.path.join(input_folder, f)
		        image = preprocess_image(fp)
		        os.makedirs("input", exist_ok=True)
		        np.save(f"input/input_{i}.npy", image)
		        outputs = session.run(None, {input_name:image})
		        # Create outpu directory if it doesn't exist
		        os.makedirs(output_dir, exist_ok=True)
		        for idx, out in enumerate(outputs):
		            np.save(f"{output_dir}/output_{i}_{idx}.npy", out)
		
		run_inference(cpu_session,"output_cpu")
		run_inference(cpu_session_xint8,"output_cpu_xint8")
		
	Run following command inside the docker:

	.. code-block::

		python3 runmodel_pre_cpu.py

	It will run inferences on CPU and save input numpy vectors for NPU processing. Next, create file *runmodel.py* with the following contents:

	.. code-block::

		import numpy as np
		import onnxruntime as ort
		import os
		
		onnx_model_xint8 ='models/resnet50-v1-12_quantized.onnx'
		
		provider_options_dict = {
		    "config_file": 'vitisai_config.json',
		    "cache_dir":   'my_cache_dir',
		    "cache_key":   'resnet50-v1-12_quantized',
		}
		
		# NPU session
		npu_session = ort.InferenceSession(
		    onnx_model_xint8,
		    providers=["VitisAIExecutionProvider"],
		    provider_options=[provider_options_dict]
		) 
		
		input_folder="input"
		output_folder="output_vek385"
		files = sorted([f for f in os.listdir(input_folder) if f.endswith(".npy")])
		input_name = npu_session.get_inputs()[0].name
		for i,f in enumerate(files):
		    fp = os.path.join(input_folder, f)
		    image = np.load(fp)
		    outputs = npu_session.run(None, {input_name:image})
		    # Create outpu directory if it doesn't exist
		    os.makedirs(output_folder, exist_ok=True)
		    for idx, out in enumerate(outputs):
		        np.save(f"{output_folder}/output_{i}_{idx}.npy", out)

	Refer to :doc:`setup-hw` to setup the VEK385 board. On the baord, run inferences with the following command:

	.. code-block::

		python3 runmodel.py

	**8. Evaluation**
	
	Quark provides a tool to compare the differences between different inference results using L2 Loss and other metrics. For example, run following command inside the docker:

	.. code-block::

		python3 -m quark.onnx.tools.evaluate --baseline_results_folder output_cpu --quantized_results_folder output_vek385
	
	Example output:

	.. code-block::

		Mean cos similarity: 0.8768183588981628
		Min cos similarity: 0.7868998646736145
		Mean l2 distance: 32.82765197753906
		Max l2 distance: 43.80929183959961
		Mean psnr: 20.953239053487778
		Min psnr: 17.875922322273254
		Mean vmaf: 0.9508001208305359
		Min vmaf: 0.919207751750946

	You can also have your own post-processing scripts to compare the results or compute model accuracy.

Quantization Using Random Data
-----------------------------

To use random data rather than calibration images, replace *quantize.py* with:

.. code-block::

	import os
	import cv2
	import numpy as np
	from torchvision import transforms
	
	from quark.onnx.quantization.config import Config, get_default_config
	from quark.onnx import ModelQuantizer
	from onnxruntime.quantization import QuantType
	
	quant_config = get_default_config("XINT8")
	quant_config.activation_type = QuantType.QInt8
	quant_config.optimize_model = False
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
	quant_config.extra_options['UseRandomData'] = True
	# Set up quantization with a specified configuration
	quantization_config = Config(global_quant_config=quant_config)
	quantizer = ModelQuantizer(quantization_config)
	float_model_path = "models/resnet50-v1-12.onnx"
	quantized_model_path = "models/resnet50-v1-12_quantized.onnx"
	# Quantize the ONNX model and save to specified path
	quantizer.quantize_model(float_model_path, quantized_model_path, calibration_data_reader=None)

Execute:

.. code-block::

	python3 quantize.py
	
Other steps remain same for quantization with calibration data or random data.

For more information about Quark quantization, please refer to https://quark.docs.amd.com/latest/. But note that it should follow this Vitis AI Edge Gen 2 User Guide's requirements for Vitis AI INT8 quantization.
