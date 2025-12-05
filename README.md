# PixC++

PixC++ is a lightweight pixel-art editor built with C++, Dear ImGui, SDL2, and OpenGL. It focuses on fast iteration, a responsive UI, and essentials for creating and previewing pixel-perfect sprites.

## Overview

The editor pairs a zoomable checkerboard canvas with a streamlined toolset (brush, eraser, line, and eyedropper) and keyboard shortcuts for quick switching. Assets are copied into the build output so you can run the application directly after compilation on Windows, macOS, or Linux.

## Key Features

- Pixel-perfect drawing with brush, eraser, line, and eyedropper tools (B, E, I shortcuts)
- Scroll-wheel canvas zoom with live checkerboard compositing
- Right-click color picking that keeps alpha information intact
- PNG export with alpha transparency via `stb_image_write`
- Dear ImGui–based menu bar and docking layout for a modern workflow

## Tech Stack

- C++17, CMake, and modern CMake workflows
- SDL2 + SDL2_image for windowing, input, and texture upload
- OpenGL 3 renderer driven through Dear ImGui backends
- Dear ImGui (docking branch) for the UI layer
- `stb_image_write` for on-disk PNG output

## Prerequisites

Install a C++17-capable toolchain, CMake ≥ 3.14, and development packages for SDL2, SDL2_image, and OpenGL on your platform.

### Windows

- Install Visual Studio 2019 (or newer) with the Desktop development with C++ workload, or use clang-cl/MinGW.
- Acquire SDL2 and SDL2_image development libraries (e.g., `vcpkg install sdl2 sdl2-image` and pass your `vcpkg` toolchain file to CMake).
- Ensure the OpenGL SDK is available (included with the Windows SDK / Visual Studio).

### macOS

```bash
brew install cmake sdl2 sdl2_image
```

### Ubuntu / Debian

```bash
sudo apt-get install cmake build-essential libsdl2-dev libsdl2-image-dev
```

### Fedora

```bash
sudo dnf install cmake gcc-c++ SDL2-devel SDL2_image-devel
```

## Build From Source

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

On multi-configuration generators (Visual Studio, Xcode) specify the configuration explicitly:

```powershell
cmake --build build --config Release
```

> CMake copies the `assets/` directory into the build tree so textures and icons resolve at runtime without extra steps.

## Run

- Unix-like: `./build/PixC++`
- Windows (Visual Studio): `.build\Release\PixC++.exe` or `.build\Debug\PixC++.exe`

## Usage Notes

- Scroll to zoom; the view clamps between 4× and 64× magnification.
- Press `B`, `E`, or `I` to switch between brush, eraser, and eyedropper tools.
- Right-click with the brush or eyedropper to sample the pixel under the cursor.
- The line tool previews the stroke before committing; press `Esc` to cancel.
- The File → Save action writes a `PNG` named `output.png` in the working directory.

## Project Layout

```
PixCPP/
|-- CMakeLists.txt
|-- assets/
|   `-- icons/
|-- src/
|   |-- App.cpp/.hpp
|   |-- main.cpp
|   |-- core/
|   |   |-- MenuBar.cpp/.hpp
|   |   `-- Windows.cpp/.hpp
|   |-- tools/
|   |   |-- TextureManager.cpp/.hpp
|   |   `-- Tools.cpp/.hpp
|   |-- ui/
|   |   |-- Canvas.cpp/.hpp
|   |   |-- CanvasRender.cpp/.hpp
|   |   `-- CanvasWindow.cpp/.hpp
|   |-- utils/
|   |   |-- ImageIO.cpp/.hpp
|   |-- stb/
        `--stb_image_write.h
`-- build/
	`-- ... (generated artifacts)
```

## Contributing

Bug reports, feature requests, and pull requests are welcome. Please open an issue describing your changes or ideas before large overhauls.

## Acknowledgements

- [Dear ImGui](https://github.com/ocornut/imgui)
- [SDL2](https://www.libsdl.org/) and [SDL2_image](https://github.com/libsdl-org/SDL_image)
- [stb_image_write.h](https://github.com/nothings/stb)
