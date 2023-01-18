project(r-type_client)

set(SOURCES
    src/Game.cpp
    src/Systems.cpp
    src/main.cpp
    src/Components.cpp
    src/Obstacle.cpp
    src/Fire.cpp
    src/Background.cpp
    src/JSONParser.cpp
)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE uwugine)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
    PUBLIC include PUBLIC ../include PUBLIC ../uwugine/include
)

add_compile_options(-g -fsanitize=address)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(EXISTS ${CLANG_TIDY_EXE})
    set(CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        "-extra-arg=-std=c++17"
        "-warnings-as-errors=-*"
        "-header-filter=^.*(?:third-party).*gm")
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
endif()
