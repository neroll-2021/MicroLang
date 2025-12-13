cmake_minimum_required(VERSION 3.31)

project(MicroLang VERSION 0.1.0
                  DESCRIPTION "A simple compiler base on LLVM."
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(LLVM_LIBRARIES core support)

add_executable(micc src/main.cpp)
target_include_directories(micc PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(micc PRIVATE ${LLVM_LIBRARIES})

target_compile_options(micc PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
