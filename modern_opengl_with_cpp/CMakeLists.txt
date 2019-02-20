cmake_minimum_required(VERSION 3.1)
project(modern_opengl)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Set directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# GLFW setup
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

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
        "${SRC_DIR}/${SECTION}/*.cpp"
        # Below for GLSL shaders
        "${SRC_DIR}/${SECTION}/*.vs"
        "${SRC_DIR}/${SECTION}/*.fs"
        "${SRC_DIR}/${SECTION}/*.gs"
    )

    # Recall ${SECTION} target is already set, so executable must have different
    # target name
    set(NAME "${SECTION}.out")
    add_executable(${NAME} ${SOURCE_FILES})
    target_link_libraries(${NAME} ${OPENGL_gl_LIBRARY} glfw)

    if (UNIX AND NOT APPLE)
        set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)
        set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
            ${BIN_DIR}/${SECTION})
    endif()
endforeach()

include_directories(INCLUDE_DIR ${INC_DIR})
