#pragma once

#include <CommonIncludes.h>

class Shader;//Forward Declaration, to avoid infinite loop of includes between Shader and ShaderManager

///Contains the ID of the shader program
class ShaderManager{
    public:
        ShaderManager();
        void LinkShaders();//request to the GLSL compiler to ensure that the shaders are compatible  
        void UseShaders();//Load the program with our shaders to the GPU
        void AddShader(Shader* shader);
        GLuint GetProgramId();
        void PrintAttachedShaders();//Debug
    private:
        GLuint m_programID;
        std::vector<Shader*> m_shaders;
};
