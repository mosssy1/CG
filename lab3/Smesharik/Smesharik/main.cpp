#include "GLFWInitializer.h"
#include "Window.h"

int main()
{
    GLFWInitializer initGLFW;
    Window window{ 1280, 720, "Smesharik" };
    window.Run();
    return 0;
}
