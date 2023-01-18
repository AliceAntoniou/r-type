project(demo-uwugine)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE uwugine)

target_include_directories(${PROJECT_NAME}
    PUBLIC include PUBLIC ../include
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
