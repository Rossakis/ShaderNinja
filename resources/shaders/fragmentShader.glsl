#version 430 core

layout (binding = 0) uniform sampler2D samp; //not used in vertex shader

in vec2 tc; //interpolated incoming texture coordinate
out vec4 color;
in vec4 varyingColor;

uniform mat4 projMat;
uniform mat4 mvMat;

void main(void){ 
    color = texture(samp, tc);
}