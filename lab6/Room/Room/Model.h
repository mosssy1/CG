#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "include.h"
#include <vector>
#include "MaterialLoader.h"

class Model {
public:
    Model();
    void LoadModel(const std::string& filePath);
    void RenderModel();

private:
    void CreateDisplayLists();
    void LoadTextures();

    const aiScene* m_scene;
    std::vector<int> m_displayLists;
    MaterialLoader m_materialLoader;
    float m_scale;
};