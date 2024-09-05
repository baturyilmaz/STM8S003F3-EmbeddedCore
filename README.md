# STM8S003F3-EmbeddedCore

A basic C library for STM8S003F3 microcontrollers.

## Current Features

- UART communication
- ADC operations
- Timer functions
- GPIO control
- Basic system management

## Upcoming Features

More peripherals and functions will be added.

## Usage

Include the necessary header files in your project and call the initialization functions for the peripherals you want to use. 

Example:

```c
#include "uart.h"
#include "adc.h"

void main() {
    UART_Init(UART_1, 9600);
    AY_ADC_Init_Single();
    
    // Your code here
}
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Disclaimer

This is a work in progress. Use at your own risk in production environments.