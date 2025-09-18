#include "Window.h"
#include "Bezier.h"
#include "Axes.h"
#include "Point.h"
#include <cmath>

Point controlPoints[4] =
{
	{ 0, 40.0 },
	{ 30.0, 70.0 },
	{ 200.0, 100.5 },
	{ -50.0, -80.5 }
};

const float controlPointSize = 7.0;
const float curveStepsNumber = 60.0;

// ������������ ��� � ������ ����� ���� � ��� �� �������  +
// ��� ����� ������� ��� ����, �����  opengl ������� � ������� ������� ���� +
// �������� ��������� ����� ��� ������ � ������������ ���� +
// ������� ��������� ����������� ����� +

void Window::Draw(int width, int height) 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION); //������� �������������, ������. ��������� �����. � ���������
	glLoadIdentity(); // ������ �� ��������� �������
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -1, 1); //�������� ������� ������� �� ������� �������������

	glMatrixMode(GL_MODELVIEW); //������� �������������
	glLoadIdentity(); // ������ �� ��������� �������

	Bezier::Draw(controlPoints, curveStepsNumber);
	Axes::Draw(width, height);
	DrawControlPoints();
	DrawControlLines(controlPoints);
}


void Window::DrawControlPoints()
{
	glColor3f(0.5, 0.5, 0.5);
	glPointSize(controlPointSize);

	glBegin(GL_POINTS);
	for (int i = 0; i < 4; ++i) 
	{
		glVertex2f(controlPoints[i].x, controlPoints[i].y);
	}
	glEnd();
}

void Window::DrawControlLines(Point controlPoints[4])
{  
	glColor3f(0.5, 0.5, 0.5);
	glLineStipple(1, 0xCCCC);
	glEnable(GL_LINE_STIPPLE);

	glBegin(GL_LINES);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; ++i)
		glVertex2f(controlPoints[i].x, controlPoints[i].y);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}
