#include <Utils.h>

const std::string Utils::readShaderFile(const char* shaderFileName){
        std::ifstream shaderFile (shaderFileName);
        std::string outputString = "";
        
        if(shaderFile.is_open()){
            std::string line = "";

            while(std::getline(shaderFile, line)){
                outputString += line + '\n';
            }
            
            shaderFile.close(); 
        }
         else 
            std::cerr << "Error opening file: " << shaderFileName << std::endl;
    

        return outputString;
    };

const GLuint Utils::createShaderProgram(const char* vertFile, const char* fragFile){
    // 1) Write Shader Code and reference it
    const std::string vertString = Utils::readShaderFile(vertFile);
    const std::string fragString = Utils::readShaderFile(fragFile);

    const GLchar* vertShaderSource = vertString.c_str();
    const GLchar* fragShaderSource = fragString.c_str();

    // 2) Create Shader Objects
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 3) Load and Attach Shader Source Code
    glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
    glShaderSource(fragShader, 1, &fragShaderSource, NULL);

    // 4) Compile the shaders
    glCompileShader(vertexShader);
    glCompileShader(fragShader);

    //IMPORTANT: Check for any shader errors
    Utils::printShaderLog(vertexShader);
    Utils::printShaderLog(fragShader);

    // 5) Create the ShaderProgram
    GLuint program = glCreateProgram();

    // 6) Attach Shaders abd Link the Shader Program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    
    //request to the GLSL compiler to ensure that the shaders are compatible  
    glLinkProgram(program);
    printProgramLog(program);

    return program;
}

const void Utils::printShaderLog(GLuint shader){
    int length = 0;
    int charWritten = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    if(length > 0)
    {
        log = (char*)malloc(length);
        glGetShaderInfoLog(shader, length, &charWritten, log);
        std::cout << "Shader Log: " << log << std::endl;
        free(log);
    }
}        
        
const void Utils::printProgramLog(int program){
    int length = 0;
    int charWritten = 0;
    char* log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

    if(length > 0)
    {
        log = (char*)malloc(length);
        glGetProgramInfoLog(program, length, &charWritten, log);
        std::cout << "Program Log: " << log << std::endl;
        free(log);
    }
}

const GLenum Utils::checkOpenGLError(const char *file, int line)
{
    GLenum errorCode;
    if ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)