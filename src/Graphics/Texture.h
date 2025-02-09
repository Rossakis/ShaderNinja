#pragma once

#include <CommonIncludes.h>

class Texture{

    public:
        Texture(const char* stringPath);
        Texture(const char* stringPath, float width, float height);
        ~Texture();
        void LoadTexture(const char* textureImagePath);
        GLuint GetTextureId();
    private:
        GLuint _textureID;
        float _width;
        float _height;
};
