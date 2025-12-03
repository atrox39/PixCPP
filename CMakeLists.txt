cmake_minimum_required(VERSION 3.14)

project(PixC++ CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------------------------
# Opcional: exportar compile_commands.json para VSCode
# --------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------------------------
# SDL2
# --------------------------------------------------------------------
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# --------------------------------------------------------------------
# OpenGL
# --------------------------------------------------------------------
find_package(OpenGL REQUIRED)

# --------------------------------------------------------------------
# Dear ImGui
# --------------------------------------------------------------------
include(FetchContent)
message(STATUS "Downloading ImGUI...")

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG docking
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(imgui PUBLIC
  OpenGL::GL
  ${SDL2_LIBRARIES}
)

# --------------------------------------------------------------------
# Archivos del proyecto PixC++
# --------------------------------------------------------------------
file(GLOB PIXCPP_SOURCES
    src/*.cpp
    src/ui/*.cpp
    src/core/*.cpp
)

add_executable(PixC++ ${PIXCPP_SOURCES})

target_include_directories(PixC++ PRIVATE
    src
    src/ui
    src/core
)

target_link_libraries(PixC++ PRIVATE
    imgui
    ${SDL2_LIBRARIES}
    OpenGL::GL
)

# --------------------------------------------------------------------
# Platform-specific libraries
# --------------------------------------------------------------------

# Windows (MinGW/MSVC)
if(WIN32)
  target_link_libraries(PixC++ PRIVATE
    mingw32
    imm32
    opengl32
  )
  set_target_properties(PixC++ PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# macOS
if(APPLE)
  target_link_libraries(PixC++ PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework OpenGL"
  )
endif()

# Linux
if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  target_link_libraries(PixC++ PRIVATE
    X11
    GL
    dl
    pthread
  )
endif()
