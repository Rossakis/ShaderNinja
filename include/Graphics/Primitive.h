#pragma once

#include <Texture.h>
#include <array>

enum PrimitiveType{
    Cube, 
    Triangle
};

class Primitive{
    public:
        Primitive();
        ~Primitive();

        const void LoadTexture(const Texture* texturePath);
        static const float CUBE_VERTICES[108];
        static const float CUBE_TEXTURE_VERTICES[72];
        static const float PYRAMID_VERTICES[54];
        static const float PYRAMID_TEXTURE_VERTICES[36];
};

