cmake_minimum_required(VERSION 3.14)

project(PixC++ CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

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
  ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(imgui PUBLIC
  OpenGL::GL
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
)

file(GLOB PIXCPP_SOURCES
    src/*.cpp
    src/ui/*.cpp
    src/core/*.cpp
    src/tools/*.cpp
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
  add_executable(PixC++ ${PIXCPP_SOURCES} src/resources.rc)
else()
  add_executable(PixC++ ${PIXCPP_SOURCES})
endif()

target_compile_definitions(
  PixC++ PRIVATE
  $<$<CONFIG:Debug>:Debug>
)

target_include_directories(PixC++ PRIVATE
    src
    src/ui
    src/core
)

target_link_libraries(PixC++ PRIVATE
    imgui
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    OpenGL::GL
)

if(WIN32)
  target_link_libraries(PixC++ PRIVATE
    mingw32
    imm32
    opengl32
  )
  set_target_properties(PixC++ PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(APPLE)
  target_link_libraries(PixC++ PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework OpenGL"
  )
endif()

if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  target_link_libraries(PixC++ PRIVATE
    X11
    GL
    dl
    pthread
  )
endif()
