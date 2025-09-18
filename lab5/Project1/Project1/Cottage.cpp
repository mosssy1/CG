#include "pch.h"
#include "Cube.h"
#include "Cottage.h"
#include "TextureManager.h"
#include "TextureNamespace.h"

	void DrawFence(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(4.0);
		auto setkaTexture = textureManager.GetTexture(texture::ZABOR_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		setkaTexture->Bind();

		glPushMatrix();//перед домом
		{
			glTranslatef(-2.0f, -0.5f, 2.5f);
			glScalef(1.0f, 0.25f, 0.01f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(2.0f, -0.5f, 2.5f);
			glScalef(1.0f, 0.25f, 0.01f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//за
		{
			glTranslatef(-2.0f, -0.5f, -2.5f);
			glScalef(1.0f, 0.25f, 0.01f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(2.0f, -0.5f, -2.5f);
			glScalef(1.0f, 0.25f, 0.01f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//слева
		{
			glTranslatef(-4.0f, -0.5f, 0.0f);
			glScalef(0.01f, 0.25f, 1.27f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//справа
		{
			glTranslatef(4.0f, -0.5f, 0.0f);
			glScalef(0.01f, 0.25f, 1.27f);
			cube->Draw();
		}
		glPopMatrix();

	}

	void DrawHouseMainPart(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(2);
		auto wallTexture = textureManager.GetTexture(texture::CEMENT_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		wallTexture->Bind();

		glPushMatrix();
		{
			cube->Draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-2.0f, 0.0f, 0.0f);
			cube->Draw();
		}
		glPopMatrix();
	}
	void DrawRoof(CreatePyramidHandler pyramidHandler, const TextureManager& textureManager)
	{
		auto pyramid = pyramidHandler({ 1.0f, 2.0f, 3.0f, 4.0f }, 1);
		auto roofTexture = textureManager.GetTexture(texture::BLACK_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		roofTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(-1.0f, 0.7f, 0.0f);
			glScalef(4.0f, 1.0f, 2.0f);
			pyramid->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(2.0f, 0.25f, 0.0f);
			glScalef(2.0f, 0.5f, 2.1f);
			pyramid->Draw();
		}
		glPopMatrix();
	}
	void DrawHouseMainPartRoof(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(2);
		auto roofTexture = textureManager.GetTexture(texture::STONE_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		roofTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(0.0f, 1.1f, 0.0f);
			glScalef(1.0f, 0.1f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-2.0f, 1.1f, 0.0f);
			glScalef(1.0f, 0.1f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();
	}

	void DrawPorch(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(2);
		auto sidingTexture = textureManager.GetTexture(texture::REIKA_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		sidingTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(-2.0f, 0.0f, 0.05f);
			glScalef(0.9f, 1.0f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();

		auto betonTexture = textureManager.GetTexture(texture::STONE_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		betonTexture->Bind();

		glPushMatrix();//поперечная балка
		{
			glTranslatef(-1.95f, 0.95f, 0.4f);
			glScalef(1.045f, 0.18f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-2.9f, 0.0f, 0.4f);
			glScalef(0.09f, 1.0f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-1.0f, 0.0f, 0.4f);
			glScalef(0.09f, 1.0f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();
	}

	void DrawDoor(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(1);
		auto doorTexture = textureManager.GetTexture(texture::DOOR_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		doorTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(-2.0f, -0.4f, 0.6f);
			glScalef(0.9f, 1.3f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();	
	}

	void DrawWindow(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(1);
		auto windowTexture = textureManager.GetTexture(texture::GLASS_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		windowTexture->Bind();

		glPushMatrix();//переднее
		{
			glTranslatef(0.0f, 0.0f, 0.55f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//заднее1
		{
			glTranslatef(0.0f, 0.0f, -0.55f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//заднее2
		{
			glTranslatef(-2.0f, 0.0f, -0.55f);
			cube->Draw();
		}
		glPopMatrix();

		glPushMatrix();//гаражное
		{
			glTranslatef(2.7f, 0.2f, 0.0f);
			glScalef(0.5f, 0.5f, 1.0f);
			cube->Draw();
		}
		glPopMatrix();
	}

	void DrawGarage(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(1.5);
		auto steelTexture = textureManager.GetTexture(texture::CEMENT_TEXTURE);

		glEnable(GL_TEXTURE_2D);
		steelTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(1.95f, -0.25f, 0.0f);
			glScalef(1.3f, 1.0f, 1.35f);
			cube->Draw();
		}
		glPopMatrix();
	}

	void DrawGarageDoor(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(1.0);
		auto steelTexture = textureManager.GetTexture(texture::REIKA_TEXTURE);

		glEnable(GL_TEXTURE_2D);
		steelTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(1.95f, -0.5f, 0.35f);
			glScalef(1.3f, 1.0f, 1.35f);
			cube->Draw();
		}
		glPopMatrix();
	}

	void DrawFloor(CreateCubeHandler cubeHandler, const TextureManager& textureManager)
	{
		auto cube = cubeHandler(2);
		auto floorTexture = textureManager.GetTexture(texture::GRASS_TEXTURE);
		glEnable(GL_TEXTURE_2D);
		floorTexture->Bind();

		glPushMatrix();
		{
			glTranslatef(0.0f, -1.2f, 0.0f);
			glScalef(6.0f, 0.2f, 6.0f);
			cube->Draw();
		}
		glPopMatrix();
	}


void Cottage::Draw(CreateCubeHandler cubeHandler, CreatePyramidHandler pyramidHandler, const TextureManager& textureManager)
{
	DrawFence(cubeHandler,textureManager);
	DrawHouseMainPart(cubeHandler, textureManager);
	DrawHouseMainPartRoof(cubeHandler, textureManager);
	DrawPorch(cubeHandler, textureManager);
	DrawDoor(cubeHandler, textureManager);
	DrawFloor(cubeHandler, textureManager);
	DrawWindow(cubeHandler, textureManager);
	DrawGarage(cubeHandler, textureManager);
	DrawGarageDoor(cubeHandler, textureManager);
	DrawRoof(pyramidHandler, textureManager);
}