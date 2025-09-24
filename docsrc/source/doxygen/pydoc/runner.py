"""!
    @brief Executes the runner with the given inputs. The VART.Runner can take the following optional arguments to build a model:
    model methods to enable Zero copy
    The API can support zero copy feature for input and output buffers.

    Such buffers are accessible directly by the NPU IP, and therefore have to be allocated physically in the DDR memory. A buffer allocated by a classic python function can't be used directly by the NPU. Only a buffer allocated by XRT can be used.
    As a consequence, the API provides a function to allocate the input buffers. The python application needs to write (like using np.copyto) into that buffer.
    However, the output buffers can be allocated directly by the SW stack, the inference call can return directly a physically allocated buffer.
    - set_output_native_formats(bool)     take a bool to enable native outputs
    - set_input_native_formats(bool)      take a bool to enable native inputs
    - alloc_native_bufs(nbImages)         allocate input buffers to be used for native input.
                                    nbImages is an optional argument, default value is the batch size of the snapshot.
                                    Returns a list of buffers of size nbInputs x nbImages with the same order as C++ stack,
                                    so for a 2 inputs batch size of 3:
                                    [inputA_batch0, inputB_batch0, inputA_batch1, inputB_batch1, inputA_batch2, inputB_batch2]
    Limitations for the zero copy API
    - input format is in NHWC.
    - maximum of input channels supported is 8.
    - model with multiple inputs with batchSize > 1 hasn't been validated
    - input and output of the models don't have the same type as the classic mode:
        - zero copy exposes each batch as a separate buffer. It allows having each buffer on a separate DDR memory, to optimize efficiency.
        - while the default mode concatenates each batch in the same buffer.
    @param snapshot_dir path of the snapshot, default is to take the content of the variable environment VAISW_SNAPSHOT_DIRECTORY
    @param network_name name of the model
    @param output_names list of output to return, default is to return all outputs
    @param npu_only runs only the sub-graphs executed on the AIE, CPU subgraphs are ignored
    @return  VART.Runner

    Sample code:

  @code
    import VART

    model = VART.Runner()
    output_inference = model(input_inference)
  @endcode
"""
"""!
    @brief Executes the runner with the given inputs. The VART.Runner can take the following optional arguments to build a model:
    @param snapshot_dir path of the snapshot, default is to take the content of the variable environment VAISW_SNAPSHOT_DIRECTORY
    @param network_name name of the model
    @param output_names list of output to return, default is to return all outputs
    @param npu_only runs only the sub-graphs executed on the AIE, CPU subgraphs are ignored
    @return  The return by VART.Runner has the following properties : 
      1. input_shapes            a list of list of uint32 indicating the shape of each input.
      2. input_shape_formats     a list of string indicating the format of each input ('NCHW', 'NHWC').
      3. input_types             a list of datatype indicating the type for each input.
      4. output_shape_formats    a list of string indicating the format of each output ('NCHW', 'NHWC')

    Sample code:

  @code
    import VART

    model = VART.Runner()
    output_inference = model(input_inference)
    model = VART.Runner()
    model.set_input_native_formats(True)
    model.set_output_native_formats(True)
    native_input = model.alloc_native_bufs()
    np.copyto(native_input[0], input_infernce[0])
    output_inference = model(input_inference)
  @endcode
"""



class VART:
    """
    @brief A Python API for VART, providing NPU-based model inference.

    This class wraps the VART C++ API for Python, leveraging an NPU Runner for execution.
    """

    def __init__(self, snapshot_dir: str, network_name: str, output_names: Optional[List[str]] = None, npu_only: bool = False):
        """
        @brief Construct a new VART object from a snapshot.

        @param snapshot_dir Directory containing the snapshot.
        @param network_name Name of the network.
        @param output_names Optional list of output tensor names.
        @param npu_only If True, use NPU exclusively for inference.
        """
        # Initialize the Runner member explicitly
        self.runner = None  # Placeholder for vart::Runner instance
        pass

    def init_out_arrays(self, use_native_bufs: bool = False) -> None:
        """
        @brief Initializes output arrays.

        @param use_native_bufs If True, allocate native buffers for output data.
        """
        pass

    def alloc_native_bufs(self, shape: List[List[int]], nb_images: int) -> List[np.ndarray]:
        """
        @brief Allocates native buffers for given shapes and returns NumPy arrays.

        @param shape List of shapes for the buffers to allocate.
        @param nb_images Number of images in the buffer.
        @return List of NumPy arrays pointing to the allocated buffers.
        """
        pass

    def get_input_shapes(self) -> List[List[int]]:
        """
        @brief Gets the shapes of the model's input tensors.

        @return List of input tensor shapes.
        """
        pass

    def get_input_shape_formats(self) -> List[str]:
        """
        @brief Gets the shape formats of the model's input tensors.

        @return List of input shape formats.
        """
        pass

    def get_output_shape_formats(self) -> List[str]:
        """
        @brief Gets the shape formats of the model's output tensors.

        @return List of output shape formats.
        """
        pass

    def get_input_types(self) -> List[np.dtype]:
        """
        @brief Gets the data types of the model's input tensors.

        @return List of NumPy data types for input tensors.
        """
        pass

    def set_input_native_formats(self, value: bool) -> bool:
        """
        @brief Sets whether input buffers are in native format.

        @param value If True, use native input format.
        @return True if the format was set successfully, False otherwise.
        """
        pass

    def set_output_native_formats(self, value: bool) -> bool:
        """
        @brief Sets whether output buffers are in native format.

        @param value If True, use native output format.
        @return True if the format was set successfully, False otherwise.
        """
        pass

    def get_input_coeffs(self) -> List[float]:
        """
        @brief Gets the quantization coefficients for input tensors.

        @return List of input quantization coefficients.
        """
        pass

    def get_output_coeffs(self) -> List[float]:
        """
        @brief Gets the quantization coefficients for output tensors.

        @return List of output quantization coefficients.
        """
        pass

    def execute(self, inputs: List[np.ndarray]) -> List[np.ndarray]:
        """
        @brief Executes the model using the Runner.

        @param inputs List of input buffers.
        @return List of output buffers.
        """
        pass