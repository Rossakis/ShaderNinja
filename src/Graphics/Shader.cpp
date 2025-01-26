#include <Shader.h>
#include <Utils.h>

Shader::Shader(ShaderManager& manager) : m_manager (manager) {
    m_shader_id = 0;
}

const void Shader::CreateShader(const char* filePath, ShaderType type){
    // 1) Write Shader Code and reference it
    const std::string fileString = Utils::readShaderFile(filePath);
    const GLchar* shaderSource = fileString.c_str();

    // 2) Create Shader Object
    switch (type) {
        case ShaderType::Vertex:
            m_shader_id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::Fragment:
            m_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw std::runtime_error("Unsupported shader type provided!");
    }

    if (m_shader_id == 0) {
        throw std::runtime_error("Failed to create shader!");
    }

    // 3) Load and Attach Shader Source Code
    glShaderSource(m_shader_id, 1, &shaderSource, nullptr);

    // 4) Compile the shader
    glCompileShader(m_shader_id);

    // Check for compilation errors
    Utils::printShaderLog(m_shader_id);

    // 5) Attach Shader to Program
    glAttachShader(m_manager.GetProgramId(), m_shader_id);
}

GLuint Shader::GetId(){
    return m_shader_id;
}