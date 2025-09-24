.. _class-doc:

Class Documentation
===================

See also: :ref:`Class Index <class-index>`, :ref:`Namespace Index <namespace-index>`, and :ref:`Namespace Documentation <namespace-doc>`.

.. _class-vart-jobhandle:

vart::JobHandle — Struct Reference
----------------------------------

Struct representing a job handle for asynchronous execution.

Public Attributes
^^^^^^^^^^^^^^^^^

- StatusCode status
- uint32_t job_id

Detailed Description
^^^^^^^^^^^^^^^^^^^^

Struct representing a job handle for asynchronous execution. This struct holds the status of a submitted job, including whether it was successfully submitted and its unique identifier.

Member Data Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^

- job_id — Unique identifier for the job.

Header
^^^^^^

- include/vart_runner_factory.hpp

Back to: :ref:`Class Index <class-index>`

.. _class-vart-nputensor:

vart::NpuTensor — Class Reference
---------------------------------

Class representing a tensor in the VART API.

Public Member Functions
^^^^^^^^^^^^^^^^^^^^^^^

- NpuTensor(const NpuTensorInfo& info, void* buffer, const MemoryType& mem_type, const TensorType& type=TensorType::CPU)
- NpuTensor(const NpuTensor& other)=delete
- NpuTensor& operator=(const NpuTensor& other)=delete
- NpuTensor(NpuTensor&& other) noexcept
- NpuTensor& operator=(NpuTensor&& other) noexcept
- void* get_buffer(MemoryType mem_type) const — Returns a pointer to the buffer for the specified memory type.
- uint64_t get_device_buffer_phy_address() const — Returns physical address of the device buffer.
- const NpuTensorInfo& get_info() const — Returns tensor metadata.
- TensorType get_tensor_type() const — Returns the tensor type.
- MemoryType get_memory_type() const — Returns the memory type.
- void print_info() const — Prints the tensor metadata.

Detailed Description
^^^^^^^^^^^^^^^^^^^^

Encapsulates metadata and memory management for tensors used in model inference. Provides methods for allocation, access, and manipulation of tensor data.

Constructor Notes
^^^^^^^^^^^^^^^^^

NpuTensor(const NpuTensorInfo& info, void* buffer, const MemoryType& mem_type, const TensorType& type=TensorType::CPU)

- Creates a NpuTensor from a user buffer.
- For TensorType::HW, the buffer must be MemoryType::DEVICE and pre-processed per HW requirements. HW is meant for zero copy only; if the tensor is not HW-compatible, use TensorType::CPU.

Back to: :ref:`Class Index <class-index>`, see also: :ref:`NpuTensorInfo <class-vart-nputensorinfo>`

.. _class-vart-nputensorinfo:

vart::NpuTensorInfo — Struct Reference
--------------------------------------

Contains metadata information about a tensor used in the NPU.

Public Member Functions
^^^^^^^^^^^^^^^^^^^^^^^

- void print() const — Prints metadata.

Member Data
^^^^^^^^^^^

- DataType data_type
- MemoryLayout memory_layout
- std::vector<uint32_t> memory_layout_order
- std::string name
- std::vector<uint32_t> shape
- size_t size
- size_t size_in_bytes
- std::vector<uint32_t> strides

Notes
^^^^^

- memory_layout_order is used when MemoryLayout is GENERIC and indicates the dimension permutation relative to CPU format.

Back to: :ref:`Class Index <class-index>`

.. _class-vart-quantparameters:

vart::QuantParameters — Struct Reference
----------------------------------------

Struct representing quantization parameters for a tensor.

Member Data
^^^^^^^^^^^

- double scale — Scale factor for quantization.
- int32_t zero_point — Optional zero point for asymmetric quantization.
- RoundingMode rounding_mode — Rounding mode used during quantization.

Back to: :ref:`Class Index <class-index>`

.. _class-vart-runner:

vart::Runner — Class Reference
------------------------------

Abstract base class for executing model inference operations.

Public Types
^^^^^^^^^^^^

- using ExecuteAsyncCallback = std::function<void(StatusCode)>

Constructor & Destructor
^^^^^^^^^^^^^^^^^^^^^^^^

- virtual ~Runner() = default
- protected explicit Runner(const std::string& model_path, const std::unordered_map<std::string, std::any>& options = {})

Member Functions
^^^^^^^^^^^^^^^^

- virtual const std::vector<NpuTensorInfo>& get_tensors_info(const TensorDirection& direction, const TensorType& type) const = 0
- virtual const NpuTensorInfo& get_tensor_info_by_name(const std::string& tensor_name, const TensorType& type) const = 0
- virtual const QuantParameters& get_quant_parameters(const std::string& tensor_name) const = 0
- virtual size_t get_num_input_tensors() const = 0
- virtual size_t get_num_output_tensors() const = 0
- virtual size_t get_batch_size() const = 0
- virtual StatusCode execute(const std::vector<std::vector<NpuTensor>>& inputs, std::vector<std::vector<NpuTensor>>& outputs) = 0
- virtual JobHandle execute_async(const std::vector<std::vector<NpuTensor>>& inputs, std::vector<std::vector<NpuTensor>>& outputs) = 0
- virtual StatusCode wait(const JobHandle& job_handle, unsigned int timeout) = 0
- virtual StatusCode execute_async(const std::vector<std::vector<NpuTensor>>& inputs, std::vector<std::vector<NpuTensor>>& outputs, ExecuteAsyncCallback cb, unsigned int timeout) = 0

Back to: :ref:`Class Index <class-index>`

.. _class-vart-runnerfactory:

vart::RunnerFactory — Class Reference
-------------------------------------

Factory class for creating Runner instances.

Member Functions
^^^^^^^^^^^^^^^^

- create_runner() — Creates a Runner instance for the given model and options.

Back to: :ref:`Class Index <class-index>`
