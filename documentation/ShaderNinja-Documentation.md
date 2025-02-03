# Shader Ninja - Documentation

This document provides an overview of the classes used in the project. Each section describes a class and its potential responsibilities.

## Classes

### Utils
- **Description**: 
  - Handles utility functions and common operations.
- **Responsibilities**:
  - Error checking and logging.
  - Helper functions for common tasks.

### ScreenUtils
- **Description**: 
  - Manages screen and window-related operations.
- **Responsibilities**:
  - Setting up the screen mode (fullscreen/windowed).
  - Managing window properties.

### InputManager
- **Description**: 
  - Handles user input from various devices.
- **Responsibilities**:
  - Processing keyboard, mouse, and joystick input.
  - Managing input states and events.

### Texture
- **Description**: 
  - Manages texture loading and binding.
- **Responsibilities**:
  - Loading textures from files.
  - Binding textures to OpenGL contexts.

### Primitive
- **Description**: 
  - Handles the creation and management of primitive shapes.
- **Responsibilities**:
  - Creating basic geometric shapes (e.g., cubes, spheres).
  - Managing vertex data for primitives.

### Camera
- **Description**: 
  - Manages the camera and its properties.
- **Responsibilities**:
  - Handling camera movement and rotation.
  - Managing view and projection matrices.

### BufferManager
- **Description**: 
  - Manages OpenGL buffers.
- **Responsibilities**:
  - Creating and managing vertex buffer objects (VBOs).
  - Managing vertex array objects (VAOs).

### Shader
- **Description**: 
  - Manages shader programs.
- **Responsibilities**:
  - Loading and compiling shaders.
  - Linking shader programs.

### ShaderManager
- **Description**: 
  - Manages multiple shader programs.
- **Responsibilities**:
  - Adding and linking shaders.
  - Managing the active shader program.

### ImguiManager
- **Description**: 
  - Manages ImGui integration.
- **Responsibilities**:
  - Handling ImGui rendering and updates.
  - Managing ImGui windows and widgets.

### OBJModelImporter
- **Description**: 
  - Handles the import of OBJ model files.
- **Responsibilities**:
  - Parsing OBJ files.
  - Extracting vertex, texture, and normal data.

### Material
- **Description**: 
  - Manages material properties.
- **Responsibilities**:
  - Setting material properties (ambient, diffuse, specular, shininess).
  - Managing default material values.

### TimeManager
- **Description**: 
  - Manages time-related operations.
- **Responsibilities**:
  - Tracking frame time and delta time.
  - Managing time-based updates.

## Functions

### applyMatrices
- **Description**: 
  - Applies transformation matrices to the shader.
- **Responsibilities**:
  - Calculating and setting model-view, projection, and normal matrices.

### initShaders
- **Description**: 
  - Initializes shaders.
- **Responsibilities**:
  - Creating and linking shader programs.

### imguiOptionsWidget
- **Description**: 
  - Displays ImGui options widget.
- **Responsibilities**:
  - Managing UI elements for options.

### imguiEditModeLabel
- **Description**: 
  - Displays the current edit mode.
- **Responsibilities**:
  - Showing the current mode (PauseMode/FreeMovementMode).

### imguiLightsWidget
- **Description**: 
  - Displays ImGui lights widget.
- **Responsibilities**:
  - Managing UI elements for light properties.

### imguiMaterialsWidget
- **Description**: 
  - Displays ImGui materials widget.
- **Responsibilities**:
  - Managing UI elements for material properties.

### imguiShowMessage
- **Description**: 
  - Displays a temporary message in ImGui.
- **Responsibilities**:
  - Showing success/error messages.

### setupObjVertices
- **Description**: 
  - Sets up vertices for an OBJ model.
- **Responsibilities**:
  - Binding vertex data to OpenGL buffers.

### initLights
- **Description**: 
  - Initializes light properties.
- **Responsibilities**:
  - Setting light properties in the shader.

## Main Function

### main
- **Description**: 
  - Entry point of the application.
- **Responsibilities**:
  - Initializing GLFW and OpenGL context.
  - Setting up the main loop and handling window events.
