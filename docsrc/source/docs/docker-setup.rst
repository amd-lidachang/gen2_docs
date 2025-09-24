Docker Setup
============

1. Download the Docker image file named `vitis_ai_2ve_2025.1_web_docker.tgz` from `this link <https://account.amd.com/en/forms/downloads/eula-xef.html?filename=vitis_ai_2ve_2025.1_web_docker.tgz>`__.

2. Execute the following code to load the Docker image onto a system where Docker is installed (for installation instructions, refer to `Install Docker Engine on Ubuntu <https://docs.docker.com/engine/install/ubuntu/>`_, `Linux post-installation steps for Docker Engine <https://docs.docker.com/engine/install/linux-postinstall/>`_, or consult your system administrator):

   .. code-block:: bash

      docker load -i vitis_ai_2ve_2025.1_web_docker.tgz

   .. note::

      Loading the Docker image might take a few minutes.

3. Run this to verify the “REPOSITORY”, “IMAGE ID” and “TAG” information of the Docker image:

   .. code-block:: bash

      docker images

   You can see the output in the following format:

   .. list-table::
      :header-rows: 1
      :widths: 25 25 25 15 10

      * - REPOSITORY
        - TAG
        - IMAGE ID
        - CREATED
        - SIZE
      * - vitis_ai_2ve_docker
        - release_v5.1_bash
        - 65fc9165b3de
        - xx hours ago
        - 37.3GB


4. Start a Docker container with the specified directories mounted using:

   .. code-block:: bash

      docker run -it --rm -v /yourDir/models:/Model vitis_ai_2ve_docker:release_v2025.1_0819 "bash"

   .. note::

      Use the `-v` option to map the specified host directory to the designated directory within the Docker container.

5. Execute the following to Set up the compilation environment inside the Docker container:

   .. code-block:: bash

      source /opt/xilinx/arm_env.bash
