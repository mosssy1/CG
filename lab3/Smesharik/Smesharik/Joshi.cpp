#include "Joshi.h"
#define _USE_MATH_DEFINES 
#include <cmath>
#include <numbers>


void DrawCircle(float centerX, float centerY, float radius, int segments)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY);
	for (int i = 0; i <= segments; i++)
	{
		float angle = 2.0f * M_PI * (float)i / (float)segments;
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f(centerX + x, centerY + y);
	}
	glEnd();
}

 void DrawEllipse(float xCenter, float yCenter, float rx, float ry, int points = 360)
{
	const float step = static_cast<float>(2 * M_PI / points);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(xCenter, yCenter);

	for (float angle = 0; angle <= 3 * M_PI; angle += step)
	{
		float a = (fabsf(static_cast<float>(angle - 2 * M_PI)) < 1e-5) ? 0 : angle;
		const float dx = rx * cosf(a);
		const float dy = ry * sinf(a);
		glVertex2f(dx + xCenter, dy + yCenter);
	}
	glEnd();
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) 
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1); 
	glVertex2f(x2, y2); 
	glVertex2f(x3, y3); 
	glEnd();
}

void DrawSpines()
{
	glColor3f(0.352, 0.239, 0.49);
	for (int i = 0; i < 5; i++) 
	{
		glPushMatrix();
		glTranslated(0, 25, 0);
		glRotated(45 * i, 0, 0, 1);
		glTranslated(140 , 0, 0);
		DrawTriangle(0, 120, 0, -120, 120, 0);
		glPopMatrix();
	}
}

void DrawBody() 
{
	glPushMatrix(); 
	glColor3f(0.784, 0.325, 0.471);
	DrawCircle(0, 0, 190, 100);
	glPopMatrix();
	
}

void DrawEars()
{
	glPushMatrix();
	glColor3f(0.784, 0.325, 0.471);
	DrawCircle(188, 55, 25, 80);
	DrawCircle(-188, 55, 25, 80);
	glPopMatrix();
}

void DrawHands()
{
	//right
	glPushMatrix();
	glColor3f(0.784, 0.325, 0.471);
	glTranslated(180, -110, 0);
	glRotated(25, 0, 0, 1);
	DrawEllipse(0, 0, 20, 45);
	DrawCircle(-10, -32, 20, 80);
	glPopMatrix();
	
	//left
	glPushMatrix();
	glColor3f(0.784, 0.325, 0.471);
	glTranslated(-180, -110, 0);
	glRotated(-25, 0, 0, 1);
	DrawEllipse(0, 0, 20, 45);
	DrawCircle(10, -32, 20, 80);
	glPopMatrix();
}

void DrawLegs() 
{
	//right
	glPushMatrix();
	glColor3f(0.784, 0.325, 0.471);
	glTranslated(60, -200, 0);
	DrawEllipse(0, 0, 20, 45);
	DrawCircle(0, -20, 25, 80);
	glPopMatrix();

	//right
	glPushMatrix();
	glColor3f(0.784, 0.325, 0.471);
	glTranslated(-60, -200, 0);
	DrawEllipse(0, 0, 20, 45);
	DrawCircle(0, -20, 25, 80);
	glPopMatrix();
}

void DrawGlasses() 
{
	glPushMatrix();
	glColor3f(0.239, 0.09, 0.267);
	DrawCircle(61, 45, 67, 80);
	DrawCircle(-61, 45, 67, 80);
	
	glBegin(GL_QUADS);
	glVertex2f(120, 57);
	glVertex2f(180, 78);
	glVertex2f(180, 58);
	glVertex2f(120, 37);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-120, 57);
	glVertex2f(-180, 78);
	glVertex2f(-180, 58);
	glVertex2f(-120, 37);
	glEnd();
	glPopMatrix();
}

void DrawEyes()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	DrawCircle(61, 45, 48, 80);
	DrawCircle(-61, 45, 48, 80);

	glColor3f(0, 0, 0);
	DrawEllipse(35, 40, 20, 25);
	DrawEllipse(-35, 40, 20, 25);

	glColor3f(1, 1, 1);
	DrawEllipse(28, 50, 9, 10);
	DrawEllipse(-28, 50, 9, 10);
	glPopMatrix();
}

void DrawNose() 
{
	glPushMatrix();
	glColor3f(0.549, 0.141, 0.243);
	DrawTriangle(-25, -10, 25, -10, 0, -35);

	glBegin(GL_QUADS);
	glVertex2f(-3, -30);
	glVertex2f(3, -30);
	glVertex2f(3, -60);
	glVertex2f(-3, -60);
	glEnd();
	glPopMatrix();
}

void DrawMouth() 
{
	glPushMatrix();
	glColor3f(0.239, 0.09, 0.267);
	DrawTriangle(0, -60, 0, -75, 35, -55);
	DrawTriangle(0, -60, 0, -75, -35, -55);
	glPopMatrix();
}

void DrawEyebrows() 
{
	glPushMatrix();
	glColor3f(0.549, 0.141, 0.243);

	glBegin(GL_QUADS);
	glVertex2f(35, 160);
	glVertex2f(80, 150);
	glVertex2f(80, 130);
	glVertex2f(35, 140);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-35, 160);
	glVertex2f(-80, 150);
	glVertex2f(-80, 130);
	glVertex2f(-35, 140);
	glEnd();
	glPopMatrix();
}

Joshi::Joshi()
{
}

void Joshi::Draw() const
{
	DrawSpines();
	DrawBody();
	DrawEars();
	DrawHands();
	DrawLegs();
	DrawGlasses();
	DrawEyes();
	DrawNose();
	DrawMouth();
	DrawEyebrows(); 
}