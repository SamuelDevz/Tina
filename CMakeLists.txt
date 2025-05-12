cmake_minimum_required(VERSION 3.5...3.28)
project(Tina3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build the shared library" OFF)
option(BUILD_EXAMPLES "Build examples programs" ON)

add_subdirectory(src)

add_library(Tina-Libraries INTERFACE)
add_library(Tina::Libraries ALIAS Tina-Libraries)
target_link_libraries(Tina-Libraries INTERFACE window)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()