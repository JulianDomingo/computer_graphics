cmake_minimum_required(VERSION 3.1)
project(modern_opengl)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(WS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/workspace")
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")

# Set directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# OpenGL setup
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# GLFW setup
# Steps taken from
# https://www.glfw.org/docs/3.0/build.html#build_link_cmake_pkgconfig. Assumes
# binaries have been installed on local machine (more portable than linking from
# source)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# GLEW setup
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
add_definitions(${GLEW_DEFINITIONS})

# Set variable for each section (for executable generation)
set(SECTIONS
    section_1
    section_2
    section_3
    section_4
    section_5)

# Group together files dependent for all sections
file(GLOB DEFAULT_DEPENDENCIES
    "${SRC_DIR}/*.cc"
    "${INC_DIR}/*.h"
    # Below for GLSL shaders
    "${SHADER_DIR}/${SECTION}/*.vs"
    "${SHADER_DIR}/${SECTION}/*.fs"
    "${SHADER_DIR}/${SECTION}/*.gs"
    )

# Make executable for each section using dependent files
foreach(SECTION ${SECTIONS})
    # Specify files from current section
    file(GLOB SECTION_DEPENDENCIES "${WS_DIR}/${SECTION}/*.cc")

    # Recall ${SECTION} target is already set, so executable must have different
    # target name
    set(NAME "${SECTION}.out")

    # Create executable
    add_executable(${NAME} ${SECTION_DEPENDENCIES} ${DEFAULT_DEPENDENCIES})

    # Links shared library version of GLFW and OpenGL to executable
    target_link_libraries(${NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

    if (UNIX AND NOT APPLE)
        # Explictly tells CMake project supports C++
        set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)
        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${BIN_DIR}/${SECTION})
    elseif (APPLE)
        # TODO:
    elseif (WIN32)
        # TODO:
    endif()

endforeach()

include_directories(INCLUDE_DIR ${INC_DIR})
