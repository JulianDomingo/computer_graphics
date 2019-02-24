# Shaders and the Rendering Pipeline

## Overview
* Operations are passed to the GPU, which performs a set series of operations
    to ultimately **render an image to the screen.** This is often referred to 
    as the graphics / rendering pipeline
* Shaders are one part of the rendering pipeline. **4** stages are programmable
    by shaders.
    * Specifically, shaders are pieces of code written in **GLSL** (OpenGL
        shading language) or **HLSL** (high-level shading language) for Direct3D
        users.
    * GLSL is based on **C** programming language
        * Vertex shader: **.vs**
        * Fragment shader: **.fs**
        * Geometry shader: **.gs**
        * Tessellation shader: **.ts**

## Rendering Pipeline Stages
1. Vertex specification
2. Vertex shader (programmable)
3. Tessellation (programmable)
4. Geometry Shader (programmable)
5. Vertex Post-Processing
6. Primitive Assembly
7. Rasterization
8. Fragment Shader (programmable)
9. Per-Sample Operations

### Vertex Specification
* A **primitive** is a shape defined using 1+ vertices
* Sets up data of the vertices for the primitives to render
* Done in the application
* Uses **VAO**s (vertex array objects) and **VBO**s (vertex buffer objects)
    * VAO defines WHAT data a vertex has (i.e. position, color, etc.)
    * VBO holds the data values
* Attribute pointers define where and how shaders can access vertex data
* VAO / VBOs stored in RAM of GPU because it's quicker, as opposed to querying needed data from CPU and moving them from RAM to GPU.

#### Creating VAO/VBO
1. Generate VAO ID
2. Bind VAO with ID
3. Generate VBO ID
4. Bind VBO with ID
5. Attach vertex data to VBO
6. Define attribute pointer formatting
7. Enable attribute pointer
8. Unbind VAO + VBO, get ready for next object to bind

* A single VAO contains many VBOs.

### Initiating Draw
1. Activate shader program you want to use
    * All shader files within project are compiled into a separate "shader
        program."
2. Bind VAO of object you want to draw. Whichever VAO is currently bounded is
   the object which is drawn.
3. Call `glDrawArrays` which initiates the rest of the pipeline

### Vertex Shader
* Handles vertices individually
* Vertex shader is **NOT** optional
* Must store something in `gl_Position` since it's used in later stages
* Can specify additional outputs pickable and usable by user-defined shaders in
    later stages
* Inputs consist of vertex data values
* Example .vs (vertex shader):

```
#version <MAJOR><MINOR><RELEASE> core

# "layout" is optional. Explicitly defines shader location to avoid needing
# to query it in application code.
layout (location = 0)

# Input is a vector consisting of 3 values named "pos"
in vec3 pos;

void main()
{
    # gl_Position is final position of vertex. Requires a vector of 4
    values. Below just adds 1.0 for last value.
    gl_Position = vec4(pos, 1.0);
}
```

### Tessellation
* Allows division of data into smaller primitives (i.e. quad -> triangle). Good
    for rendering detail
* Commonly used in things like water movement

### Geometry Shader
* Vertex handle handles vertices, geometry shader handles **primitives**, which
    are **groups of vertices** (i.e. triangle).
* Takes primitives and "emits" their vertices to create the given primitive, or
    new / modified primitives.
* Can alter primitive types, or create new ones

### Vertex Post-Processing
1. Transformation Feedback (if enabled):
    * Result of vertex and geometry stages saved to buffers for later use if
        these stages are used **repeatedly**. Advanced concept used for
        rendering optimization.
2. Clipping:
    * Primitives that won't be visiable are removed (don't draw things we can't
        see)
    * Positions converted from "clip-space" to "window space"

### Primitive Assembly
* Vertices are converted into a series of primitives
* I.e. 6 vertices could become 2 triangles, if rendering triangles
* Face culling - removal of primitives that can't be seen, or are facing "away"
    from the viewer.
    * I.e. remove inner sides of a box. Recall in games where you pass through a
        wall and look back, noticing the wall you passed through was invisible

### Rasterization
* Converts primitives into **fragments**
* Fragments are pieces of data for each pixel, obtained from rasterization
    process
    * I.e. depth, color, other metadata
* Fragment dat will be **interpolated** based on its position relative to each
    vertex

### Fragment Shader
* Handles data for each fragment
* Optional, but rare to NOT use it. Exceptions include cases where only depth or
    stencil data is required (i.e. shadow maps)
* Most important output is pixel color the fragment covers
* Simplest OpenGL programs usually have a vertex and fragment shader
* Example .fs (fragment shader):

```
#version 330

# Can also capture output from vertex shader using "in" keyword
# Output is vector of 4 values named "color"
out vec4 color;

void main()
{
    # No matter where we are, this fragment is red. (R, G, B, ?)
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
```

### Per-Sample Operations
* Series of tests run to see if the fragment should be drawn
* Most important test: **depth test**. Determines if something is in front of
    the point being drawn
    * I.e. drawing 2 triangles. First has already been drawn, second is
        currently being drawn behind the first triangle - no point in drawing
        fragments that would be covered by the first triangle
* Color blending: using defined operations, fragment colors are blended together
    with overlapping fragments. Used primarily for transparent objects
* Fragment data written to currently bound `Framebuffer` (usually default
    Framebuffer). `Framebuffer` is the Framebuffer behind the current drawn Framebuffer for
    double buffering.
* Finally, in the application code, the user usually defines a Framebuffer swap,
    putting the newly updated Framebuffer to the front (make it the currently
    drawn Framebuffer).
    * Can do some clever things with 3+ Framebuffers, like a CCTV effect in a game.
        There'd be a 3rd Framebuffer which won't be swapped into the main Framebuffer, but
        is filled out and converted to a texture, then sent to the main Framebuffer
        to draw it onto a TV screen!

### Other
* Shader programs are usually a group of vertex, tessellation, geometry,
    fragment, etc. shaders **associated with one another**.
    * Created in OpenGL with a series of functions

## Creating a Shader Program
1. Create empty program
2. Create empty shaders
3. Attach shader source code to shaders
4. Compile shaders
5. Attach shaders to program
6. Link program (creates executables from shaders and links them together)
7. Validate program (optional, but highly advised for mitigating shader debug
   time)

## Using a Shader Program
* When creating a shader, ID is given (like VAO / VBOs)
* With given ID, call `glUseProgram(shaderID)`
* All draw calls from then on will use that shader until a new shader ID is
    passed, or `glUseProgram(0)` is called, which means "no shader."

## Summary
* Vertices -> vertex shader
* Primitives -> geometry shader
* Fragments -> fragment shader
