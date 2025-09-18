#include <stdexcept>
#include <GLFW/glfw3.h>

class GLFWInitializer final 
{
public:
    GLFWInitializer();
    GLFWInitializer(const GLFWInitializer&) = delete;
    GLFWInitializer& operator=(const GLFWInitializer&) = delete;
    ~GLFWInitializer();
private:
    virtual void OnRunStart() {}
    virtual void OnRunEnd() {}
};

