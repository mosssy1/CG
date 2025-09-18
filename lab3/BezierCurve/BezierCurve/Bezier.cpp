#include "Bezier.h"
#include "Window.h"
#include <cmath>
#include <GL/gl.h> 

void Bezier::Draw(Point controlPoints[4], float curveStepsNumber)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= curveStepsNumber; ++i)
    {
        float t = (float)i / curveStepsNumber;

        // явна€ формула кубической кривой Ѕезье, разобратьс€ получше
        float x = pow(1 - t, 3) * controlPoints[0].x +
            3 * pow(1 - t, 2) * t * controlPoints[1].x +
            3 * (1 - t) * pow(t, 2) * controlPoints[2].x +
            pow(t, 3) * controlPoints[3].x;

        float y = pow(1 - t, 3) * controlPoints[0].y +
            3 * pow(1 - t, 2) * t * controlPoints[1].y +
            3 * (1 - t) * pow(t, 2) * controlPoints[2].y +
            pow(t, 3) * controlPoints[3].y;

        glVertex2f(x, y);
    }

    glEnd();
}
