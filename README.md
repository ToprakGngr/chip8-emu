# CHIP-8 Emulator

![Language](https://img.shields.io/badge/language-C++-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20|%20Windows%20|%20macOS-lightgrey.svg)

A generic, Cycle-accurate CHIP-8 interpreter written in **C++**. This project emulates the classic CHIP-8 system from the 1970s, allowing you to run classic ROMs like Pong, Tetris, and Invaders on modern hardware.

## 📖 Table of Contents
- [About](#-about)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Prerequisites](#-prerequisites)
- [Build Instructions](#-build-instructions)
- [Usage](#-usage)
- [Controls & Keymap](#-controls--keymap)
- [Technical Details](#-technical-details)
- [License](#-license)

## 🧐 About
CHIP-8 is an interpreted programming language, developed by Joseph Weisbecker. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine.

This emulator implements the full instruction set of the original CHIP-8, including graphics rendering, input handling, and sound timers. It is designed with clean C++ architecture, separating the core CPU logic from the platform-specific rendering layer.

## ✨ Features
* **Full Opcode Support**: Implements all standard CHIP-8 opcodes.
* **Graphics**: 64x32 monochrome display rendering.
* **Input**: Hex keypad emulation using the standard QWERTY keyboard layout.
* **Timers**: Functional Delay and Sound timers (60Hz).
* **ROM Loading**: Dynamic loading of binary ROM files.
* **Cross-Platform**: Compatible with Linux, Windows, and macOS (via SDL2/Graphics library).

## 📂 Project Structure
The repository is organized as follows:

```text
chip8-emu/
├── include/        # Header files (.h) defining the Chip8 class and interfaces
├── src/            # Source files (.cpp) containing the implementation logic
├── roms/           # Collection of classic CHIP-8 ROMs (games/demos)
├── .gitignore      # Git ignore rules
└── LICENSE         # MIT License file
```

## 🛠 Prerequisites

To build and run this emulator, you will need:

*   **C++ Compiler**: A modern C++ compiler (e.g., `g++`, `clang++`, or `MSVC`) supporting C++11 or later.
*   **Build System**: Make or CMake (optional but recommended).
*   **Graphics Library**: SDL2 (Simple DirectMedia Layer) development libraries.
    *   *Note: If the project uses a different backend (e.g., Raylib/SFML), ensure those dev libraries are installed.*

### Installing SDL2

**Ubuntu/Debian:**
```bash
sudo apt-get install libsdl2-dev
```

**macOS (Homebrew):**
```bash
brew install sdl2
```

**Windows:**
Download the development libraries from the [SDL website](https://www.libsdl.org/) and link them in your IDE.

## 🔨 Build Instructions

### Method 1: Using g++ (Command Line)

If you do not have a build system set up, you can compile directly from the root directory:

```bash
# Compile source files and link SDL2
g++ src/*.cpp -o chip8-emu -I include -lSDL2

# If specific flags are needed:
g++ -std=c++17 src/*.cpp -o chip8-emu -I include -lSDL2
```

### Method 2: Using CMake (Recommended)

If a `CMakeLists.txt` is present (usually in `src` or root):

```bash
mkdir build
cd build
cmake ..
make
```

## 🚀 Usage

Once built, you can run the emulator by passing the path to a ROM file as an argument.

```bash
./chip8-emu roms/PONG
```

*Replace `roms/PONG` with the path to any `.ch8` file you wish to play.*

## 🎮 Controls & Keymap

The original CHIP-8 used a 16-key hexadecimal keypad. This emulator maps these keys to the left side of your QWERTY keyboard.

| CHIP-8 Keypad | QWERTY Mapping |
| :---: | :---: |
| **1 2 3 C** | **1 2 3 4** |
| **4 5 6 D** | **Q W E R** |
| **7 8 9 E** | **A S D F** |
| **A 0 B F** | **Z X C V** |

*   **Esc**: Exit the emulator.

## 💻 Technical Details

*   **Memory**: 4KB (4096 bytes) of RAM.
    *   `0x000-0x1FF`: Reserved for interpreter.
    *   `0x200-0xFFF`: Program/ROM data space.
*   **Registers**: 16 general-purpose 8-bit registers (V0 - VF), plus a 16-bit Index register (I) and Program Counter (PC).
*   **Stack**: 16-level stack for subroutine calls.
*   **Display**: 64x32 pixels, monochrome.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
