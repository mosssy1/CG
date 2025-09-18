#pragma once
#include "include.h"
#include "stb_image.h"

class MaterialLoader {
public:
    MaterialLoader();
    void LoadMaterialTextures(const aiMaterial* material);
    void ApplyMaterial(aiMaterial* material, int index);

private:
    std::vector<GLuint> m_texIds;
    bool m_texLoaded;

    glm::vec3 ConvertColorToGL(aiColor4D& color);
};