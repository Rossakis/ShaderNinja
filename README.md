## What is Shader Ninja

Shader Ninja is 3D viewing program, running on OpenGL 4.3, that handles loading of Wavefront (OBJ) type models, alongside textures for them through PNG and JPG files. The Scene contains Imgui parameters for managing lighting values, as well as the material values applied to the 3D model.


#### BUILDING SHADER-NINJA

NOTE: Make sure you have at least C++ 20, Mingw compiler version 11.0 and newer (necessary), and have installed CMake on your device beforehand at: https://cmake.org/download/

In case you're using "<b>Visual Studio Code</b>", make sure to download the "<b>C/C++</b>" and "<b>CMake Tools</b>" extensions by Microsoft.

#### Step 1: Navigate to the directory through your terminal
```
cd "your-ShaderNinja-directory" 
```
For example,
```
cd C:\Users\MyName\Documents\ShaderNinja
```

#### Step 2: Specify CMake source and buildsystem files using the MINGW compiler
```
cmake -B ./build -G "MinGW Makefiles"
```

This will create your project's "build" directory within the current one, along with the necessary CMake buildsystem files.

#### Step 3: Create the CMake build files
```
cmake --build ./build --target run
```
This will build and run the `ShaderNinja.exe` in the `ShaderNinja/build` directory. You can also navigate to the same directory in File Explorer and double-click on the created executable to run it.

### [Read the documentation here!](documentation/ShaderNinja-Documentation.md)


![ShaderNinja-Instancing-100K-Cubes](https://github.com/user-attachments/assets/4a294322-d9c3-41e1-a347-99a3c70519d5)

