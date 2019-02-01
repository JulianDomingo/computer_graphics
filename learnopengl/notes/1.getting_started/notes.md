# 1. Getting Started

## OpenGL Overview
### Extensions
* When large optimization for rendering is released by a graphics card company,
    can enable it through the extension name. As a result, these new rendering
    techniques can be used without having to wait for OpenGL to include the
    functionality in a future version.

### State Machine
* OpenGL is a large state machine - collection of variables defining how OpenGL
    should operate.
* Current state is the **context**. Context is often changed when we want to
    (for example) draw lines instead of triangles.

## Objects
* Collection of options representing a subset of OpenGL's state
    * I.e. object representing settings of the drawing window (size, color
        supports, etc.)
* As soon as objects are populated with their **"options"**, context target is set back to default.

## Creating a Window
### GLFW
