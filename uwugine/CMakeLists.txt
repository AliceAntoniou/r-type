project(uwugine)

set(SOURCES
    src/Segment.cpp
    src/Exception.cpp
    src/Client.cpp
    src/Texture.cpp
    src/Clock.cpp
    src/Polygone.cpp
    src/Registery.cpp
    src/Sprite.cpp
    src/Point.cpp
    src/Text.cpp
    src/Window.cpp
    src/Hitbox.cpp
    src/Systems.cpp
    src/Sound.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
)

add_compile_options(-g -fsanitize=address)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

if(EXISTS ${CLANG_TIDY_EXE})
     set(CLANG_TIDY
     "${CLANG_TIDY_EXE}"
     "-extra-arg=-std=c++17"
     "-warnings-as-errors=-*"
     "-header-filter=^.*(?:third-party).*gm")
     set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
