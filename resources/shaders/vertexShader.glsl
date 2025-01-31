#version 430

layout (location = 0) in vec3 position; // Vertex position
layout (location = 1) in vec2 texCoord; // Vertex texture coordinates
layout (location = 2) in vec3 normal;   // Vertex normal (if needed for lighting calculations)
layout (binding = 0) uniform sampler2D samp; // Texture sampler (not used in vertex shader)

out vec3 varyingNormal; //Eye-space vertex normal
out vec3 varyingLightDir; // Vector pointing at light source
out vec3 varyingVertPos; // Vertex pos in eye-space
out vec3 varyingHalfVector; // Used for Blinn-Phong calculations
out vec2 tc; // Texture coordinate passed to the fragment shader

struct PositionalLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat4 normMatrix;

void main(void) {
    varyingVertPos = (mvMatrix * vec4(position, 1.0)).xyz;
    varyingLightDir = light.position - varyingVertPos;
    varyingNormal = (normMatrix * vec4(normal, 1.0)).xyz;
    varyingHalfVector = (varyingLightDir + (-varyingVertPos)).xyz;

    tc = texCoord; // Pass texture coordinates to the fragment shader
    gl_Position = projMatrix * mvMatrix * vec4(position, 1.0); // Calculate final vertex position
}


