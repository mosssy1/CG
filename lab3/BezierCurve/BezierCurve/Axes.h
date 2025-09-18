#include <GLFW/glfw3.h>
#include "Point.h"

class Axes
{
public:
	Axes();
	static void Draw(int width, int height);
	~Axes() = default;
}; 
