#pragma once

#include <CommonIncludes.h>

class Transform{
    public:
        
glm::mat4 rotateX(float rad)
{   
    return glm::mat4(1.0,  0.0     ,  0.0      ,  0.0,
                0.0,  cos(rad),  -sin(rad),  0.0,
                0.0,  sin(rad),  cos(rad) ,  0.0,
                0.0,  0.0     ,  0.0      ,  1.0);
}

glm::mat4 rotateY(float rad)
{   
    return glm::mat4(cos(rad) ,   0.0,   sin(rad),  0.0,
                0.0      ,   1.0,     0.0   ,  0.0,
                -sin(rad),   0.0,   cos(rad),  0.0,
                0.0      ,   0.0,     0.0   ,  1.0);
}

glm::mat4 rotateZ(float rad)
{   
    return glm::mat4(cos(rad), -sin(rad),  0.0,  0.0,
                sin(rad),  cos(rad),  0.0,  0.0,
                  0.0   ,   0.0    ,  1.0,  0.0,
                  0.0   ,   0.0    ,  0.0,  1.0);
}

glm::mat4 scaleXYZ(float x, float y, float z)
{   
    return glm::mat4( x , 0.0, 0.0, 0.0,
                0.0,  y , 0.0, 0.0,
                0.0, 0.0,  z , 0.0,
                0.0, 0.0, 0.0, 1.0);
}
};
