#include <fstream>
#include <string>
#include <iostream>
#include <glad/glad.h>

/// @brief A helper class that contains useful utility methods, such as reading shader files
class Utils {
    public: 
        //Shader Reading-Creation
        static const std::string readShaderFile(const char* shaderFileName);
        static const GLuint createShaderProgram(const char* vertFile, const char* fragFile);
        
        //Debug
        static const void printShaderLog(GLuint shader);
        static const void printProgramLog(int program);
        static const bool checkOpenGLError();
};