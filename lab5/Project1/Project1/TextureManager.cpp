#include "pch.h"
#include "TextureManager.h"
#include "CTextureLoader.h"
#include "TextureNamespace.h"
#include <functional>
#include <map>


CTexture2D* TextureManager::GetTexture(const std::wstring& textureName) const
{
	if (textureName == texture :: CEMENT_TEXTURE)
	{
		InitTextureIfNeed(texture :: CEMENT_TEXTURE, m_cementTexture);
		return &m_cementTexture;
	}
	else if (textureName == texture::DOOR_TEXTURE)
	{
		InitTextureIfNeed(texture::DOOR_TEXTURE, m_doorTexture);
		return &m_doorTexture;
	}
	else if (textureName == texture::REIKA_TEXTURE)
	{
		InitTextureIfNeed(texture::REIKA_TEXTURE, m_reikaTexture);
		return &m_reikaTexture;
	}
	else if (textureName == texture::STONE_TEXTURE)
	{
		InitTextureIfNeed(texture::STONE_TEXTURE, m_stoneTexture);
		return &m_stoneTexture;
	}
	else if (textureName == texture::GLASS_TEXTURE)
	{
		InitTextureIfNeed(texture::GLASS_TEXTURE, m_glassTexture);
		return &m_glassTexture;
	}
	else if (textureName == texture::GRASS_TEXTURE)
	{
		InitTextureIfNeed(texture::GRASS_TEXTURE, m_grassTexture);
		return &m_grassTexture;
	}
	else if (textureName == texture::ZABOR_TEXTURE)
	{
		InitTextureIfNeed(texture::ZABOR_TEXTURE, m_zaborTexture);
		return &m_zaborTexture;
	}
	else if (textureName == texture::BLACK_TEXTURE)
	{
		InitTextureIfNeed(texture::BLACK_TEXTURE, m_blackTexture);
		return &m_blackTexture;
	}
	throw std::exception("There are no texture for this name");
}

void TextureManager::InitTextureIfNeed(const std::wstring& textureName, CTexture2D& texture) const
{
	if (!texture)
	{
		CTextureLoader loader;
		loader.SetWrapMode(GL_REPEAT, GL_REPEAT);
		texture.Attach(loader.LoadTexture2D(textureName));
	}
}