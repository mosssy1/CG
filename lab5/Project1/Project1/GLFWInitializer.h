#pragma once
#include "pch.h"

class GLFWInitializer final
{
public:
	GLFWInitializer();

	GLFWInitializer(GLFWInitializer const&) = delete;
	GLFWInitializer& operator=(GLFWInitializer const&) = delete;

	~GLFWInitializer() noexcept;
};