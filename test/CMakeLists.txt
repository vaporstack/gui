cmake_minimum_required(VERSION 3.0)
project(test_gui)
set (test_gui_VERSION_MAJOR 0)
set (test_gui_VERSION_MINOR 0)
set (test_gui_VERSION_PATCH 1)

file(GLOB sources *.c)
message(${sources})

add_executable(test_gui ${sources})
target_include_directories (test_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
target_include_directories (test_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
target_include_directories (test_gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib)
target_link_libraries(test_gui LINK_PUBLIC gui)



