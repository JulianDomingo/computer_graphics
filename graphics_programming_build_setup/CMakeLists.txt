cmake_minimum_required(VERSION 3.1)
project(open_gl_setup_tutorial)

# Define location of all subdirectories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Separate executables to a bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

include_directories(INCLUDE_DIR ${INC_DIR})

# TODO: For multiple subdirectories within source dir, write CMakeLists in such
# a way to generate binaries for all subprojects, if applicable
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES})

# GLFW
# Suppress CMP0072 warning (unset OpenGL_GL_PREFERENCE for cmake version > 3.11)
set(OpenGL_GL_PREFERENCE GLVND)
# If GLFW binaries installed on local machine
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
# OPENGL_gl_LIBRARY becomes set if glfw3 package was found through
# find_package()
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glfw)

# glad
# Compile the glad source file "glad.c" using the existing library in our
# include directory, named "glad".
add_library("glad" "${SRC_DIR}/glad.c")
# Specify the location of the "glad" directory, housing the header files.
target_include_directories("glad" PRIVATE ${INCLUDE_DIR})
# TODO: explain what CMAKE_DL_LIBS does
target_link_libraries(${PROJECT_NAME} "glad" ${CMAKE_DL_LIBS})
