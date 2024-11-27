#ifndef PRIMITIVE_H
#define PRIMITIVE_H

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
};


#endif