#pragma once

#include <CommonIncludes.h>

class Transform{
    public:

//Row-based transforms

static glm::mat4 rotateX(float rad)
{   
    return glm::mat4(1.0,  0.0     ,  0.0      ,  0.0,
                0.0,  cos(rad),  -sin(rad),  0.0,
                0.0,  sin(rad),  cos(rad) ,  0.0,
                0.0,  0.0     ,  0.0      ,  1.0);
}

static glm::mat4 rotateY(float rad)
{   
    return glm::mat4(cos(rad) ,   0.0,   sin(rad),  0.0,
                0.0      ,   1.0,     0.0   ,  0.0,
                -sin(rad),   0.0,   cos(rad),  0.0,
                0.0      ,   0.0,     0.0   ,  1.0);
}

static glm::mat4 rotateZ(float rad)
{   
    return glm::mat4(cos(rad), -sin(rad),  0.0,  0.0,
                sin(rad),  cos(rad),  0.0,  0.0,
                  0.0   ,   0.0    ,  1.0,  0.0,
                  0.0   ,   0.0    ,  0.0,  1.0);
}

static glm::mat4 scaleXYZ(float x, float y, float z)
{   
    return glm::mat4( x , 0.0, 0.0, 0.0,
                0.0,  y , 0.0, 0.0,
                0.0, 0.0,  z , 0.0,
                0.0, 0.0, 0.0, 1.0);
}
};

/* Column-Based Transforms

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
 */
