#pragma once

#include <CommonIncludes.h>

/// @brief A helper class that contains useful utility methods, such as reading shader files
class Utils {
    public: 
        //Shader Reading-Creation
        static const std::string readShaderFile(const char* shaderFilePath);
        static const GLuint createShaderProgram(const char* vertFile, const char* fragFile);
        
        //OpenGL/Shader Debug
        static const void printShaderLog(GLuint shader);
        static const void printProgramLog(int program);
        static const GLenum checkOpenGLError(const char *file, int line);

        //GLM Debug
        //By default, glm matrices are column-major
        static const void printMatrix4Value(glm::mat4 matrix, bool showColumnMajor = true);
        static const void printVector3Value(glm::vec3 vector);
};