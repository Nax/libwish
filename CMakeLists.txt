cmake_minimum_required(VERSION 3.0)
project(libwish)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_C_FALGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -Wextra -fstrict-aliasing")
option(BUILD_SHARED_LIBS "Build shared libs" OFF)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(libwish ${SOURCES})
set_target_properties(libwish PROPERTIES OUTPUT_NAME wish)
target_link_libraries(libwish -lncurses)
include_directories("include")

add_custom_command(
    OUTPUT
    ${CMAKE_SOURCE_DIR}/src/caps.c
    ${CMAKE_SOURCE_DIR}/src/wish_caps.h
    COMMAND
    ruby
    ${CMAKE_SOURCE_DIR}/scripts/gen_caps
    ${CMAKE_SOURCE_DIR}/data/caps.txt
    ${CMAKE_SOURCE_DIR}/src/wish_caps.h
    ${CMAKE_SOURCE_DIR}/src/caps.c
    DEPENDS
    ${CMAKE_SOURCE_DIR}/data/caps.txt
    ${CMAKE_SOURCE_DIR}/scripts/gen_caps
    COMMENT
    "Generating caps code"
    VERBATIM
    )

install(
    TARGETS libwish
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )

install(
    FILES include/wish.h
    DESTINATION include
    )
