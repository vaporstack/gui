cmake_minimum_required(VERSION 3.0)

use_c99()

project(gui)

set(project_name gui)

set (gui_VERSION_MAJOR 0)
set (gui_VERSION_MINOR 0)
set (gui_VERSION_PATCH 1)

option(BuildLibrary "Build the gui library for embedding or linking" ON)
option(BuildTest "BuildTest" ON)
option(BuildDocumentation "BuildDocumentation" OFF)

if(${BuildTest})
  add_subdirectory("test")
endif()

file(GLOB_RECURSE sources gui.c src/*.c)

add_library(gui STATIC ${sources})

target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)
