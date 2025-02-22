#include <Utils.h>

#define glCheckError() glCheckError_(__FILE__, __LINE__)

const std::string Utils::readShaderFile(const char* shaderFilePath){
    std::ifstream shaderFile (shaderFilePath);
    std::string outputString = "";
    
    if(shaderFile.is_open()){
        std::string line = "";
        while(std::getline(shaderFile, line)){
            outputString += line + '\n';
        }
        
        shaderFile.close(); 
    }
     else 
        std::cerr << "Error opening file: " << shaderFilePath << std::endl;

    return outputString;
};

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
        std::cout << "\n" << error << " | " << file << " (" << line << ")" << "\n"  << std::endl;
        // glfwTerminate();
        // exit(EXIT_SUCCESS);
    }
    return errorCode;
}

const void Utils::printMatrix4Value(glm::mat4 matrix, bool showColumnMajor){
    double dArray[16] = {0.0};

    const float *pSource;

    if(showColumnMajor == true)
        pSource = (const float*)glm::value_ptr(matrix);
    else{
        glm::mat4 transMat = glm::transpose(matrix);
        pSource = (const float*)glm::value_ptr(transMat);
    }

    for (int i = 0; i < 16; ++i)
        dArray[i] = pSource[i];            

    std::stringstream ss;
    ss << std::fixed
       << "|" << dArray[0] << ", " << dArray[1] << ", " << dArray[2] << ", " << dArray[3] << "|" << "|\n"
       << "|" << dArray[4] << ", " << dArray[5] << ", " <<  dArray[6] << ", " << dArray[7] << "|" << "|\n"
       << "|" << dArray[8] << ", " << dArray[9] << ", " <<  dArray[10] << ", " << dArray[11] << "|" << "|\n"
       << "|" << dArray[12] << ", " << dArray[13] << ", " <<  dArray[14] << ", " << dArray[15] << "|" << "|\n";

    std::cout << ss.str() << std::endl;
}

const void Utils::printVector3Value(glm::vec3 vector){ 
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";;
    std::cout << ss.str() << std::endl;
}



