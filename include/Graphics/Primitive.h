#pragma once

#include <Texture.h>
#include <array>

class Primitive{
    public:
        Primitive();
        ~Primitive();

        static const float CUBE_VERTICES[108];
        static const float CUBE_TEXTURE_VERTICES[72];
        static const float CUBE_NORMALS[108];

        static const float PYRAMID_VERTICES[54];
        static const float PYRAMID_NORMALS[54];
        static const float PYRAMID_TEXTURE_VERTICES[36];
};

