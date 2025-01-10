#pragma once

#include <CommonIncludes.h>
#include <Texture.h>
#include <BufferManager.h>

class Mesh {
    public:
        Mesh(BufferManager& buffer, float vertices[]);
        ~Mesh();
        const void LoadTexture(Texture* texturePath);
        const std::vector<float> GetVertices();
        const GLuint GetVerticesSize();
    
    private:
        BufferManager& m_buffer;
        GLuint m_vertex_buffer[1];
        std::vector<float> m_vertices;
        Texture* m_texture;
};