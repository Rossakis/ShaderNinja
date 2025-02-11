# Shader Ninja - Documentation

# Project Documentation

This document provides an overview of the classes and their functionalities in the project. Each section describes a class and its potential responsibilities.

---

## Contents
0. [Building and Linking](../README.md)
1. [High-Level Interface](#high-level-interface)
   1. [BufferManager](#buffermanager)
   2. [InputManager](#inputmanager)
   3. [TimeManager](#timemanager)
   4. [ImguiManager](#imguimanager)
   5. [Material](#material)
   6. [Mesh](#mesh)
   7. [OBJModelImporter](#objmodelimporter)
   8. [Primitive](#primitive)
   9. [Shader](#shader)
   10. [ShaderManager](#shadermanager)
   11. [Texture](#texture)
   12. [Camera](#camera)
   13. [ScreenUtils](#screenutils)
   14. [Utils](#utils)
2. [System](#system)
3. [Graphics](#graphics)
4. [Input](#input)
5. [Time Management](#time-management)
6. [GUI](#gui)

---

## Building and Linking
This section will describe how to build and link the project, including dependencies and setup instructions.

---

## High-Level Interface
The high-level interface consists of classes that manage core functionalities such as buffer management, input handling, time management, GUI integration, and more.

### BufferManager
[[Header]](../src/Core/BufferManager.h) [[Cpp]](../src/Core/BufferManager.cpp)
Manages OpenGL buffer objects, including vertex arrays (VAOs) and vertex buffer objects (VBOs).

- **Responsibilities**:
  - Binding and updating vertex buffers.
  - Managing VAOs and VBOs.
  - Providing access to buffer objects for rendering.

- **Functions**:
  - `BindVertexArray()`: Binds the vertex array object.
  - `BindVertexBuffer()`: Binds vertex data to a buffer.
  - `UpdateVertexBuffer()`: Updates vertex buffer data.
  - `GetVAO()`: Returns the vertex array object.
  - `GetNumOfVBOs()`: Returns the number of vertex buffer objects.
  - `GetVBOs()`: Returns a list of vertex buffer objects.

---

### InputManager
[[Header]](../src/Core/InputManager.h) [[Cpp]](../src/Core/InputManager.cpp)
Handles user input from keyboard and mouse.

- **Responsibilities**:
  - Tracking mouse and keyboard input.
  - Calculating mouse delta for camera movement.
  - Detecting key presses for movement and actions.

- **Functions**:
  - `UpdateInput()`: Updates input states.
  - `GetMouseDeltaRaw()`: Returns unscaled mouse delta.
  - `GetMouseDelta()`: Returns mouse delta scaled by frame time.
  - `UpPressed()`, `DownPressed()`, etc.: Detects specific key presses.

---

### TimeManager
[[Header]](../src/Core/TimeManager.h) [[Cpp]](../src/Core/TimeManager.cpp)
Manages time-related operations, such as delta time calculation.

- **Responsibilities**:
  - Tracking frame time.
  - Calculating delta time for smooth animations and updates.

- **Functions**:
  - `UpdateTime()`: Updates the time state.
  - `GetDeltaTime()`: Returns the time elapsed since the last frame.

---

### ImguiManager
[[Header]](../src/Debug/ImguiManager.h) [[Cpp]](../src/Debug/ImguiManager.cpp)
Manages ImGui integration for GUI rendering and file dialogs.

- **Responsibilities**:
  - Initializing and managing ImGui.
  - Handling file dialogs for OBJ and texture loading.
  - Displaying temporary messages.

- **Functions**:
  - `UpdateFrame()`: Updates ImGui frame state.
  - `UpdateFileDialog()`: Updates file dialog states.
  - `Render()`: Renders ImGui elements.
  - `Exit()`: Cleans up ImGui resources.
  - `printMessage()`: Displays a temporary message.
  - `OpenFileDialog()`: Opens a file dialog for a specific file type.
  - `GetFileDialog()`: Returns the file dialog for a specific file type.

---

### Material
[[Header]](../src/Graphics/Material.h) [[Cpp]](../src/Graphics/Material.cpp)
Manages material properties for rendering.

- **Responsibilities**:
  - Providing default material properties (ambient, diffuse, specular, shininess).

- **Functions**:
  - `GetDefaultAmbient()`: Returns default ambient material properties.
  - `GetDefaultDiffuse()`: Returns default diffuse material properties.
  - `GetDefaultSpecular()`: Returns default specular material properties.
  - `GetDefaultShininess()`: Returns default shininess material properties.

---

### Mesh
[[Header]](../src/Graphics/Mesh.h) [[Cpp]](../src/Graphics/Material.cpp)
Represents a 3D mesh with vertices and textures.

- **Responsibilities**:
  - Managing vertex data and textures for rendering.
  - Loading textures for the mesh.

- **Functions**:
  - `LoadTexture()`: Loads a texture for the mesh.
  - `GetVertices()`: Returns the vertices of the mesh.
  - `GetVerticesSize()`: Returns the size of the vertex data.

---

### OBJModelImporter
[[Header]](../src/Graphics/OBJModelImporter.h) [[Cpp]](../src/Graphics/OBJModelImporter.cpp)
Imports and parses OBJ model files.

- **Responsibilities**:
  - Parsing OBJ files to extract vertex, texture, and normal data.
  - Providing access to parsed model data.

- **Functions**:
  - `parseObjFile()`: Parses an OBJ file.
  - `getNumVertices()`: Returns the number of vertices in the model.
  - `getVertices()`: Returns the vertex data.
  - `getTexCoords()`: Returns the texture coordinates.
  - `getNormals()`: Returns the normal data.

---

### Primitive
[[Header]](../src/Graphics/Primitive.h) [[Cpp]](../src/Graphics/Primitive.cpp)
Provides predefined primitive shapes (e.g., cube, pyramid).

- **Responsibilities**:
  - Storing vertex data for primitive shapes.
  - Creating and managing primitive shapes.

- **Functions**:
  - `CreatePrimitiveCube()`: Creates a cube primitive.

---

### Shader
[[Header]](../src/Graphics/Shader.h) [[Cpp]](../src/Graphics/Shader.cpp)
Manages individual shaders (vertex, fragment).

- **Responsibilities**:
  - Compiling and managing shader programs.

- **Functions**:
  - `CreateShader()`: Creates a shader from a file.
  - `GetId()`: Returns the shader ID.

---

### ShaderManager
[[Header]](../src/Graphics/ShaderManager.h) [[Cpp]](../src/Graphics/ShaderManager.h)
Manages multiple shaders and links them into a shader program.

- **Responsibilities**:
  - Linking shaders into a program.
  - Managing the shader program.

- **Functions**:
  - `LinkShaders()`: Links shaders into a program.
  - `UseShaders()`: Activates the shader program.
  - `AddShader()`: Adds a shader to the manager.
  - `GetProgramId()`: Returns the shader program ID.

---

### Texture
[[Header]](../src/Graphics/Texture.h) [[Cpp]](../src/Graphics/Texture.cpp)
Manages texture loading and binding.

- **Responsibilities**:
  - Loading textures from files.
  - Binding textures for rendering.

- **Functions**:
  - `LoadTexture()`: Loads a texture from a file.
  - `GetTextureId()`: Returns the texture ID.

---

### Camera
[[Header]](../src/Scene/Camera.h) [[Cpp]](../src/Scene/Camera.cpp)
Manages the camera's position and rotation.

- **Responsibilities**:
  - Updating camera position and rotation based on input.
  - Providing camera state for rendering.

- **Functions**:
  - `Update()`: Updates the camera state.
  - `GetPos()`: Returns the camera position.
  - `SetPos()`: Sets the camera position.
  - `GetRot()`: Returns the camera rotation.

---

### ScreenUtils
[[Header]](../src/Utilities/ScreenUtils.h)
Provides utility functions for screen resolution and window management.

- **Responsibilities**:
  - Setting screen resolution.
  - Managing fullscreen and windowed modes.

- **Functions**:
  - `setResolutionHD()`: Sets the resolution to HD.
  - `setResolutionFHD()`: Sets the resolution to Full HD.
  - `setScreenMode()`: Sets the screen mode (fullscreen or windowed).

---

### Utils
[[Header]](../src/Utilities/Utils.h) [[Cpp]](../src/Utilities/Utils.cpp)
Provides utility functions for shader loading, debugging, and matrix/vector operations.

- **Responsibilities**:
  - Reading shader files.
  - Debugging OpenGL and shader programs.
  - Printing matrix and vector values.

- **Functions**:
  - `readShaderFile()`: Reads a shader file.
  - `createShaderProgram()`: Creates a shader program.
  - `printShaderLog()`: Prints shader log for debugging.
  - `printProgramLog()`: Prints program log for debugging.
  - `checkOpenGLError()`: Checks for OpenGL errors.
  - `printMatrix4Value()`: Prints a 4x4 matrix.
  - `printVector3Value()`: Prints a 3D vector.

---

## System
In order for the program to be able to register time and input, `TimeManager` and `InputManager` need to be instantiated with their respective constructors and their `Update()` function called in the `while()` loop of the main program.

<u>**Note**</u> that you need to instantiate `TimeManager` **before** the `InputManager`, due to `InputManager`'s constructor needing a reference to it.

Another useful class to use is the `Camera` class, which contains and movement data position, which can be used with `TimeManager` and `InputManager` in order to move around in the scene. Its `Update()` function should also be called in the `while()` loop of the main program.

---

## Graphics
`OBJModelImporter` is the class used to load the **OBJ** type of format into the program. It retuns the necessary data, such as vertices count, to whoever calls it, and can be used either with manual OpenGL buffer loading (like in the main.cpp program), or with the `Mesh` class, to create a mesh instance.

`Primitive` class can be used if you want to create simple 3D primitive shapes, like pyramids or cubes, if loading 3D objects doesn't seem like an option.


---

### Buffer Management
Most of the buffer management in the main program is done manually, by calling the OpenGL buffer functions (e.g. `glGenBuffer()`).

However, if you want to, you can use `BufferManager` as a helper class to able to load basic vertices, textures, normals, etc. But it is ***not*** needed if you don't want to use it.

---

## Input
All of the program's user input (save for GUI) is done through the `InputManager` instance in the main program. 
It retains data about the WASD keys for camera movement, and mouse rotations on the x and y axis.


---

## Time Management
`TimeManager` contains the core time data to be used for other classes, such as current time delta time.
It's used as a core component for many classes that need to be updated contantly (e.g. `InputManager`).

---

## GUI
All of the GUI in Shader Ninja is done through `ImguiManager`. In it, other than the main `imgui.h` library, another library called `imfilebrowser.h` is used, to able to create dialogs/windows for file selection.

The `ImguiManager->UpdateFrame()`  needs to be called before `TimeManager.UpdateTime()` and `InputManager.UpdateInput()`, to set the next frames it will show before OpenGL gets loaded (otherwise imgui gui will *not* be shown).

<u>**However**</u>, the `ImguiManager->UpdateFileDialog()` and `ImguiManager->UpdateRender()` functions need to be called ***after*** `UpdateTime()` and `UpdateInput()`, to render the Imgui GUI and the FileDialog *over* the OpenGL window.

---

## [Building and Linking](https://github.com/Rossakis/ShaderNinja/blob/main/README.md)

