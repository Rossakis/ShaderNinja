#include <Primitive.h>

Primitive::Primitive(){
    
}

const float Primitive::CUBE_VERTICES[108] = {
    -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
     1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
};

const float Primitive::CUBE_NORMALS[108] = {
    // Front face
    0.0f,  0.0f,  1.0f,  // Normal pointing outward along +Z
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    // Back face
    0.0f,  0.0f, -1.0f,  // Normal pointing outward along -Z
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,

    // Left face
   -1.0f,  0.0f,  0.0f,  // Normal pointing outward along -X
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,

    // Right face
    1.0f,  0.0f,  0.0f,  // Normal pointing outward along +X
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    // Top face
    0.0f,  1.0f,  0.0f,  // Normal pointing outward along +Y
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    // Bottom face
    0.0f, -1.0f,  0.0f,  // Normal pointing outward along -Y
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
};

const float Primitive::CUBE_TEXTURE_VERTICES[72] = {
     // Front face
    0.0f, 1.0f, // Bottom-left
    0.0f, 0.0f, // Top-left
    1.0f, 0.0f, // Top-right
    1.0f, 0.0f, // Top-right
    1.0f, 1.0f, // Bottom-right
    0.0f, 1.0f, // Bottom-left

    // Right face
    1.0f, 1.0f, // Bottom-left
    1.0f, 0.0f, // Top-left
    0.0f, 0.0f, // Top-right
    0.0f, 0.0f, // Top-right
    0.0f, 1.0f, // Bottom-right
    1.0f, 1.0f, // Bottom-left

    // Back face
    1.0f, 1.0f, // Bottom-left
    1.0f, 0.0f, // Top-left
    0.0f, 0.0f, // Top-right
    0.0f, 0.0f, // Top-right
    0.0f, 1.0f, // Bottom-right
    1.0f, 1.0f, // Bottom-left

    // Left face
    0.0f, 1.0f, // Bottom-left
    0.0f, 0.0f, // Top-left
    1.0f, 0.0f, // Top-right
    1.0f, 0.0f, // Top-right
    1.0f, 1.0f, // Bottom-right
    0.0f, 1.0f, // Bottom-left

    // Bottom face
    0.0f, 0.0f, // Bottom-left
    1.0f, 0.0f, // Bottom-right
    1.0f, 1.0f, // Top-right
    1.0f, 1.0f, // Top-right
    0.0f, 1.0f, // Top-left
    0.0f, 0.0f, // Bottom-left

    // Top face
    0.0f, 0.0f, // Bottom-left
    1.0f, 0.0f, // Bottom-right
    1.0f, 1.0f, // Top-right
    1.0f, 1.0f, // Top-right
    0.0f, 1.0f, // Top-left
    0.0f, 0.0f  // Bottom-left
};

 const float Primitive::PYRAMID_VERTICES[54] = {
    -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f
};

const float Primitive::CUBE_NORMALS[] = {
    // Front face
    0.0f,  0.0f,  1.0f,  // Normal pointing outward along +Z
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

    // Back face
    0.0f,  0.0f, -1.0f,  // Normal pointing outward along -Z
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,

    // Left face
   -1.0f,  0.0f,  0.0f,  // Normal pointing outward along -X
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,
   -1.0f,  0.0f,  0.0f,

    // Right face
    1.0f,  0.0f,  0.0f,  // Normal pointing outward along +X
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,

    // Top face
    0.0f,  1.0f,  0.0f,  // Normal pointing outward along +Y
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    // Bottom face
    0.0f, -1.0f,  0.0f,  // Normal pointing outward along -Y
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
};


const float Primitive::PYRAMID_TEXTURE_VERTICES[36] = {
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f  
};