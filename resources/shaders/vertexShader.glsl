#version 410 core
//'layout (location = 0)' : layout qualifier
// in : input (there also exists 'out' type)
// position : name of the variable
layout (location = 0) in vec3 position;

uniform mat4 projMat;
uniform float timeF;
uniform mat4 mvMat;

out vec4 varyingColor;  // be interpolated by the rasterizer

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void) {
    float i = gl_InstanceID + timeF;  // value based on time factor, but different for each cube instance
    float a = sin(203.0 * i/8000.0) * 403.0;
    float b = sin(301.0 * i/4001.0) * 401.0;
    float c = sin(400.0 * i/6003.0) * 405.0;
    
    mat4 localTrans = buildTranslate(a, b, c);
    
    // mat4 finalM = mvMat * localTrans;
    // gl_Position = projMat * finalM * vec4(position, 1.0); //randomly translate objects
    gl_Position = projMat * mvMat * vec4(position, 1.0);
    
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
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