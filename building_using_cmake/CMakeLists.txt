# Below is a template for projects using OpenGL / GLFW / GLEW to build
# successfully on a linux platform.
# Each command is prefaced with a tidbit on the command's purpose.
# TODO: Update to make platform-independent

#
cmake_minimum_required(VERSION 3.1)

# Sets the projct name. Once set, it can alternatively be accessed using
# ${PROJECT_NAME}.
project(modern_opengl)

# set() binds argument 1 to all subsequent argument(s).
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Set directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# OpenGL setup

# "GLVND" allows compatibility for legacy libraries in OpenGL. Present in CMake
# versions >= 3.11.
set(OpenGL_GL_PREFERENCE GLVND)
# Find OpenGL
find_package(OpenGL REQUIRED)
# Once package is found, include all of OpenGL's headers.
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

# Make executable for each section
foreach(SECTION ${SECTIONS})
    file(GLOB SOURCE_FILES
        "${SRC_DIR}/${SECTION}/*.h"
        "${SRC_DIR}/${SECTION}/*.cc"
        # Below for GLSL shaders
        "${SRC_DIR}/${SECTION}/*.vs"
        "${SRC_DIR}/${SECTION}/*.fs"
        "${SRC_DIR}/${SECTION}/*.gs"
    )

    # Recall ${SECTION} target is already set, so executable must have different
    # target name
    set(NAME "${SECTION}.out")
    # Creates executable file with files dictated by current ${SOURCE_FILES}
    add_executable(${NAME} ${SOURCE_FILES})

    # Links shared library version of GLFW and OpenGL to executable
    target_link_libraries(${NAME} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})

    if (UNIX AND NOT APPLE)
        # Explictly tells CMake project supports C++
        set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)
        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${BIN_DIR}/${SECTION})
    endif()
endforeach()

include_directories(INCLUDE_DIR ${INC_DIR})
