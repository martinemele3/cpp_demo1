# demo2 — NUCLEO-G474RE user LED

This firmware blinks the board's software-controlled user LED, LD2 (green),
on PA5, with a 100 ms on/off interval. The board's B1 button (PC13) toggles
blinking on and off; blinking starts enabled after reset.

## About LD1

LD1 is the ST-LINK COM-status indicator, not an MCU-controlled user LED.
The ST-LINK controls its red/green status indication, so application firmware
cannot make LD1 blink on demand. The board's power LED is LD3; the user LED
available to this demo is LD2, which is green.

## Build on Windows

Install CMake, Ninja, and the ARM GNU Toolchain (`arm-none-eabi-gcc` and
`arm-none-eabi-objcopy`), and make sure they are available on `PATH`. From the
repository root, run:

```powershell
cmake -S .\demo2 -B .\demo2\build -G Ninja --toolchain .\demo2\cmake\arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\demo2\build
```

The build produces `demo2\build\demo2.bin`.

## Program the board

1. Connect the NUCLEO-G474RE over USB and confirm that its `NOD_G474RE` drive
   is mounted (in this setup it is `F:`).
2. Copy `demo2\build\demo2.bin` to the root of that drive.
3. Wait for the copy to finish and the board to reset, then observe LD2.

The drive letter can change; use the drive labeled `NOD_G474RE` if it is not
mounted as `F:`.

## Python virtual environment

An optional Python virtual environment is available in `.venv`. Activate it
from the repository root in PowerShell with:

```powershell
.\demo2\.venv\Scripts\Activate.ps1
```

This firmware has no Python dependencies; the virtual environment is separate
from the ARM GNU Toolchain required to build it.
