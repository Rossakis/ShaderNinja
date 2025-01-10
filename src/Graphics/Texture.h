#pragma once

#include <CommonIncludes.h>

class Texture{

    public:
        Texture(const char* stringPath);
        Texture(const char* stringPath, float width, float height);
        ~Texture();

        GLuint GetTextureId();
        const GLuint LoadTexture(const char* textureImagePath);
        
    private:
        GLuint _textureID;
        float _width;
        float _height;
};
