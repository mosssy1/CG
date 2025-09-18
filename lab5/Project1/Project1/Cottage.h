#pragma once
#include <functional>
#include <memory>
#include "Cube.h"
#include "Pyramid.h"
#include "TextureManager.h"

using CreateCubeHandler = std::function<std::shared_ptr<Cube>(float size)>;
using CreatePyramidHandler = std::function<std::shared_ptr<Pyramid>(Pyramid::PyramidSideSize&& size, float height)>;

class Cottage
{
public:
	Cottage() = delete;
	//сделать полями класса, тогда не будет аргументов
	//вместо зависимости будет агрегация
	void static Draw(CreateCubeHandler cubeHandler, CreatePyramidHandler pyramidHandler, const TextureManager & textureManager);\
}; 
