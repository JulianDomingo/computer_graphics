#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

int main(int argc, char *argv[])
{
    if (!glfwInit()) {
        printf("opengl: failed to init!");
        glfwTerminate();
        return 1;
    }

    // Allow modern extension features
    glewExperimental = GL_TRUE;
    
    // OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Backwards incompatible for non-core concepts
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Forward compatible
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "section_1", NULL, NULL);

    if (!mainWindow) {
        glfwTerminate();
        return 1;
    }

    // Get buffer size (area inside the window, or "viewport")
    GLint bufferWidth, bufferHeight;    
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set OpenGL context to tie to mainWindow
    glfwMakeContextCurrent(mainWindow);

    if (glewInit() != GLEW_OK) {
        printf("glew: failed to init!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Setup viewport size (drawable portion of window)
    glViewport(0, 0, bufferWidth, bufferHeight);

    while (!glfwWindowShouldClose(mainWindow)) {
        // Obtain + handle user input events
        glfwPollEvents();

        // Clear entire window frame (last param makes clear opaque)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        // Every pixel in a graphical application has more metadata than just
        // color. For the purpose of clearing the window frame, we clear only
        // the color 
        glClear(GL_COLOR_BUFFER_BIT);

        // Double buffering
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}
