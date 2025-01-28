#pragma once

#include <CommonIncludes.h>

class OBJModelImporter {
private:
    std::vector<float> vertVals;
    std::vector<float> texCoordVals;
    std::vector<float> normVals;

    std::vector<float> triangleVerts;
    std::vector<float> textureCoords;
    std::vector<float> normals;

public:
    OBJModelImporter();
    void parseObjFile(const char* path);

    int getNumVertices();
    std::vector<float> getVertices();
    std::vector<float> getTexCoords();
    std::vector<float> getNormals();
};
