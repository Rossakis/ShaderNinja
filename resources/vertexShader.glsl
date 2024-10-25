#version 430 core

uniform float offset;
uniform float scale = 1.0f; // New uniform for scaling
uniform float angle = 0.0f;

mat4 rotateX(float rad)
{   
    return mat4(1.0,  0.0     ,  0.0      ,  0.0,
                0.0,  cos(rad),  -sin(rad),  0.0,
                0.0,  sin(rad),  cos(rad) ,  0.0,
                0.0,  0.0     ,  0.0      ,  1.0);
}

mat4 rotateY(float rad)
{   
    return mat4(cos(rad) ,   0.0,   sin(rad),  0.0,
                0.0      ,   1.0,     0.0   ,  0.0,
                -sin(rad),   0.0,   cos(rad),  0.0,
                0.0      ,   0.0,     0.0   ,  1.0);
}

mat4 rotateZ(float rad)
{   
    return mat4(cos(rad), -sin(rad),  0.0,  0.0,
                sin(rad),  cos(rad),  0.0,  0.0,
                  0.0   ,   0.0    ,  1.0,  0.0,
                  0.0   ,   0.0    ,  0.0,  1.0);
}

mat4 scaleXYZ(float x, float y, float z)
{   
    return mat4( x , 0.0, 0.0, 0.0,
                0.0,  y , 0.0, 0.0,
                0.0, 0.0,  z , 0.0,
                0.0, 0.0, 0.0, 1.0);
}


void main(void) {
    vec4 vertexPosition;

    // Scale the triangle's vertices based on the scale uniform
    if (gl_VertexID == 0) {
        vertexPosition = vec4((0.25 + offset), -0.25, 0.0, 1.0);
    }
    else if (gl_VertexID == 1) {
        vertexPosition = vec4((-0.25 + offset), -0.25, 0.0, 1.0);
    }
    else {
        vertexPosition = vec4((0 + offset), 0.25, 0.0, 1.0);   
    }

    // Apply rotation to the vertex position
    gl_Position = rotateZ(angle) * scaleXYZ(scale, scale, 1.0) * vertexPosition; // Order of multiplication is correct
}