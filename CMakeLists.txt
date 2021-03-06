cmake_minimum_required(VERSION 3.0)

macro(use_c99)
	if (CMAKE_VERSION VERSION_LESS "3.1")
		if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
			set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
		endif ()
	else ()
		set (CMAKE_C_STANDARD 99)
	endif ()
endmacro(use_c99)

use_c99()


set(project_name gui)
project(${project_name})

set (${project_name}_VERSION_MAJOR 0)
set (${project_name}_VERSION_MINOR 0)
set (${project_name}_VERSION_PATCH 1)

option(BuildGUILibrary "Build the gui library for embedding or linking" ON)
option(BuildGUITest "BuildTest" ON)
option(BuildGUIDocumentation "BuildDocumentation" OFF)
option(BuildGUIDemo "BuildDemo" OFF)

if(${BuildGUITest})
  add_subdirectory("test")
endif()

if(${BuildGUIDemo})
  add_subdirectory("demo")
endif()

file(GLOB_RECURSE sources gui.c src/*.c)

add_library(gui STATIC ${sources})

target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)
