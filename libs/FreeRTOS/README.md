# FreeRTOS
This "library" provides the FreeRTOS kernel that can be added to applications, as well as various add-ons. It uses the latest FreeRTOS kernel from [GitHub mirror](https://github.com/FreeRTOS/FreeRTOS) to take advantage of CMake support.

## Targets
The following targets are exported:

- `embedded-fw-base::FreeRTOS`: FreeRTOS kernel
- `embedded-fw-base::FreeRTOS-CMSIS`: FreeRTOS kernel, but with CMSIS-RTOS2 wrapper API
    - This code has some minor changes on top of what ARM provides; be sure to keep this in mind when updating it.

## Configuration
You _must_ set the `FREERTOS_CONFIG_FILE_DIRECTORY` variable in your project file to define where the FreeRTOS config header file lives.
