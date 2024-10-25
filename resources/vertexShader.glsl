#version 430 core

uniform float offset;
uniform float scale = 1.0f; // New uniform for scaling

void main(void) {
    // Scale the triangle's vertices based on the scale uniform
    if (gl_VertexID == 0) {
        gl_Position = vec4((0.25 + offset) * scale, -0.25 * scale, 0.0, 1.0);
    }
    else if (gl_VertexID == 1) {
        gl_Position = vec4((-0.25 + offset) * scale, -0.25 * scale, 0.0, 1.0);
    }
    else {
        gl_Position = vec4((0 + offset) * scale, 0.25 * scale, 0.0, 1.0);   
    }
}