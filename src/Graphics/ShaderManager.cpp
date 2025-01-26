#include <ShaderManager.h>
#include <Utils.h>

ShaderManager::ShaderManager(){
    m_programID  = glCreateProgram();
    Utils::printShaderLog(m_programID);

    if(m_programID <= 0){
        std::cout << "Couldn't create a program Id" << std::endl;
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
}

void ShaderManager::LinkShaders(){
    glLinkProgram(m_programID);

    GLint success;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        Utils::printProgramLog(m_programID);
        throw std::runtime_error("Program linking failed");
    }
}

void ShaderManager::UseShaders(){
   glUseProgram(m_programID);   
}

void ShaderManager::AddShader(Shader* shader){
    if(shader == nullptr){
        throw std::runtime_error("Shader is null!");
        return;
    }
    m_shaders.push_back(shader);
}

GLuint ShaderManager::GetProgramId(){
    return m_programID;
}

void ShaderManager::PrintAttachedShaders()
{
    if(m_shaders.size() <= 0)    {
        throw std::runtime_error("No shaders were added to ShaderManager!");
        return;
    }

    GLint count;
    GLuint shaders[10];
    glGetAttachedShaders(m_programID, 10, &count, shaders);
    for (int i = 0; i < count; ++i) {
        std::cout << "Attached Shader ID: " << shaders[i] << std::endl;
    }
}