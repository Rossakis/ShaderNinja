# HOW TO INSTALL AND BUILD SHADER-NINJA

### NOTE: Make sure you have at least C++ 20, and have installed CMake on your device beforehand at: 
https://cmake.org/download/
<br/>

In case you're using "<b>Visual Studio Code</b>", make sure to download the "<b>C/C++</b>" and "<b>CMake Tools</b>" extensions by Microsoft.
<br/>
<br/>

### Step 1: Navigate to the directory through your terminal
```
cd <custom-ShaderNinja-directory> 
```
For example,
```
cd C:\Users\MyName\Documents\ShaderNinja
```

### Step 2: Specify CMake source and buildsystem files
```
cmake -S <./src> -B <./build>
```

This will create your project's "build" directory, with the necessary CMake buildsystem files.
<br/>
<br/>
### Step 3: Create the CMake build files
```
cmake --build <./build>
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
