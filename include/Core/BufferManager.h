#pragma once

#include <CommonIncludes.h>

class BufferManager{
    public:
        enum BufferType{
        Vertex,
        Texture,
        Color
        };

        BufferManager();
        ~BufferManager();
        const void BindVertexArray();
        const void BindVertexBuffer(const float* vertices, size_t size, BufferType type);
        const void UpdateVertexBuffer();

    private:
        GLuint m_buffer_index;
        GLuint m_num_VBOs;
        GLuint m_VAOs[1]; // VAO = Vertex Array Objects
        std::vector<GLuint> m_VBOs; // VBO = Vertex Buffer Objects
};