cmake_minimum_required(VERSION 3.0)
project(graphic_interface)

find_package(FLTK)

set(FLTK_INCLUDE_DIR "graphic_calculator/fltk-1.3.9")
set(FLTK_LIBRARY_DIR "graphic_calculator/fltk-1.3.9/lib")

add_executable(graphic_interface_launch launch.cpp)

target_include_directories(graphic_interface_launch PRIVATE ${FLTK_INCLUDE_DIR})

target_link_directories(graphic_interface_launch PRIVATE ${FLTK_LIBRARY_DIR})

target_link_libraries(graphic_interface_launch PRIVATE
        fltk
        fltk_images
        fltk_forms
        fltk_gl
        fltk_jpeg
        fltk_png
        fltk_z
        fltk_vg
        fltk_fontconfig
        fltk_thread
)
