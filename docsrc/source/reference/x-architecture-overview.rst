VART X APIs Architecture Overview
==================================

VART X framework is designed to enable applications with device management, preparing input and retrieval of results from inference operations, video format conversions, utilize hardware acceleration, and perform frame overlay. VART X framework provides a set of modules, each offering C++ APIs that seamlessly integrate into any application. These modules include Device, VideoFrame, Pre-processing, Post-processing, Metaconvert, Overlay. Additionally, it includes supporting modules such as InferResult and Memory, which serve as helper modules. Each module is available as a dynamic shared object (.so) file, allowing applications to dynamically link with these files as needed.

.. image:: images/vart-stack.png
   :alt: Training Neural Network
	:width: 400
	:align: center

VART X API Design
~~~~~~~~~~~~~~~~~~~~

VART X provides C++ APIs that adhere to the implementation design pattern, promoting encapsulation and maintainability. You do not need to relink with the application in case of any changes to the implementation, as long as the external interface remains unchanged. VART X leverages the VVAS-CORE framework for hardware acceleration tasks, which is supported by the XRT module. You can seamlessly integrate VART X Modules in the application using the classes as illustrated in the below diagram. Additionally, you can take advantage of in-built supported features/types (for example, post-processing by default supports YOLOv2, ResNet50, SSD-ResNet34). For a comprehensive list of default in-built supported features/types, refer to the API documentation. Alternatively, if you wish to integrate custom implementations for modules like Pre-processing and post-processing, refer to the Integrating Custom Implementation into VART X Modules section.

.. image:: images/vart-x-modues.png
   :alt: Training Neural Network
	:width: 400
	:align: center

.. note::
   If you opt to utilize only built-in supported features/types, then you need not use VART::ModuleBaseImpl class.
   For example, if you opt to utilize only built-in post-processing types like YOLOv2, ResNet50, SSD-ResNet34, then in such scenarios you do not need to use the PostProcessImplBase base class.

VART X API Modules
~~~~~~~~~~~~~~~~~~~~~

**Device:** Manages the hardware context and loading of xclbin onto the device. Refer to the API documentation for more information.

**Videoframe:** Simplifies the management of frame memory complexities and provides APIs for allocation (Heap & XRT backed memory), deallocation, reading, and writing a frame. The VideoFrame class offers flexibility for applications to encapsulate their own memory into the VideoFrame class. In such instances, the application bears the responsibility for deallocating the frame memory.

**Pre-processing:** Handles data preparation tasks such as normalization, scaling, and video format conversion. This module supports software-based pre-processing as well as hardware-accelerated pre-processing for optimized performance. It ensures that input data is appropriately formatted for inference. The application can also incorporate custom pre-processing by overriding base class methods.

**Post-processing:** Performs additional computations on output tensor data from NPU to generate a more meaningful interpretation. Post-processing by default supports YOLOv2, ResNet50, SSD-ResNet34. Refer to the API documentation on usage and additional information. If an application requires custom post-processing, it can override the base class methods.

**Metaconvert:** Facilitates the conversion of Infer metadata into a format compatible with the overlay module. Metaconvert also accepts configuration parameters as JSON strings, which provide further flexibility on configuring overlay information such as line thickness, font size, and font type. Refer to the API documentation for more information. Additionally, if you have custom metadata then can integrate customized functions to convert them into a format suitable for processing by the overlay module by overriding the base class.

**Overlay:** Facilitates the overlay of annotations onto the video frame. Currently overlay utilizes the OpenCV library to draw on frames, which is software-based. Overlay supports drawing bounding boxes, text, lines, arrows, circles, and polygons on frames. The application can also incorporate custom implementation using the base class.

**InferResult:** Represents inference results. Presently, the default supported types include classification and detection. Users can integrate new types by overriding base class methods to incorporate custom inference results. For additional information, please check API documentation.

**Memory:** Responsible for allocating and managing memory on the device.

Integrating Custom Implementation into VART X Modules
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Each VART Module exposes a base class, allowing you to inherit and add custom implementations. These implementations can then be seamlessly integrated into the modules, ensuring flexibility and ease of use. The following figure is a representation of how you can integrate custom implementations.

.. image:: images/vart-custom-implementation.png
   :alt: Training Neural Network
	:width: 400
	:align: center


