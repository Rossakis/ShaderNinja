#include <Texture.h>

Texture::Texture(const char* textureImagePath){
    LoadTexture(textureImagePath);
}

Texture::Texture(const char* textureImagePath, float width, float height){
    LoadTexture(textureImagePath);
    this->_width = width;
    this->_height = height;
}

Texture::~Texture() {

}

GLuint Texture::GetTextureId(){
    return this->_textureID;
}

void Texture::LoadTexture(const char* textureImagePath){
    _textureID = SOIL_load_OGL_texture(textureImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if(_textureID == 0){
        std::cout << "Could not load the texture file. Last result: " << SOIL_last_result() << std::endl;
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
};
