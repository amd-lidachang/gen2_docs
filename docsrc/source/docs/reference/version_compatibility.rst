.. _version-compatibility:

IP and Tool Version Compatibility
=================================

This page provides information on the compatibility between tools, IP, and Vitis |trade| AI release versions. Ensure that you are using the supported versions of all the components.

Current Release
---------------

Vitis AI v2025.1 is available in the `Vitis AI lounge <https://account.amd.com/en/member/vitis-ai-ea-release.html>`_. Starting from Vitis AI 2024.1EA, AMD renamed the DPU to NPU for better unified naming. The Vitis AI 2024.1EA and NPU IP released with the 2024.1EA branch are verified to be compatible with AMD Vitis |trade|, AMD Vivado |trade|, and Petalinux version 2024.1 release.

.. list-table::
   :widths: 25 25 25 25
   :header-rows: 1

   * - Vitis AI Release Version
     - NPU IP Version
     - Software Tools Version
     - Linux Kernel Version Tested

   * - 2024.1
     - 0x32650C74 (performance NPU IP)
       0x0E981B52 (functional NPU IP)
     - Vitis / PetaLinux 2024.1
     - 5.15.0-87-generic

   * - 2024.1EA
     - 0xD7FC51A7
     - Vitis / PetaLinux 2024.1
     - 5.15.0-87-generic


Versal |trade| AI Edge


All Releases
------------

If you are using a previous release of Vitis AI, refer to the following table for the corresponding releases.



.. list-table::
   :widths: 25 25 25 25
   :header-rows: 1

   * - Vitis AI Release Version
     - DPUCV2DX8G IP Version
     - Software Tools Version
     - Linux Kernel Version Tested

   * - v3.5
     - 1.0
     - Vitis / PetaLinux 2023.1
     - 6.1

   * - v3.0
     - Early Access
     - Vitis / PetaLinux 2022.2
     - 5.15

Zynq |trade| Ultrascale+ |trade|

.. list-table::
   :widths: 25 25 25 25
   :header-rows: 1

   * - Vitis AI Release Version
     - DPUCZDX8G IP Version
     - Software Tools Version
     - Linux Kernel Version Tested

   * - v3.5
     - 4.1 (not updated*)
     - Vivado / Vitis / PetaLinux 2023.1
     - 6.1

   * - v3.0
     - 4.1
     - Vivado / Vitis / PetaLinux 2022.2
     - 5.15

   * - v2.5
     - 4.0
     - Vivado / Vitis / PetaLinux 2022.1
     - 5.15

   * - v2.0
     - 3.5
     - Vivado / Vitis / PetaLinux 2021.2
     - 5.10

   * - v1.4
     - 3.3
     - Vivado / Vitis / PetaLinux 2021.1
     - 5.10

   * - v1.3
     - 3.3
     - Vivado / Vitis / PetaLinux 2020.2
     - 5.4

   * - v1.2
     - 3.2
     - Vivado / Vitis / PetaLinux 2020.1
     - 5.4

   * - v1.1
     - 3.2
     - Vivado / Vitis / PetaLinux 2019.2
     - 4.19

   * - v1.0
     - 3.1
     - Vivado / Vitis / PetaLinux 2019.1
     - 4.19

   * - N/A (DNNDK)
     - 3.0
     - Vivado / Vitis / PetaLinux 2019.1
     - 4.19

   * - N/A (DNNDK)
     - 2.0
     - Vivado / Vitis / PetaLinux 2018.2
     - 4.14

   * - First Release (DNNDK)
     - 1.0
     - Vivado / Vitis / PetaLinux 2018.1
     - 4.14

Versal |trade| AI Core

.. list-table::
   :widths: 25 25 25 25
   :header-rows: 1

   * - Vitis AI Release Version
     - DPUCV2DX8G IP Version
     - Software Tools Version
     - Linux Kernel Version Tested

   * - v3.5
     - 1.0
     - Vitis 2022.2
     - 5.15

   * - v3.0
     - Early Access
     - Vitis 2022.2
     - 5.15

.. list-table::
   :widths: 25 25 25 25
   :header-rows: 1

   * - Vitis AI Release Version
     - DPUCVDX8H IP Version
     - Software Tools Version
     - Linux Kernel Version Tested

   * - v3.5
     - 1.3 (not updated*)
     - Vitis 2022.2
     - 5.15

   * - v3.0
     - 1.3
     - Vitis 2022.2
     - 5.15

   * - v2.5
     - 1.2
     - Vitis 2022.1
     - 5.15

   * - v2.0
     - 1.1
     - Vitis 2021.2
     - 5.10

   * - v1.4
     - 1.0
     - Vitis 2021.1
     - 5.10

   * - v1.3
     - Early Access
     - Vitis 2020.2
     - 5.4


Entries marked `not updated` are considered mature IP and do not have a corresponding pre-built board image and reference design.  Extensive compatibility testing will not be done for mature IP for minor (x.5) releases, but will be refreshed with each major (x.0) release.


.. |trade|  unicode:: U+02122 .. TRADEMARK SIGN
   :ltrim:
.. |reg|    unicode:: U+02122 .. TRADEMARK SIGN
   :ltrim:
