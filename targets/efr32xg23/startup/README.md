# EFR32xG23 Initialization
Provides the low level initialization and setup glue for the EFR32xG23 series chips. This consists of the vector table, and C runtime startup code. (It does _not_ set up any of the on-board peripherals.)

This pulls in sources from the Silicon Labs Gecko SDK, specifically for the "device"

## Requirements
Vectors are placed into the `.isr_vector` section, and startup code in the `.startup` section. The linker script must include both of these sections.
