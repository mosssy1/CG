#include "BaseWindow.h"
#include "Joshi.h"

BaseWindow::BaseWindow(int w, int h, const char* title)
    : m_window{ CreateWindow(w, h, title) } 
{
    if (!m_window) 
    {
        throw std::runtime_error("Failed to create window");
    }
}

BaseWindow::~BaseWindow() 
{
    glfwDestroyWindow(m_window);
}


void BaseWindow::Run() 
{
    glfwMakeContextCurrent(m_window);
    OnRunStart();
    while (!glfwWindowShouldClose(m_window))
    {
        int w, h;
        glfwGetFramebufferSize(m_window, &w, &h);
        Draw(w, h);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    OnRunEnd();
}


GLFWwindow* BaseWindow::CreateWindow(int w, int h, const char* title)
{
    return glfwCreateWindow(w, h, title, nullptr, nullptr);
}
