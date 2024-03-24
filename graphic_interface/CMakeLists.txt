cmake_minimum_required(VERSION 3.0)
project(graphic_interface)
set(CMAKE_CXX_STANDARD 17)

# Path to FLTK
set(FLTK_INCLUDE_DIR "E:/FLTK")
# Path to FLTK lib
set(FLTK_LIBRARY_DIR "E:/FLTK/lib")

add_executable(graphic_interface_launch launch.cpp)

target_include_directories(graphic_interface_launch PRIVATE ${FLTK_INCLUDE_DIR})
target_link_directories(graphic_interface_launch PRIVATE ${FLTK_LIBRARY_DIR})
target_link_libraries(graphic_interface_launch PRIVATE ${FLTK_LIBRARIES})
