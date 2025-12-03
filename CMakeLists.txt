cmake_minimum_required(VERSION 3.14)

project(PixC++ CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
message(STATUS "Downloading ImGUI...")
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.92.5
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

add_executable(PixC++ main.cpp)

target_link_libraries(PixC++ PRIVATE
  imgui
)

if(WIN32)
  set_target_properties(PixC++ PROPERTIES WIN32_EXECUTABLE TRUE)
  target_link_libraries(PixC++ PRIVATE
    mingw32
    opengl32
    imm32
  )
endif()
