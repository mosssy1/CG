#include "pch.h"
#include "Scene.h"
/*
constexpr int COLUMNS = 25, ROWS = 25;
constexpr float X_MIN = -1.0f, X_MAX = 1.0f, Y_MIN = -1.0f, Y_MAX = 1.0f;

void Scene::Draw()
{
	const float dy = (Y_MAX - Y_MIN) / (ROWS - 1);
	const float dx = (X_MAX - X_MIN) / (COLUMNS - 1);

	float y = Y_MIN;
	for (int row = 0; row < ROWS - 1; ++row, y += dy)
	{
		glBegin(GL_TRIANGLE_STRIP);
		float x = -1.0f;
		for (int column = 0; column <= COLUMNS; ++column, x += dx)
		{
			glm::vec3 v0 = { x, y + dy, 0 };
			glm::vec3 v1 = { x, y, 0 };

			glVertex3f(v0.x, v0.y, v0.z);

			glVertex3f(v1.x, v1.y, v1.z);
		}
		glEnd();
	}
}*/

void Scene::Draw()
{
	float x = 0, y = 0, z = 0;

	float u = 0, v = 0;
	glBegin(GL_TRIANGLE_STRIP);
	for (v = 0; v < 1 + 0.02; v += 0.02)
	{
		for (u = 0; u <= 1; u += 0.02)
		{
			glVertex3f(u, v, z);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (u = 0; u <= 1; u += 0.02)
	{
		for (v = 0; v < 1 + 0.02; v += 0.02)
		{
			glVertex3f(u, v, z);
		}
	}
	glEnd();
	glFlush();
}

