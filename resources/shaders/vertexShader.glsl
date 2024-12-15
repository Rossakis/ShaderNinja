#version 430 core
//'layout (location = 0)' : layout qualifier
// in : input (there also exists 'out' type)
// position : name of the variable
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 3) in vec2 normal;
layout (binding = 0) uniform sampler2D samp; //not used in vertex shader

out vec3 fragPos;    // Pass vertex position to fragment shader
out vec3 fragNormal; // Pass normal to fragment shader
out vec2 fragTexCoord; //texture coordinate to rasterizer for interpolation
uniform mat4 projMat;
uniform mat4 mvMat;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void) {
    // gl_Position = projMat * mvMat * vec4(position, 1.0);
    // tc = texCoord;
    gl_Position = projMat * mvMat * vec4(position, 1.0);
    fragPos = vec3(mvMat * vec4(position, 1.0)); // Transform vertex position
    fragNormal = normalize(normMat * normal);   // Transform vertex normal
    fragTexCoord = texCoord;
}


// builds and returns a matrix that performs a rotation around the X axis
mat4 buildRotateX(float rad) {
    mat4 xrot = mat4(1.0, 0.0,      0.0,       0.0,
                     0.0, cos(rad), -sin(rad), 0.0,
                     0.0, sin(rad), cos(rad),  0.0,
                     0.0, 0.0,      0.0,       1.0);
    return xrot;
}

// builds and returns a matrix that performs a rotation around the Y axis
mat4 buildRotateY(float rad) {
    mat4 yrot = mat4(cos(rad),  0.0, sin(rad), 0.0,
                     0.0,       1.0, 0.0,      0.0,
                     -sin(rad), 0.0, cos(rad), 0.0,
                     0.0,       0.0, 0.0,      1.0);
    return yrot;
}

// builds and returns a matrix that performs a rotation around the Z axis
mat4 buildRotateZ(float rad) {
    mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
                     sin(rad), cos(rad),  0.0, 0.0,
                     0.0,      0.0,       1.0, 0.0,
                     0.0,      0.0,       0.0, 1.0);
    return zrot;
}

// builds and returns a translation matrix
mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x,   y,   z,   1.0);
    return trans;
}