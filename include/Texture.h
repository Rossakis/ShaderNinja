#ifndef TEXTURE_H
#define TEXTURE_H

#include <Common.h>

class Texture{

    public:
        Texture(const char* stringPath);
        ~Texture();
        const GLuint LoadTexture(const char* textureImagePath);
        
    private:
        GLuint _textureID;
};

#endif