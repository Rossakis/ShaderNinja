#version 430

in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec2 tc;       // Interpolated texture coordinates from the vertex shader
out vec4 color;   // Output color of the fragment

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
uniform sampler2D samp; // Texture sampler

void main(void){
    vec3 L = normalize(varyingLightDir);//light
    vec3 N = normalize(varyingNormal);// normal
    vec3 V = normalize(-varyingVertPos); //view

    vec3 R = normalize(reflect(-L, N)); //Compute light reflection vector with respect to N
    float cosTheta = dot(L, N); // Get the angle between the light and surface normal
    float cosFi = dot(V, R); // Angle between the view vector and the reflected light

    // Computer ADS (Ambient, Diffuse, Specular) contributions per pixel, and combine to output color
    vec3 ambient = ((globalAmbient * material.ambient) + (light.ambient * material.ambient)).xyz;
    vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(cosTheta, 0.0);
    vec3 specular = light.specular.xyz * material.specular.xyz * pow(max(cosFi, 0.0), material.shininess);

    vec4 textureColor = texture(samp, tc);  // Get the texture's color
    vec3 finalColor = (ambient + diffuse + specular) * textureColor.rgb;
    color = vec4(finalColor, 1.0);
}