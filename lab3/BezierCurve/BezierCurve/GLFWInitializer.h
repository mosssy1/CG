#ifndef GLFW_INITIALIZER_H
#define GLFW_INITIALIZER_H

#include <stdexcept>
#include <GLFW/glfw3.h>

class GLFWInitializer final 
{
public:
    GLFWInitializer();
    GLFWInitializer(const GLFWInitializer&) = delete;
    GLFWInitializer& operator=(const GLFWInitializer&) = delete;
    ~GLFWInitializer();
};

#endif 
