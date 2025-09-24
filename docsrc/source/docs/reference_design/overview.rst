==========================
Reference Design Overview
==========================

Introduction to the integrated reference design and its scope:

Vitis AI includes a reference design that integrates hardware-accelerated pre-processing and runs the machine learning inference on the Neural Processing Unit (NPU). This design showcases a complete, end-to-end pipeline from ingesting image or video inputs to producing and saving the inference results.

Supported Features:
-------------------

- Hardware-accelerated pre-processing via the Image Processing PL kernel, including resizing, color space conversion, normalization, and cropping.
- Inference execution on the NPU.
- Software-based post-processing on the CPU.
- Visualization utilities to overlay bounding boxes and labels (text) on the input image based on inference results.

The package includes:
---------------------

- Source code for the System Integrated Reference Design.
- Sample applications that demonstrate both standalone and combined ML inference accelerated on the AI Engines, hardware-accelerated pre-processing using the image_processing PL HLS(High Level SYnthesis) kernel, and CPU-based post-processing.
- Ready-to-test boot images that embed the application binary for immediate evaluation on target hardware.

Requirements
------------

To build the reference design and deploy it on board, the following setup are required:

- System Requirements :doc:`system_requirements`
- Docker Setup :doc:`docker_setup`
- Board Setup :doc:`board_setup`

Download Reference Design:
-----------------------------
Download the reference design:

sv_rel.tar.gz

The release package includes:

- Boot images
- ONNX model
- VART-based and ONNX Runtime based applications
- Source code for the VAIML Platform Reference Design

Extract the package to the /home directory on the host machine. If you choose a different location, ensure all related commands, scripts, and environment references are updated to reflect the new path.

Assumptions

- The release archive contains a top-level amd/ directory.
- You have sudo privileges on the host.

Steps

1. Extract the release package to /home (creates /home/amd)

.. code-block::

	sudo tar -xvf sv_rel_aug2025.tar.gz -C /home
	cd /home/amd

2. Prepare the root filesystem (rootfs) for NFS export

.. code-block::

	# Create the rootfs directory
	sudo mkdir rootfs

	# Extract the rootfs image into /home/amd/rootfs
	sudo tar -xvf boot_images/rootfs.tar.gz -C rootfs

3. Copy required folders into the rootfs

.. code-block::

	# Copy overlay into rootfs
	sudo cp -r boot_images/overlay rootfs/

	# Copy host application binaries into rootfs
	sudo cp -r host_app_binaries rootfs/


4. Unarchive the host application sources to your chosen location

.. code-block::

	# Replace <sources_path> with an actual writable directory (e.g., /home/amd/sources)
	tar -xvf /home/amd/sources/vaiml_platform_host_app.tar.gz -C <sources_path>

.. note::

	Do not extract the rootfs into the boot_images directory (often owned by the tftp user). Always extract into a separate directory (e.g., /home/amd/rootfs) using a sudo-capable user.

If your release archive does not create /home/amd automatically, create it first and adjust the commands accordingly:

.. code-block::

	sudo mkdir -p /home/amd
	sudo tar -xvf sv_rel_aug2025.tar.gz -C /home/amd
	cd /home/amd

After extraction, verify directory structure and permissions before exporting rootfs over NFS.

Directory structure
-------------------
