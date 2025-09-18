#pragma once
#include "TextureManager.h"

class Scene
{
public:
	void Draw() const;

	~Scene() = default;

private:
	TextureManager textureManager;
};
