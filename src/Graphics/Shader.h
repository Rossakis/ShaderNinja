#pragma once

#include <CommonIncludes.h>
#include <ShaderManager.h>

class Shader{
    public:
        enum ShaderType{
            Vertex,
            Fragment
        };
        Shader(ShaderManager& manager);
        ~Shader();
        const void CreateShader(const char* filePath, ShaderType type);
        GLuint GetId();
    
    private:
        ShaderManager& m_manager;
        GLuint m_shader_id;
};