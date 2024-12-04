#include <Texture.h>

Texture::Texture(const char* textureImagePath){
    LoadTexture(textureImagePath);
}

Texture::Texture(const char* textureImagePath, float width, float height){
    LoadTexture(textureImagePath);
    this->_width = width;
    this->_height = height;
}


GLuint Texture::GetTextureId(){
    return this->_textureID;
}

const GLuint Texture::LoadTexture(const char* textureImagePath){
        _textureID = SOIL_load_OGL_texture(textureImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

        if(_textureID == 0){
            std::cout << "Could not find texture file: " << textureImagePath << std::endl;
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }
    };
