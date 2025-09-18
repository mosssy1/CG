#include "Model.h"

Model::Model()
{
}

void Model::LoadModel(const std::string& filePath) 
{
	Assimp::Importer importer;
	m_scene = importer.ReadFile(filePath, aiProcess_FlipUVs);
	LoadTextures();
	CreateDisplayLists();
}

void Model::RenderModel() 
{

	for (int i = 0; i < m_displayLists.size(); ++i) 
	{
		glCallList(m_displayLists[i]);
	}
}


void Model::CreateDisplayLists() 
{
	int meshCount = m_scene->mNumMeshes;
	m_displayLists.resize(meshCount);

	for (int i = 0; i < meshCount; ++i) 
	{
		aiMesh* mesh = m_scene->mMeshes[i];
		m_displayLists[i] = glGenLists(1);
		glNewList(m_displayLists[i], GL_COMPILE);

		m_materialLoader.ApplyMaterial(m_scene->mMaterials[mesh->mMaterialIndex], i);

		if (mesh->mFaces[0].mNumIndices % 3 == 0)
		{
			glBegin(GL_TRIANGLES);
		}
		else
		{
			glBegin(GL_QUADS);
		}
	
		for (int k = 0; k < mesh->mNumVertices; ++k) 
		{
			if (m_scene->mMaterials[mesh->mMaterialIndex]->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
			{
				glTexCoord2f(mesh->mTextureCoords[0][k].x, mesh->mTextureCoords[0][k].y);
			}
			glVertex3f(mesh->mVertices[k].x, mesh->mVertices[k].y, mesh->mVertices[k].z);
		}
		glEnd();

		glEndList();
	}
}

void Model::LoadTextures() 
{
	for (int i = 0; i < m_scene->mNumMeshes; ++i) 
	{
		aiMesh* mesh = m_scene->mMeshes[i];
		if (mesh->mMaterialIndex >= 0) 
		{
			aiMaterial* material = m_scene->mMaterials[mesh->mMaterialIndex];
			m_materialLoader.LoadMaterialTextures(material);
		}
	}
}//удалять дисплейные списки в деструкторе
//в ApplyMaterial добавить else disable