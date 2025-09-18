#include <GLFW/glfw3.h>
#include "Point.h"

class Bezier 
{
public:
	Bezier();
    static void Draw(Point controlPoints[4], float curveStepsNumber);
	~Bezier() = default;
}; 
