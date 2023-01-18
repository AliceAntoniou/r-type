cmake_minimum_required(VERSION 3.0.0)
project(rtype VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)

set_target_properties(sfml-system PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-audio PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-window PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
set_target_properties(sfml-graphics PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

set_target_properties(sfml-system PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:sfml-system,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(sfml-audio PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:sfml-audio,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(sfml-window PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:sfml-window,INTERFACE_INCLUDE_DIRECTORIES>)
set_target_properties(sfml-graphics PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:sfml-graphics,INTERFACE_INCLUDE_DIRECTORIES>)

add_compile_options(-g)

add_subdirectory(uwugine)
add_subdirectory(game)
add_subdirectory(uwugine/demo)
