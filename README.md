# HOW TO INSTALL AND BUILD SHADER-NINJA

### NOTE: Make sure you have at least C++ 20, Mingw compiler version 11.0 and newer (necessary), and have installed CMake on your device beforehand at: 
https://cmake.org/download/
<br/>

In case you're using "<b>Visual Studio Code</b>", make sure to download the "<b>C/C++</b>" and "<b>CMake Tools</b>" extensions by Microsoft.
<br/>

### Step 1: Navigate to the directory through your terminal
```
cd "your-ShaderNinja-directory" 
```
For example,
```
cd C:\Users\MyName\Documents\ShaderNinja
```
<br/>

### Step 2: Specify CMake source and buildsystem files using the MINGW compiler
```
cmake -B ./build -G "MinGW Makefiles"
```

This will create your project's "build" directory within the current one, along with the necessary CMake buildsystem files.
<br/>
### Step 3: Create the CMake build files
```
cmake --build ./build --target run
```
This will build and run the `ShaderNinja.exe` in the `ShaderNinja/build` directory. You can also navigate to the same directory in File Explorer and double-click on the created executable to run it.

## Full documentation of the program is here: 

[Documentation](documentation/ShaderNinja-Documentation.md)


![ShaderNinja-Instancing-100K-Cubes](https://github.com/user-attachments/assets/4a294322-d9c3-41e1-a347-99a3c70519d5)

