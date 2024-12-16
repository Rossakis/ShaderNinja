#include <BufferManager.h>

BufferManager::BufferManager(){
    m_buffer_index = 0;
    BindVertexArray();
}

const void BufferManager::BindVertexArray(){
    glGenVertexArrays(1, m_VAOs);//Create VAOs
    glBindVertexArray(m_VAOs[0]);//Make the VAO active
}

const void BufferManager::BindVertexBuffer(const float* vertices, size_t size, BufferType type){    
    GLuint newBufferId;
    m_VBOs.push_back(newBufferId);

    glGenBuffers(1, &m_VBOs[m_buffer_index]);// assign the id to the buffer 
    glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[m_buffer_index]);//make the new buffer active
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);// loads the cube vertices into the 0th VBO buffer

    switch (type)
    {
        case BufferType::Vertex:
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);
            break;
        case BufferType::Texture:
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(1);
            break;
        case BufferType::Normal:
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(2);
            break;
        case BufferType::Color:
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(3);
            break;
    
        default:
            break;
    }

    m_buffer_index++;
}

const void BufferManager::UpdateVertexBuffer(){    
}