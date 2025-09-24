Supported Operators
=========================

The following table lists the ONNX operators supported in Vitis AI 2025.1_web. The operators are categorized by their support for different quantization types: BF16, and INT8. A “Y” indicates that Vitis AI provides broad coverage for that operator and for that specific quantization type for CNN models. Some specific configurations of that operator may however not be fully supported.

+------------------------+-------+-------+
| Ops                    | BF16  | INT8  |
+========================+=======+=======+
| Abs                    | Y     | Y     |
+------------------------+-------+-------+
| Add                    | Y     | Y     |
+------------------------+-------+-------+
| And                    | Y     | Y     |
+------------------------+-------+-------+
| ArgMax                 | Y     |       |
+------------------------+-------+-------+
| ArgMin                 | Y     |       |
+------------------------+-------+-------+
| `AveragePool`_         | Y     | Y     |
+------------------------+-------+-------+
| BatchNormalization     | Y     | Y     |
+------------------------+-------+-------+
| BitShift               | Y     | Y     |
+------------------------+-------+-------+
| BitwiseAnd             | Y     | Y     |
+------------------------+-------+-------+
| BitwiseNot             | Y     | Y     |
+------------------------+-------+-------+
| BitwiseOr              | Y     | Y     |
+------------------------+-------+-------+
| BitwiseXor             | Y     | Y     |
+------------------------+-------+-------+
| Cast                   | Y     |       |
+------------------------+-------+-------+
| Ceil                   | Y     | Y     |
+------------------------+-------+-------+
| Clip                   | Y     | Y     |
+------------------------+-------+-------+
| `Concat`_              | Y     | Y     |
+------------------------+-------+-------+
| Constant               | Y     | Y     |
+------------------------+-------+-------+
| ConstantOfShape        | Y     | Y     |
+------------------------+-------+-------+
|Conv                    | Y     | Y     |
+------------------------+-------+-------+
| ConvTranspose          | Y     | Y     |
+------------------------+-------+-------+
| CumSum                 | Y     |       |
+------------------------+-------+-------+
| `DepthToSpace`_        | Y     | Y     |
+------------------------+-------+-------+
| Div                    | Y     | Y     |
+------------------------+-------+-------+
| Einsum                 | Y     |       |
+------------------------+-------+-------+
| Elu                    | Y     |       |
+------------------------+-------+-------+
| Equal                  | Y     | Y     |
+------------------------+-------+-------+
| Erf                    | Y     | Y     |
+------------------------+-------+-------+
| Exp                    | Y     |       |
+------------------------+-------+-------+
| Expand                 | Y     | Y     |
+------------------------+-------+-------+
| Flatten                | Y     | Y     |
+------------------------+-------+-------+
| Floor                  | Y     | Y     |
+------------------------+-------+-------+
| Gather                 | Y     | Y     |
+------------------------+-------+-------+
| GatherElements         | Y     | Y     |
+------------------------+-------+-------+
| Gelu                   | Y     |       |
+------------------------+-------+-------+
| `Gemm`_                | Y     | Y     |
+------------------------+-------+-------+
| `GlobalAveragePool`_   | Y     | Y     |
+------------------------+-------+-------+
| Greater                | Y     | Y     |
+------------------------+-------+-------+
| GridSample             | Y     | Y     |
+------------------------+-------+-------+
| GroupConv              | Y     | Y     |
+------------------------+-------+-------+
| HardSigmoid            | Y     | Y     |
+------------------------+-------+-------+
| HardSwish              | Y     | Y     |
+------------------------+-------+-------+
| Identity               | Y     | Y     |
+------------------------+-------+-------+
| InstanceNormalization  | Y     | Y     |
+------------------------+-------+-------+
| LayerNormalization     | Y     | Y     |
+------------------------+-------+-------+
| LeakyRelu              | Y     | Y     |
+------------------------+-------+-------+
| Less                   | Y     | Y     |
+------------------------+-------+-------+
| Log                    | Y     | Y     |
+------------------------+-------+-------+
| LSTM                   | Y     |       |
+------------------------+-------+-------+
| MatMul                 | Y     | Y     |
+------------------------+-------+-------+
| Max                    | Y     | Y     |
+------------------------+-------+-------+
| `MaxPool`_             | Y     | Y     |
+------------------------+-------+-------+
| Min                    | Y     | Y     |
+------------------------+-------+-------+
| Mish                   | Y     |       |
+------------------------+-------+-------+
| Mod                    | Y     | Y     |
+------------------------+-------+-------+
| Mul                    | Y     | Y     |
+------------------------+-------+-------+
| Neg                    | Y     | Y     |
+------------------------+-------+-------+
| Not                    | Y     | Y     |
+------------------------+-------+-------+
| Or                     | Y     | Y     |
+------------------------+-------+-------+
| `Pad`_                 | Y     | Y     |
+------------------------+-------+-------+
| Pow                    | Y     | Y     |
+------------------------+-------+-------+
| Reciprocal             | Y     | Y     |
+------------------------+-------+-------+
| ReduceMax              | Y     |       |
+------------------------+-------+-------+
| ReduceMean             | Y     | Y     |
+------------------------+-------+-------+
| ReduceMin              | Y     |       |
+------------------------+-------+-------+
| ReduceSum              | Y     | Y     |
+------------------------+-------+-------+
| Relu                   | Y     | Y     |
+------------------------+-------+-------+
| Reshape                | Y     | Y     |
+------------------------+-------+-------+
| `Resize`_              | Y     | Y     |
+------------------------+-------+-------+
| Round                  | Y     | Y     |
+------------------------+-------+-------+
| ScatterND              | Y     | Y     |
+------------------------+-------+-------+
| Shape                  | Y     | Y     |
+------------------------+-------+-------+
| Sigmoid                | Y     | Y     |
+------------------------+-------+-------+
| Sign                   | Y     |       |
+------------------------+-------+-------+
| Sin                    | Y     | Y     |
+------------------------+-------+-------+
| Size                   | Y     | Y     |
+------------------------+-------+-------+
| `Slice`_               | Y     | Y     |
+------------------------+-------+-------+
| Softmax                | Y     | Y     |
+------------------------+-------+-------+
| `Split`_               | Y     | Y     |
+------------------------+-------+-------+
| Sqrt                   | Y     | Y     |
+------------------------+-------+-------+
| Squeeze                | Y     | Y     |
+------------------------+-------+-------+
| Sub                    | Y     | Y     |
+------------------------+-------+-------+
| Tanh                   | Y     | Y     |
+------------------------+-------+-------+
| Tile                   | Y     | Y     |
+------------------------+-------+-------+
| Transpose              | Y     | Y     |
+------------------------+-------+-------+
| Unsqueeze              | Y     | Y     |
+------------------------+-------+-------+
| Upsample               | Y     | Y     |
+------------------------+-------+-------+
| Upsample (deprecated)  | Y     | Y     |
+------------------------+-------+-------+
| Where                  | Y     | Y     |
+------------------------+-------+-------+
| Xor                    | Y     |       |
+------------------------+-------+-------+

Operator Shape Support Matrix
-----------------------------

The information below outlines a subset of the operators listed above and their basic supported shapes. The Vitis AI compiler may also support more complex data shapes, derived from these base types.

AveragePool
~~~~~~~~~~~

Implements average pooling over a 2D input.

**Supported Features:**
	
	**Data Types:** bf16, int8
	
	**ksize_h, ksize_w:** Pooling kernel height and width (1 to 20, step size 1)
	
	**stride_h, stride_w:** Kernel strides for height and width (1 to 20, step size 1)

Concat
~~~~~~~~~

Implements the concatenation operator.

**Supported Features:**
	
	**Data Types:** bf16, int8/uint8
	
	**Tensor Layout:** H (Height), C (Channels), W (Width), N (Batch Size)
	
	**concat_axis:** Specifies the axis along which concatenation is performed (allowed: 0 to 3, step size 1)

Conv2D (BF16)
~~~~~~~~~~~~~

Provides a 2D convolution operator in BF16 format, supporting a variety of activation functions.

**Supported Features:**
	
	**Data Types:** Input, weights, and output must be in bf16 format.
	
	**Batch Size:** 1, 2, or 4.
	
	**Activation Function:** 
		
		Applied at the operator output and natively fused with convolution.  
		
		Supported: LINEAR, RELU, LRELU. 
		
		Additional activation functions (e.g. sigmoid, tanh) are supported separately.
	
	**Kernel Size:**  
		
		Width: 1, 3, 4, 5, 7, 15, 16, 128  
		
		Height: 1, 3, 4, 5, 7, 9, 15  
		
		If kernel height is 3, kernel width must be either 3 or 15.  
		
		If kernel width is 15, kernel height must be 3.  
		
		If kernel height is 4, kernel width must be 16.  
		
		1xN or Nx1 kernels can be automatically converted to NxN if N is a supported width.
	
	**Dilation:** Only a dilation value of 1 is supported.
	
	**Stride:**  
		
		Height: 1, 2, 4, 8  
		
		Width: 1, 2, 4  
		
		If stride width is 4, stride height must also be 4 (and vice versa).

Conv2D (INT8)
~~~~~~~~~~~~~

Provides a 2D convolution operator in INT8 format, supporting various activation functions.

**Supported Features:**
	
	**Data Types:** Input, weights, and output must be in int8 format.
	
	**Batch Size:** 1, 2, or 4.
	
	**Activation Function:** 
		
		Applied at the operator output and natively fused with convolution.  
		
		Supported: LINEAR, RELU, LRELU. 
		
		Additional activation functions (e.g. sigmoid, tanh) are supported separately.
	
	**Kernel Size:**  
		
		Width: 1 to 16 (step size 1)  
		
		Height: 1 to 16 (step size 1)
	
	**Dilation:** Only a value of 1 is supported.
	
	**Stride:**  
	 
	 Height: 1 to 16 (step size 1)  
	 
	 Width: 1 or 2

DepthToSpace
~~~~~~~~~~~~

Rearranges data from the depth (channel) dimension into spatial blocks.  

Input Tensor: (N, C, H, W) -> Output Tensor: (N, C//(B*B), H*B, W*B)

**Supported Features:**
	
	**Data Types:** bf16, int8, uint8
	
	**Mode:** DCR, CRD
	
	**Block Size:** 2, 3, 4, 8

Gemm
~~~~

General Matrix Multiplication operator supporting matrix product, bias addition, and optional transposition of weights.

**Supported Features:**
	
	**Data Types:** bf16, int8, uint8
	
	**Computation:**  
		
		C(M, N) = A(M, K) x B(K, N) + bias
	
	**Ranges:**  
		
		M: 16 to 96 (step 16)  
		
		K: 64 to 128 (step 16); extended K: 1 to 65535 (step 1, by iteration)  
		
		N: 16 to 96 (step 16)
	
	**Bias Handling:**  
		
		When used, bias is padded to a multiple of 32 and is concatenated with the weights: Data layout: {bias_padded, weight}

GlobalAveragePool
~~~~~~~~~~~~~~~~~

Implements 2D global average pooling.

**Supported Features:**
	
	**Data Types:** bf16, int8
	
	**stride:** 1 to 20, step size 1
	
	**kernel size:** 1 to 20, step size 1

GroupedConv2D (BF16)
~~~~~~~~~~~~~~~~~~~~

Implements group convolution in bf16 format. This operator wraps the Conv2D kernel to enable grouped processing; a single kernel run can consume multiple feature map groups when input/output channels per group are small. (Specifications subject to change.)

**Supported Features:**
	
	**Data Types:** bf16 for input, weights, and output
	
	**Batch Size:** 1
	
	**Groups:** 1 to 255 (step size 1)
	
	**Activation Function:** 
		
		Applied at the operator output and natively fused with convolution.  
		
		Supported: LINEAR, RELU, LRELU. 
		
		Additional activation functions (e.g. sigmoid, tanh) supported separately.
	
	**Kernel Size:**  
		
		Width: 1, 3, 5, 7  
		
		Height: 1, 3, 5, 7
	
	**Dilation:** Only a value of 1 is supported
	
	**Stride:**  
		
		Height: 1 or 2  
		
		Width: 1 or 2

GroupedConv2D (INT8)
~~~~~~~~~~~~~~~~~~~~

Implements group convolution in int8 format.

**Supported Features:**
	
	**Data Types:** int8 for input, weights, and output
	
	**Batch Size:** 1
	
	**Groups:** 1 to 255 (step size 1)
	
	**Activation Function:** 
		
		Applied at the operator output and natively fused with convolution.  
		
		Supported: LINEAR, RELU, LRELU. 
		
		Additional activation functions (e.g. sigmoid, tanh) supported separately.
	
	**Kernel Size:**  
		
		Width: 1, 3, 5, 7, or 11  
		
		Height: 1, 3, 5, 7, or 11
	
	**Dilation:** Only a value of 1 is supported
	
	**Stride:**  
		
		Height: 1, 2, or 4  
		
		Width: 1, 2, or 4

MaxPool
~~~~~~~

Implements 2D max pooling.

**Supported Features:**
	
	**Data Types:** bf16, int8
	
	**stride:** 1 to 20, step size 1
	
	**kernel size:** 1 to 20, step size 1

Pad
~~~~

Implements 2D padding. The operator fills the edges of a tensor with the specified padding value. Supported modes: TOP, BOT, LEFT, RIGHT, BOTRIGHT, TOPLEFT.

**Supported Features:**
	
	**Data Types:** bf16, int8, uint8
	
	**Modes:** 0 (zero padding), runtime value padding
	
	**pad_left, pad_right, pad_top, pad_bot:** Positions padded on each edge (0 to 255, step size 1)

Resize
~~~~~~~~~

Implements tensor resizing with configurable interpolation.

**Supported Features:**
	
	**Data Types:** bf16, int8
	
	**Interpolation modes:**  
		
		mode: 0 (nearest), 1 (linear)  
		
		nearest_mode: 0 (floor), 1 (round_prefer_ceil), 2 (round_prefer_floor; default)
	
	**Scale Factor:** Maximum scale factor less than 32

Slice
~~~~~~~~~

Implements slicing of a tensor.

**Supported Features:**
	
	**Data Types:** bf16, int8
	
	**Slice indices:**  
		
		height_start, width_start, depth_start, height_end, width_end, depth_end (0 to 2048, step size 1)
		
		height_step, width_step, depth_step (1 to 2048, step size 1)

Split
~~~~~~~~~

Implements tensor splitting along a specified axis.

**Supported Features:**
	
	**Data Types:** bf16, int8, uint8
	
	**split_axis:** Axis to split on (allowed values: 0 to 2, step size 1)
