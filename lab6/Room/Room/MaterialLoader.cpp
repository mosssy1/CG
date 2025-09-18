#include "MaterialLoader.h"

MaterialLoader::MaterialLoader()
{
}

void MaterialLoader::LoadMaterialTextures(const aiMaterial* material) 
{
    m_texIds.resize(material->GetTextureCount(aiTextureType_DIFFUSE));
    m_texLoaded = true;

    for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) 
    {
        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, i, &texturePath) == AI_SUCCESS) 
        {
            std::string textureFilePath = texturePath.C_Str();
            if (!textureFilePath.empty()) 
            {
                unsigned int texId;
                glGenTextures(1, &texId);
                glBindTexture(GL_TEXTURE_2D, texId);

                int width, height, nrChannels;
                unsigned char* data = stbi_load(textureFilePath.c_str(), &width, &height, &nrChannels, 0);
                if (data) 
                {
                    GLenum format{};
                    if (nrChannels == 1)
                        format = GL_RED;
                    else if (nrChannels == 3)
                        format = GL_RGB;
                    else if (nrChannels == 4)
                        format = GL_RGBA;

                    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                    stbi_image_free(data);

                    m_texIds[i] = texId;
                }
                else 
                {
                    std::cout << "Failed to load texture: " << textureFilePath << std::endl;
                }
            }
        }
    }
}

void MaterialLoader::ApplyMaterial(aiMaterial* material, int index) 
{
    aiColor4D ambientColor;
    aiColor4D diffuseColor;
    aiColor4D specularColor;
    float shininess;

    aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);
    aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);
    aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);
    aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
    
    glm::vec3 ambientColorGL = ConvertColorToGL(ambientColor);
    glm::vec3 diffuseColorGL = ConvertColorToGL(diffuseColor);
    glm::vec3 specularColorL = ConvertColorToGL(specularColor);
    

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &ambientColorGL.r);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &diffuseColorGL.r);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &specularColorL.r);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    if (m_texLoaded) 
    {
        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, index, &texturePath) == AI_SUCCESS) 
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, m_texIds[index]);
        }
    }
}

glm::vec3 MaterialLoader::ConvertColorToGL(aiColor4D& color)
{
    glm::vec3 colorGL;
    colorGL.r = color.r;
    colorGL.g = color.g;
    colorGL.b = color.b;
    return colorGL;
}

