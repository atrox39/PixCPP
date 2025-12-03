# PixC++

A pixel art editor built with C++, ImGui, SDL2, and OpenGL. PixC++ provides a lightweight and efficient environment for creating and editing pixel art with a modern GUI interface.

## Features

- **Canvas System**: Customizable pixel canvas with resize and clear functionality
- **Modern UI**: Built with Dear ImGui for a responsive and intuitive interface
- **OpenGL Rendering**: Hardware-accelerated graphics rendering
- **Cross-platform**: Works on macOS, Linux, and Windows

## Requirements

- **C++17** or higher
- **CMake 3.14** or higher
- **SDL2**
- **OpenGL**
- **Dear ImGui** (automatically fetched via CMake)

## Dependencies Installation

### macOS
```bash
brew install sdl2 cmake
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsdl2-dev cmake build-essential
```

### Linux (Fedora)
```bash
sudo dnf install SDL2-devel cmake gcc-c++
```

## Building

1. Clone the repository:
```bash
git clone https://github.com/atrox39/PixCPP.git
cd PixCPP
```

2. Create a build directory and compile:
```bash
mkdir -p build
cd build
cmake ..
make
```

3. Run the application:
```bash
./PixC++
```

## Project Structure

```
PixCPP/
├── CMakeLists.txt          # CMake configuration
├── src/
│   ├── main.cpp            # Application entry point
│   ├── App.cpp/.hpp        # Main application class
│   ├── core/
│   │   ├── MenuBar.cpp/.hpp    # Menu bar UI components
│   │   └── Windows.cpp/.hpp    # Window management
│   └── ui/
│       ├── Canvas.cpp/.hpp         # Canvas data structure
│       ├── CanvasWindow.cpp/.hpp   # Canvas rendering window
│       └── EditorState.cpp/.hpp    # Editor state management
└── build/                  # Build artifacts (generated)
```

## Architecture

- **App**: Core application class managing SDL2 window, OpenGL context, and main loop
- **Canvas**: Pixel data storage and manipulation using a 32-bit RGBA format
- **UI Components**: ImGui-based interface for canvas editing and tool management
- **Core Systems**: Menu bar and window management for the editor interface

## Development

The project uses CMake for build configuration and automatically fetches Dear ImGui from the docking branch. The build system generates `compile_commands.json` for enhanced IDE support.

### Build Configuration

- C++ Standard: C++17
- ImGui Branch: docking (for advanced windowing features)
- Backends: SDL2 + OpenGL3

## License

[Add your license information here]

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## Author

[atrox39](https://github.com/atrox39)
