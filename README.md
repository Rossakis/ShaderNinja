# HOW TO INSTALL AND BUILD SHADER-NINJA

### NOTE: Make sure you have at least C++ 20, and have installed CMake on your device beforehand at: 
https://cmake.org/download/
<br/>

In case you're using "<b>Visual Studio Code</b>", make sure to download the "<b>C/C++</b>" and "<b>CMake Tools</b>" extensions by Microsoft.
<br/>
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

### Step 2: Specify CMake source and buildsystem files
```
cmake -B ./build
```

This will create your project's "build" directory within the current one, along with the necessary CMake buildsystem files.
<br/>
<br/>
### Step 3: Create the CMake build files
```
cmake --build ./build
```
This will create the build files using the compiler available on your operating system (E.g., Ninja, Clang, GNU, etc.).
<br/>
<br/>
### Step 4: The executable will now have been created in the "build" directory. Now, you can either:
  a) Type this to run the program:
  ```
  ./build/your_executable_name
  ```
 OR 
  <br/>
  <br/>
  b) Navigate to the same folder in Explorer (Windows) or Finder (MacOS), and double-click on the created executable.

### Alternative to Step 3-4: To both build and run the executable in the "build" directory with one command, you can type:
  ```
  cmake --build ./build --target run
  ```
  <br/>
  <br/>

![ShaderNinja-BasicTriangle](https://github.com/user-attachments/assets/f4234e8d-3dbe-4119-ba2f-c691d88420dd)
