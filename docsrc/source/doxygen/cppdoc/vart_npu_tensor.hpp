/*
 * Copyright (C) 2025 Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace vart {

/**
 * @enum DataType
 * @brief Enumerates the supported data types for tensors in the VART API.
 *
 * This enum defines the various data types that can be used to represent tensor
 * elements. It includes integer and floating-point formats, as well as
 * specialized types such as BF16.
 *
 * - UNKNOWN:        Unknown data type.
 * - INT8:           8-bit signed integer.
 * - UINT8:          8-bit unsigned integer.
 * - INT16:          16-bit signed integer.
 * - UINT16:         16-bit unsigned integer.
 * - BF16:           16-bit Brain Floating Point format.
 * - FP16:           16-bit floating point.
 * - FLOAT32:        32-bit floating point.
 */
enum class DataType {
  UNKNOWN,
  INT8,
  UINT8,
  INT16,
  UINT16,
  BF16,
  FP16,
  FLOAT32,
};

/**
 * @enum MemoryLayout
 * @brief Enumerates the supported memory layouts for tensors in the VART API.
 *
 * This enum defines the various memory layouts that can be used to represent
 * tensor data. It includes formats such as NHWC, NCHW, and others that specify
 * how tensor dimensions are organized in memory.
 *
 * - UNKNOWN:       Unknown memory layout.
 * - NHW:           Batch, Height, Width.
 * - NHWC:          Batch, Height, Width, Channels (packed format).
 * - NCHW:          Batch, Channels, Height, Width (planar format).
 * - NHWC4:         Batch, Height, Width, Channel groups of 4 (e.g RGBA).
 * - NC4HW4:        Batch, Channels / 4, Height, Width, Channel groups of 4.
 * - NC8HW8:        Batch, Channels / 8, Height, Width, Channel groups of 8.
 * - HCWNC4:        Height, Channels / 4, Width, Batch, Channel groups of 4.
 * - HCWNC8:        Height, Channels / 8, Width, Batch, Channel groups of 8.
 * - GENERIC:       Generic layout. See NpuTensorInfo::memory_layout_order for
 * more info.
 */
enum class MemoryLayout {
  UNKNOWN,
  NHW,
  NHWC,
  NCHW,
  NHWC4,
  NC4HW4,
  NC8HW8,
  HCWNC4,
  HCWNC8,
  GENERIC,
};

/**
 * @enum MemoryType
 * @brief Enumerates the types of memory used for tensors in the VART API.
 *
 * This enumeration defines where tensor data resides:
 * - UNKNOWN: Memory type is unspecified.
 * - DEVICE:  Represents device or physical memory (e.g., `xrt::bo`).
 * - HOST:    Represents virtual pointer-based memory in system RAM, usually
 * accessed by the CPU.
 */
enum class MemoryType {
  UNKNOWN,
  DEVICE,
  HOST,
};

/**
 * @enum TensorDirection
 * @brief Enumerates the supported tensor directions in the VART API.
 *
 * This enum defines the various directions that tensors can have in the context
 * of model inference. It includes input and output directions.
 *
 * - INPUT:         Input tensor direction.
 * - OUTPUT:        Output tensor direction.
 *
 */
enum class TensorDirection { INPUT, OUTPUT };

/**
 * @enum TensorType
 * @brief Specifies the tensor types supported in the VART API.
 *
 * Enumerates the available tensor types:
 * - CPU: Represents tensor metadata from the ONNX model, as defined for
 * standard CPU execution.
 * - HW:  Corresponds to AMD hardware-specific tensor metadata, formatted for
 * direct execution on AMD AI engines.
 *
 * @note AMD optimizes its AI engines with unique data formats and memory
 * layouts. As a result, the HW tensor layout and format will typically differ
 * from the CPU tensor representation defined by the ONNX model.
 */
enum class TensorType { CPU, HW };

/**
 * @struct NpuTensorInfo
 * @brief Metadata structure describing a tensor used in VART.
 *
 * Contains various attributes used to define and manage a tensor:
 *
 * @var NpuTensorInfo::name
 *   Name of the tensor.
 *
 * @var NpuTensorInfo::data_type
 *   Data type of the tensor elements.
 *
 * @var NpuTensorInfo::memory_layout
 *   Memory layout type of the tensor.
 *
 * @var NpuTensorInfo::memory_layout_order
 *   (Optional) Dimension permutation order for buffer data, relevant when
 * memory_layout is GENERIC. Specifies the order in which dimensions are
 * arranged compared to the reference TensorType::CPU tensor format. For
 * example, if the TensorType::CPU format is "ABCD", memory_layout_order is {0,
 * 1, 2, 3}; if the TensorType::HW format is "ADBC", memory_layout_order is {0,
 * 3, 1, 2}.
 *
 * @var NpuTensorInfo::size
 *   Number of elements in the tensor.
 *
 * @var NpuTensorInfo::size_in_bytes
 *   Size of the tensor data in bytes.
 *
 * @var NpuTensorInfo::shape
 *   Dimensions of the tensor.
 *
 * @var NpuTensorInfo::strides
 *   (Optional) Stride values for each dimension.
 *
 * @fn void NpuTensorInfo::print() const
 *   Prints tensor metadata to standard output.
 */
struct NpuTensorInfo {
  std::string name;
  DataType data_type;
  MemoryLayout memory_layout;
  std::vector<uint32_t> memory_layout_order;
  size_t size;
  size_t size_in_bytes;
  std::vector<uint32_t> shape;
  std::vector<uint32_t> strides;

  void print() const;
};

/**
 * @brief This class represents a tensor in the VART API.
 *
 * This class encapsulates tensor metadata and offers access to the tensor's
 * data buffers. It acts as a lightweight wrapper around buffers supplied by the
 * user.
 *
 * @note: This class does not take ownership of the buffer memory.
 * The user is responsible for managing the buffer's lifecycle.
 */
class NpuTensor {
 public:
  /**
   * @brief Construct a NpuTensor from a user-supplied buffer.
   *
   * Initializes the tensor using the specified metadata and buffer.
   *
   * @param info      Tensor metadata (NpuTensorInfo).
   * @param buffer    Pointer to the user buffer containing the tensor data.
   * @param mem_type  Specifies whether the buffer is in host or device memory
   * (HOST or DEVICE).
   * @param type      Indicates the tensor type (CPU or HW).
   *
   * @note When using TensorType::HW:
   *   - The buffer must be of MemoryType::DEVICE.
   *   - The data should be pre-processed to meet hardware requirements.
   *   - TensorType::HW supports zero-copy operations only.
   *     If the buffer is not pre-processed or compatible with hardware, use
   * TensorType::CPU instead.
   */
  NpuTensor(const NpuTensorInfo& info,
            void* buffer,
            const MemoryType& mem_type,
            const TensorType& type = TensorType::CPU);

  NpuTensor() = delete;                        // Disable default constructor
  NpuTensor(const NpuTensor& other) = delete;  // Disable copy constructor
  NpuTensor& operator=(const NpuTensor& other) =
      delete;  // Disable copy assignment

  NpuTensor(NpuTensor&& other) noexcept;             // Move constructor
  NpuTensor& operator=(NpuTensor&& other) noexcept;  // Move assignment

  /**
   * @brief Returns a pointer to the buffer associated with the specified memory
   * type.
   *
   * Provides access to the buffer associated with the given memory type.
   *
   * @param mem_type The memory type (e.g., DEVICE or HOST) for which to
   * retrieve the buffer.
   * @return void*   Pointer to the buffer, or nullptr if no buffer is available
   * for the requested memory type.
   */
  void* get_buffer(MemoryType mem_type) const;

  /**
   * @brief Returns the NpuTensorInfo metadata of the tensor.
   *
   * This method returns the NpuTensorInfo object that contains metadata about
   * the tensor, such as its name, shape, strides, data type, and memory layout.
   * @return A constant reference to the NpuTensorInfo object.
   */
  const NpuTensorInfo& get_info() const;

  /**
   * @brief Returns the type of the tensor.
   *
   * @return The type of the tensor (CPU or HW).
   */
  TensorType get_tensor_type() const;

  /**
   * @brief Get the memory type of the tensor.
   *
   * @return MemoryType The memory type of the tensor, which can be either HOST
   * or DEVICE.
   */
  MemoryType get_memory_type() const;

  /**
   * @brief Prints the metadata of the tensor.
   *
   * This method prints the NpuTensorInfo metadata, including name, shape,
   * strides, data type, memory layout, and size. It is useful for debugging and
   * understanding the tensor's properties.
   */
  void print_info() const;

 private:
  NpuTensorInfo info_;      // Tensor metadata
  void* buffer_;            // Pointer to the buffer memory (host or device)
  MemoryType memory_type_;  // Memory type (HOST or DEVICE)
  TensorType type_;         // Tensor type (CPU or HW)
};

}  // namespace vart
