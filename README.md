# group3-embedded

Part of the Group 3 semester project: a management system for Linak motorized desks (distributed system with embedded elements).

Embedded part (Raspberry Pi Pico). Stack: TBD, chosen after the class and sequence diagrams.

Rules for contributing: see [CONTRIBUTING.md](CONTRIBUTING.md).

## Build

Needs `cmake`, `arm-none-eabi-gcc` and the [Pico SDK](https://github.com/raspberrypi/pico-sdk) (2.1.1).

```sh
export PICO_SDK_PATH=/path/to/pico-sdk
cmake -S . -B build && cmake --build build -j
```

Flash: hold BOOTSEL, plug in the Pico, copy `build/desk_pico.uf2` onto the `RPI-RP2` drive.
CI builds the same thing on every PR and uploads the `.uf2`.
