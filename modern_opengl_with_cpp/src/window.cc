// Copyright 2019: Julian Domingo
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "window.h"

Window::Window(GLint w, GLint h) {
    width = w;
    height = h;

    glfwInit();
    glewInit();

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Backwards incompatible for non-core concepts
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Forward compatible
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, 
                                   height, 
                                   "title", 
                                   NULL, 
                                   NULL);

    // Get buffer size (area inside the window, or "viewport")
    GLint bufferWidth, bufferHeight;    
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Setup viewport size (drawable portion of window)
    glViewport(0, 0, bufferWidth, bufferHeight);
 
    // Update OpenGL current context to be newly created window
    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwTerminate();
}

const bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow *Window::GetWindow() const {
    return window;
}

void Window::Refresh() {
    // Clear entire window frame (last param makes clear opaque)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Every pixel in a graphical application has more metadata than just
    // color. For the purpose of clearing the window frame, we clear only
    // the color 
    glClear(GL_COLOR_BUFFER_BIT);

    // OpenGL's implementation of double buffering
    glfwSwapBuffers(window);
}
