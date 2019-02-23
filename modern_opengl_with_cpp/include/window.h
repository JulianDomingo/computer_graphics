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
//
// -----------------------------------------------------------------------------
// File: window.h
// -----------------------------------------------------------------------------
//
// This header file provides the data and functions for the Window class,
// encapsulating usage of the GLFWwindow type.
//

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;
    GLint width;
    GLint height;

public:
    Window(GLint width, GLint height);
    ~Window();
    const bool ShouldClose();

    // "const" at the end of a function declaration guarantees returned object
    // state will not change.
    GLFWwindow *GetWindow() const;

    void Refresh();
};

#endif  // _WINDOW_H_
