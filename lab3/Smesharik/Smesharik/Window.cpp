#include "Window.h"
#define M_PI 3.14159265358979323846
#include <cmath>
#include <numbers>
#include "Joshi.h"
#include <iostream>

const float rotationSpeed = 0.004f;
float rotationAngle = 0.0f;

void Window::OnRunStart()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void Window:: SetupProjectionMatrix(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double aspectRatio = double(width) / double(height);
	double viewWidth = 1280.0;
	double viewHeight = 720;
	if (aspectRatio > 1.0)
	{
		viewWidth = viewHeight * aspectRatio;
	}
	else
	{
		viewHeight = viewWidth / aspectRatio;
	}
	glOrtho(-viewWidth * 0.5, viewWidth * 0.5, -viewHeight * 0.5, viewHeight * 0.5, -1.0, 1.0);
}

void Window::Draw(int width, int height)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, width, height);
	SetupProjectionMatrix(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ��� ���������� ��������������� �������� �� ������������� +

	// ��� �� ����� ���� ������ glloadidentity? + 
	//��� ���� ����� ��������������� ��������� ������� + 
	// ����� �������������� ������ ��������� ������� + 

	//���������� ���������, ����� ���� 2 ���������, ������ ��������, ������� ���, �����
	//���� �������� ��� �� ��������, ������ ����� ������ ����, ������ �� ����������, � ������ ��� �������� ������ ����
	
	glTranslatef(-100, 0, 0.0f);
	Joshi bigSmesharik1;
	glScalef(0.8f, 0.8f, 1.0f);
	bigSmesharik1.Draw();

	// ��������� ���������� ��� �������� ���������� ���
	float centerX = 0.0f; 
	float centerY = 0.0f;
	float radius = 370.0f; 

	// ��������� ���� ��������
	rotationAngle += rotationSpeed;

	// ��������� ����� ���������� ���������� ��� �� ����������
	float newX = centerX + radius * cos(rotationAngle);
	float newY = centerY + radius * sin(rotationAngle);
	float newX2 = centerX + radius * cos(rotationAngle + M_PI); 
	float newY2 = centerY + radius * sin(rotationAngle + M_PI);


	glPushMatrix();
	glTranslatef(newX, newY, 0.0f); 
	glRotatef(rotationAngle * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
	glScalef(0.3f, 0.3f, 1.0f); 
	Joshi smallSmesharik1;
	smallSmesharik1.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(newX2, newY2, 0.0f);
	glRotatef(-rotationAngle * 720.0f / M_PI, 0.0f, 0.0f, 1.0f);
	glScalef(0.3f, 0.3f, 1.0f); 
	Joshi smallSmesharik2;
	smallSmesharik2.Draw();
	glPopMatrix();
}




