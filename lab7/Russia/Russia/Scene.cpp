#include "pch.h"
#include "Scene.h"

void Scene::Draw()
{
	glPointSize(1.0f);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-0.8, -0.8);

		glTexCoord2f(4, 0);
		glVertex2f(0.8, -0.8);

		glTexCoord2f(4, 4);
		glVertex2f(0.8, 0.8);

		glTexCoord2f(0, 4);
		glVertex2f(-0.8, 0.8);
	}
	glEnd();
}