#include <GLFW/glfw3.h>

int main(int argc, char const *argv[])
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(600, 600, "Hello OpenGL!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        glBegin(GL_TRIANGLES);

        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);

        glEnd();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    return 0;
}