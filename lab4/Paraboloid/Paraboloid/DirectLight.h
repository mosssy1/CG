#pragma once
#include "pch.h"

class DirectLight
{
public:
	explicit DirectLight(glm::vec3 direction);

	void SetDiffuseColor(glm::vec4 color);
	void SetAmbientColor(glm::vec4 color);
	void SetSpecularColor(glm::vec4 color);

	void Apply(GLenum light) const;

private:
	glm::vec3 m_direction;
	glm::vec4 m_diffuseColor;
	glm::vec4 m_ambientColor;
	glm::vec4 m_specularColor;
}; 
