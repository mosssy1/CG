#pragma once
#include "Texture.h"

class TextureManager
{
public:
	TextureManager() = default;

	CTexture2D* GetTexture(const std::wstring& textureName) const;

	~TextureManager() = default;

private:
	void InitTextureIfNeed(const std::wstring& textureName, CTexture2D& texture) const;

	mutable CTexture2D m_cementTexture;
	mutable CTexture2D m_doorTexture;
	mutable CTexture2D m_reikaTexture;
	mutable CTexture2D m_stoneTexture;
	mutable CTexture2D m_glassTexture;
	mutable CTexture2D m_grassTexture;
	mutable CTexture2D m_zaborTexture;
	mutable CTexture2D m_blackTexture;
}; 
