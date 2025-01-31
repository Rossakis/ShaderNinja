#pragma once

class Material {
    public:
        static float* GetDefaultAmbient() {
            static float ambient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
            return ambient;
        }
        static float* GetDefaultDiffuse() {
            static float diffuse[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
            return diffuse;
        }
        static float* GetDefaultSpecular() {
            static float specular[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
            return specular;
        }
        static float* GetDefaultShininess() {
            static float shininess[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
            return shininess;
        }
};


