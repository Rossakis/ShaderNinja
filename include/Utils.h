#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL2/src/SOIL2/SOIL2.h>

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
        static const void printMatrixValue(glm::mat4 matrix, bool showColumnMajor = true);

        //Texture
        static const GLuint loadTexture(const char* textureImagePath);

};