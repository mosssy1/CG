#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H

#include <stdexcept>
#include <GLFW/glfw3.h>

class BaseWindow 
{
public:
    BaseWindow(int w, int h, const char* title);
    BaseWindow(const BaseWindow&) = delete;
    BaseWindow& operator=(const BaseWindow&) = delete;
    virtual ~BaseWindow();
    void Run();
private:
    virtual void Draw(int width, int height) = 0;
    static GLFWwindow* CreateWindow(int w, int h, const char* title);
    GLFWwindow* m_window;
    virtual void OnRunStart() {}
    virtual void OnRunEnd() {}
};

#endif 

