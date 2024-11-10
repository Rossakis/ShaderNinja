#version 410 core
//'layout (location = 0)' : layout qualifier
// in : input (there also exists 'out' type)
// position : name of the variable
layout (location = 0) in vec3 position;

uniform float offset;
uniform float scale = 1.0f;
uniform float angle = 0.0f;

uniform mat4 mv_matrix;//model-view matrix
uniform mat4 proj_matrix;//projection matrix

void main(void) {
    // vec4 vertexPosition;
    // Scale the triangle's vertices based on the scale uniform
    // if (gl_VertexID == 0) {
    //     vertexPosition = vec4((0.25 + offset), -0.25, 0.0, 1.0);
    // }
    // else if (gl_VertexID == 1) {
    //     vertexPosition = vec4((-0.25 + offset), -0.25, 0.0, 1.0);
    // }
    // else {
    //     vertexPosition = vec4((0 + offset), 0.25, 0.0, 1.0);   
    // }

    //gl_Position = rotateZ(angle) * scaleXYZ(scale, scale, 1.0) * vertexPosition;
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);  // right-to-left

}