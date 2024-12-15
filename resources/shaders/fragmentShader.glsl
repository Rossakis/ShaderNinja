#version 430 core

layout (binding = 0) uniform sampler2D samp; //not used in vertex shader

// in vec2 fragTexCoord; //interpolated incoming texture coordinate
// out vec4 color;
// in vec4 varyingColor;

//new
in vec3 fragPos;     // From vertex shader
in vec3 fragNormal;  // From vertex shader
in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D samp;        // Texture sampler
uniform vec3 lightPos;         // Position of the light
uniform vec3 lightColor;       // Color of the light
uniform vec3 viewPos;   

//old
uniform mat4 projMat;
uniform mat4 mvMat;

void main(void){ 
    //color = texture(samp, tc); //old

    // Ambient component
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse component
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular component
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine components
    vec3 lighting = ambient + diffuse + specular;
    vec4 textureColor = texture(samp, fragTexCoord);
    fragColor = vec4(lighting, 1.0) * textureColor; // Modulate texture with lighting
}