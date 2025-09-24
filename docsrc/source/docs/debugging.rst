Debugging VART-X and VART-ML Based Apps
==================================================

The VART interface and x_plus_ml type apps offer extensive debugging features to help you identify and resolve errors. You can enable or disable debugging with command-line options or environment variables at different levels of the framework, giving flexible and controlled debugging.

Command Line Debugging in x_plus_ml Type Apps
----------------------------------------------

Activate or deactivate application-level debugging by command line option ``--log-level`` for x_plus_ml apps at runtime. This provides granular control of log levels for specific application runs. Each level includes logs at that level and all lower levels.

The available log levels are:

1. ERROR
2. WARNING
3. INFERENCE RESULT
4. FIXME
5. INFO
6. DEBUG

Example command with log level 6 (DEBUG and below):

.. code-block:: bash

   $ x_plus_ml_ort/x_plus_ml_vart --input-file <path_to_test_jpeg_image> --app-config <path to json config> --log-level 6
   $ spatial_mt_ml_ort/temporal_ml_ort --input-dir <dir_path_to_jpeg_images> --app-config <path to json config> --log-level 6

Framework-Level Debugging with VART and VVAS CORE
-------------------------------------------------

For more detailed debugging of framework-level processes, enable logs within the VART and VVAS CORE interfaces. This is useful for understanding internal flow and pinpointing deeper issues.

Enabling VART Logs
~~~~~~~~~~~~~~~~~~

Set the following environment variables before launching the application:

.. code-block:: bash

   $ export VART_LOG_FILE_PATH=CONSOLE
   $ export VART_CORE_DEBUG_ENV=5

This displays VART logs on the console at DEBUG level.

Enabling VVAS CORE Logs
~~~~~~~~~~~~~~~~~~~~~~~

To enable logs for the VVAS CORE framework, set these environment variables:

.. code-block:: bash

   $ export VVAS_CORE_LOG_FILE_PATH=CONSOLE
   $ export VVAS_CORE_DEBUG=4 # 4 is for INFO level verbosity

Adjust the VVAS_CORE_DEBUG level to control verbosity:

0. NONE
1. ERROR
2. WARNING
3. FIXME
4. INFO
5. DEBUG

Logs print on the console and offer detailed insights into the VVAS CORE framework.

Redirecting VART and VVAS Logs to a File
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Besides displaying logs on the console, you can redirect VART and VVAS CORE logs to a file for easier analysis and persistent logging. Set specific environment variables to a file path to achieve this.

Example:

To save VART logs to a file, specify the VART_CORE_LOG_FILE_PATH environment variable:

.. code-block:: bash

   $ export VART_CORE_LOG_FILE_PATH=/tmp/vart_logs.txt
   $ export VART_CORE_DEBUG_ENV=5

This configuration writes all VART logs at the specified log level (and below) to ``/tmp/vart_logs.txt``. Use these features to effectively debug and optimize your applications with the VART interface.

Capturing Logs from Vitis AI Execution Provider
-----------------------------------------------

To capture logs from the Vitis AI Execution Provider, please set the logging level in ``vitisai_config.json``.

Example vitisai_config Json:

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
         "vaiml_config": {
           "device": "ve2",
           "optimize_level": 2,
           "logging_level": "info",   -------> set logging info.
           "threshold_gops_percent": 20
         }
       }
     ]
   }

``logging_level``

- Type: String
- Supported values: “info”, “error”, “warning”
- Default: “error”

Vitis AI Logging Level
~~~~~~~~~~~~~~~~~~~~~~

- **Info**: Provides details about significant events or actions, including additional comparative information between options.
- **Warning**: Indicates recoverable issues have occurred, with possible additional warnings highlighting differences between options.
- **Error**: Reports critical failures that prevent program continuation; limited error details are displayed.

``vitis_ai_config.json`` can be used for ``ml_ort``, ``temporal_ml_ort`` and ``spatial_mt_ml_ort``.

Enabling VART-ML Logs in x_plus_ml_vart
----------------------------------------

To enable VART-ML log in ``x_plus_ml_vart``, edit ``inference-config.runner-options.log-level``.

Available logging options are:

- "ERROR"
- "WARNING"
- "INFO"
- "DEBUG"

Refer to `Inference Configuration JSON Guide <https://gitenterprise.xilinx.com/IPS-SSW/Vitis-AI-Telluride/tree/main/examples/cpp_examples/x_plus_ml_vart/json_configs>`_ for more info.
