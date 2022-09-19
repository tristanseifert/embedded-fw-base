# Silicon Labs EFR32xG23 Target
Provides support for the EFR32xG23 chipset.

## Requirements
The toolchain used to build this code must support the [ARM CMSE](https://developer.arm.com/documentation/100720/0200/CMSE-support) extensions.

Additionally, you _must_ specify the `EFWB_GECKO_CONFIG_DIR` variable in your firmware project to the full path to a directory that contains the SDK configuration headers. (These headers can be copied from the `config` directory in the root of a Simplicity Studio project's source tree.)
