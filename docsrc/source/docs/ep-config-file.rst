Vitis AI EP Configuration File
==============================

When creating the ORT inference session with the Vitis AI EP, it is necessary to provide a configuration file through the ``config_file`` provider option. This file is commonly referred to as the ``vitisai_config.json`` file, but it can be given any name.

By default, the ``vitisai_config.json`` file should contain the following:

.. code-block:: json

    {
      "passes": [
       {
         "name": "init",
         "plugin": "vaip-pass_init"
       },
       {
        "name": "vaiml_partition",
        "plugin": "vaip-pass_vaiml_partition",
        "vaiml_config":
        {
          "device": "ve2",
          "optimize_level": 2,
          "logging_level": "info",
          "threshold_gops_percent": 20
        }
       }
      ],
      "target": "VAIML",
      "targets": [
        {
            "name": "VAIML",
            "pass": [
                "init",
                "vaiml_partition"
            ]
        }
      ]
    }

Additional options can be specified in the ``vaiml_config`` section of the configuration file, as described below.

optimize_level
~~~~~~~~~~~~~~

Controls the optimization level.

- **Type:** Integer
- **Supported values:** 1, 2, 3
- **Default:** 1

The optimization level can be changed as follows:

.. code-block:: json

    "vaiml_config": {
      "optimize_level": 2
    }

preferred_data_storage
~~~~~~~~~~~~~~~~~~~~~~

Controls whether intermediate data is stored in vectorized or unvectorized format. Models dominated by convolutions (e.g., CNNs) perform better with vectorized data. Models dominated by GEMMs (e.g., Transformers) perform better with unvectorized data. When the ``auto`` mode is selected, the compiler tries to select the best layout.

- **Type:** String
- **Supported values:** "vectorized", "unvectorized", "auto"
- **Default:** "auto"

The data storage format can be changed as follows:

.. code-block:: json

    "vaiml_config": {
      "preferred_data_storage": "unvectorized"
    }

threshold_gops_percent
~~~~~~~~~~~~~~~~~~~~~~

An option that directs high-GOPS(Giga Operations Per Second) operators to the NPU and low-GOPS operators to the CPU, based on a set performance threshold.

logging_level
~~~~~~~~~~~~~

- **Type:** String
- **Supported values:** "info", "error", "warning"
- **Default:** "error"

Vitis AI logging level

**Info:** Provides details about significant events or actions, including additional comparative information between options.
**Warning:** Indicates recoverable issues have occurred, with possible additional warnings highlighting differences between options.
**Error:** Reports critical failures that prevent program continuation; limited error details are displayed.
