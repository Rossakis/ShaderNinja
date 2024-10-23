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
    //STEPS FOR CREATING SHADERS IN OPENGL
    // -------------------------

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

    // 5) Create the ShaderProgram
    GLuint program = glCreateProgram();

    // 6) Attach Shaders abd Link the Shader Program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);//request to the GLSL compiler to ensure that the shaders are compatible  
    
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

const bool Utils::checkOpenGLError(){
    bool foundError = false;
    int glError = glGetError();

    while(glError != GL_NO_ERROR){
        std::cout << "glError: " << glError << std::endl;
        foundError = true;
        glError = glGetError();
    }

    return foundError;
}
