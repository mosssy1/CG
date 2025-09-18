#include "pch.h"
#include "Paraboloid.h"
#include <cmath>

void Paraboloid::Draw(void) const
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Константы для формы параболоида
    float a = 1.0; // Параметр, определяющий ширину параболоида вдоль оси x
    float b = 0.8; // Параметр, определяющий ширину параболоида вдоль оси y
    float scale_z = 2.0; // Масштабный коэффициент для оси z

    // Переменные для координат точек
    float x, y, z;

    // Параметры для параметризации
    double u, v;
    for (u = 0; u <= 2 * M_PI; u += 0.1)
    {
        glBegin(GL_LINE_STRIP);

        for (v = 0; v <= 1; v += 0.01)
        {
            // Вычисление координат точек с увеличенным масштабом по оси z
            x = a * sqrt(2 * v) * cos(u);
            y = b * sqrt(2 * v) * sin(u);
            z = v * scale_z; // Увеличиваем координату z

            // Отрисовка точки
            glColor3f(abs(x / 2.5), abs(y / 2.5), abs(z / 2.5));
            glVertex3f(x / 2.5, y / 2.5, z / 2.5);
        }

        glEnd();
    }

    glFlush();
}
