## GLEW
* OpenGL extension wrangler
    * Interface for OpenGL versions above 1.1
        * Most modern games use OpenGL 3 or 4
    * Load OpenGL extensions
        * Some are platform specific, but GLEW checks for extension existence
    * Alternatives: GL3W
* #include <GL/glew.h>
    * <GL/wglew.h> for windows
* Initialize OpenGL context, then:
    * glewExperimental = GL_TRUE; /* Modern extensions enabling */
    * glewInit();
    * Error handling => glewGetErrorString(result);
    * Check existence of extension: if (!GLEW_EXT_framebuffer_object){ ... }

## GLFW
* Creates windows and contexts for openGL to interact with
* Pick up and process input from I/O (keyboard, mouse, etc.)
    * Records I/O as events
* Multiple monitor support
* SDL
    * Can do same as GLFW, but also:
        * Audio
        * Threading
        * Filesystems

## Libs
* glew
* glfw-wayland
* visual-studio-code-bin
    * Run "code" in terminal to start a vscode instance
*
