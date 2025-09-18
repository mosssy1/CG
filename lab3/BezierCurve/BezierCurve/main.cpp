#include "GLFWInitializer.h"
#include "Window.h"

int main() 
{
    GLFWInitializer initGLFW;
    Window window{ 1200, 700, "Bezier curve" };
    window.Run();
    return 0;
}
