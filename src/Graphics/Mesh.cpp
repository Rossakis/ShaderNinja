#include <Mesh.h>

Mesh::Mesh(BufferManager& buffer, float vertices[]) : m_buffer (buffer) {
    m_vertices.insert(m_vertices.end(), &vertices[0], &vertices[sizeof(vertices)]);
}

const void Mesh::LoadTexture(Texture* texture){
    if (!texture) {
        std::cerr << "Error: Texture is null." << std::endl;
        return;
    }

    m_texture = texture;
    //m_buffer.BindVertexBuffer(m_vertices);

    try {
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer[1]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, m_texture->GetTextureId());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught in LoadTexture: " << e.what() << std::endl;
    }
}

const std::vector<float> Mesh::GetVertices(){
    return m_vertices;
}