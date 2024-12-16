#version 430 core

layout (binding = 0) uniform sampler2D samp; // Texture sampler

uniform mat4 projMat;
uniform mat4 mvMat;

in vec2 tc;       // Interpolated texture coordinates from the vertex shader
out vec4 color;   // Output color of the fragment

void main(void){ 
    color = texture(samp, tc); // Sample the texture using interpolated texture coordinates
}