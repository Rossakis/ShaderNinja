#version 430 core
//'layout (location = 0)' : layout qualifier
// in : input (there also exists 'out' type)
// position : name of the variable
layout (location = 0) in vec3 position;

out vec4 varyingColor;//the color will be outputed to the fragmentShader through the rasterizer

uniform float offset;
uniform float scale = 1.0f;
uniform float angle = 0.0f;

uniform mat4 mv_matrix;//model-view matrix
uniform mat4 proj_matrix;//projection matrix

void main(void) {
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);  // right-to-left
    varyingColor = vec4(position, 1.0f) * 0.5f + vec4(0.5f, 0.5f, 0.5f, 0.5f);  
}