System Requirements
===================


Hardware Requirements
---------------------

The following table lists Vitis |trade| AI developer workstation hardware requirements:

.. list-table::
   :widths: 10 20
   :header-rows: 1

   * - Component
     - Requirement

   * - Host Machine
     - Any 64-bit Linux host machine with Ubuntu 22.04.4 LTS OS, 100 GB of free disk space, 64 GB of RAM and minimum of 20 Cores

   * - Software Packages
     - Includes binaries for PDI, Linux images, models, and Docker

   * - Target Board
     - VEK385 RevA card with pre-production silicon

   * - Connectivity
     - VEK385 target board connected to the host machine with an ethernet cable and an UART USB cable. The cable (Type A to Type C) provided with the VEK385 board for connectivity. Type A is connected to the host and Type C is connected to the board


.. note::

   You can connect the VEK385 target board to a host machine for convenient file transfers, for example transferring snapshot files. However, a network connection is not required to run inference.


Software Requirements
---------------------

.. list-table::
   :widths: 10 20
   :header-rows: 1


   * - Component
     - Requirement

   * - HOST OS
     - Ubuntu 22.04.4 LTS 

   * - Vivado
     - Version 2025.1

   * - Python
     - Version 3.10.12

   * - Docker
     - Version 24.0.5


.. note::
    - Docker versions up to 24.0.5 have been verified for compatibility. While newer Docker versions might function properly, they have not been formally tested with Vitis AI.



.. |trade|  unicode:: U+02122 .. TRADEMARK SIGN
   :ltrim:
.. |reg|    unicode:: U+000AE .. REGISTERED TRADEMARK SIGN
   :ltrim:

