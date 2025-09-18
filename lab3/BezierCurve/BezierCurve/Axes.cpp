#include "Axes.h"

void Axes::Draw(int width, int height) 
{
    int w, h;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

    // ��� �
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-w / 2, 0);
    glVertex2f(w / 2, 0);

    // ������� �� ��� X
    glVertex2f(w / 2, 0);
    glVertex2f(w / 2 - 20, -10);
    glVertex2f(w / 2, 0);
    glVertex2f(w / 2 - 20, 10);

    // ��� Y
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0, -h / 2);
    glVertex2f(0, h / 2);

    // c������ �� ��� Y
    glVertex2f(0, h / 2);
    glVertex2f(-10, h / 2 - 20);
    glVertex2f(0, h / 2);
    glVertex2f(10, h / 2 - 20);
    glEnd();

    // ��������� ������� �� ����
    float stepX = 60.0;
    float stepY = 35.0;

    // ������� �� ��� X
    for (int i = 1; i < 20; ++i) 
    {
        glBegin(GL_LINES);
        glVertex2f(-600 + i * stepX, -5);
        glVertex2f(-600 + i * stepX, 5);
        glEnd();
    }

    // ������� �� ��� Y
    for (int i = 1; i < 20; ++i) 
    {
        glBegin(GL_LINES);
        glVertex2f(-5, -350 + i * stepY);
        glVertex2f(5, -350 + i * stepY);
        glEnd();
    }
}
