.. _namespace-doc:

Namespace Documentation
=======================

See also: :ref:`Namespace Index <namespace-index>`, :ref:`Class Index <class-index>`, and :ref:`Class Documentation <class-doc>`.

.. _ns-vart:

vart Namespace Reference
------------------------

Classes
-------

- :ref:`NpuTensorInfo <class-vart-nputensorinfo>` — Contains metadata information about a tensor used in the NPU.
- :ref:`NpuTensor <class-vart-nputensor>` — Class representing a tensor in the VART API.
- :ref:`QuantParameters <class-vart-quantparameters>` — Struct representing quantization parameters for a tensor.
- :ref:`JobHandle <class-vart-jobhandle>` — Struct representing a job handle for asynchronous execution.
- :ref:`Runner <class-vart-runner>` — Abstract base class for executing model inference operations.
- :ref:`RunnerFactory <class-vart-runnerfactory>` — Factory class for creating Runner instances.

Detailed Description
--------------------

Enumeration Type Documentation
------------------------------

.. _enum-datatype:

DataType
^^^^^^^^
Enumerates the supported data types for tensors in the VART API.

- UNKNOWN — Unknown data type.
- INT8 — 8-bit signed integer.
- UINT8 — 8-bit unsigned integer.
- INT16 — 16-bit signed integer.
- UINT16 — 16-bit unsigned integer.
- BF16 — 16-bit Brain Floating Point format.
- FP16 — 16-bit floating point.
- FLOAT32 — 32-bit floating point.

.. _enum-devicetype:

DeviceType
^^^^^^^^^^
Enumerates the types of devices supported by the VART API.

- UNKNOWN — Unknown device type.
- ZEBRA — Zebra devices.
- VAIML — Vaiml devices.

.. _enum-memorylayout:

MemoryLayout
^^^^^^^^^^^^
Enumerates the supported memory layouts for tensors in the VART API.

- UNKNOWN — Unknown memory layout.
- NHW — Batch, Height, Width.
- NHWC — Batch, Height, Width, Channels (packed format).
- NCHW — Batch, Channels, Height, Width (planar format).
- NHWC4 — Batch, Height, Width, Channel groups of 4.
- NC4HW4 — Batch, Channels/4, Height, Width, Channel groups of 4.
- NC8HW8 — Batch, Channels/8, Height, Width, Channel groups of 8.
- HCWNC4 — Height, Channels/4, Width, Batch, Channel groups of 4.
- HCWNC8 — Height, Channels/8, Width, Batch, Channel groups of 8.
- GENERIC — Generic layout. See :ref:`NpuTensorInfo::memory_layout_order <class-vart-nputensorinfo>`.

.. _enum-memorytype:

MemoryType
^^^^^^^^^^
Enumerates the types of memory used for tensors in the VART API.

- UNKNOWN — Unknown memory type.
- DEVICE — Device (hardware) memory, typically used for inference on accelerators.
- HOST — Host memory, typically used for CPU operations.

.. _enum-roundingmode:

RoundingMode
^^^^^^^^^^^^
Enumerates the rounding modes used in quantization.

- UNKNOWN — Unknown rounding mode.
- ROUND_TO_NEAREST_EVEN — Round to nearest even value.
- ROUND_TOWARD_ZERO — Truncate towards zero (no rounding).

.. _enum-statuscode:

StatusCode
^^^^^^^^^^
Enumerates the status codes used in the VART API.

- SUCCESS — Operation completed successfully.
- FAILURE — Operation failed.
- INVALID_INPUT — Invalid input parameters.
- INVALID_OUTPUT — Invalid output parameters.
- OUT_OF_MEMORY — Memory allocation failed.
- RUNTIME_ERROR — Runtime error occurred.
- TIMEOUT — Operation timed out.
- DEVICE_ERROR — Device-specific error occurred.

.. _enum-tensordirection:

TensorDirection
^^^^^^^^^^^^^^^
Enumerates the supported tensor directions in the VART API.

- INPUT — Input tensor direction.
- OUTPUT — Output tensor direction.

.. _enum-tensortype:

TensorType
^^^^^^^^^^
Defines the types of tensors supported in the VART API.

- CPU — CPU-side tensor representing the model’s actual inputs and outputs. Used for non-zero copy scenarios.
- HW — Device (hardware) tensor representing NPU inputs and outputs, enabling zero-copy execution.

Note: AI engines typically have their own memory layouts and data types, which may differ from those defined by the model. The CPU tensor corresponds to the model’s original tensor information, while the HW tensor refers to the AI engine’s representation. The VART framework manages conversions between CPU and HW tensors, but these conversions can introduce copies that impact latency and performance. To minimize overhead, users may implement their own conversion logic to achieve true zero-copy operations.
