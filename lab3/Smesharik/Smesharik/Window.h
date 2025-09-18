#include "BaseWindow.h"
#include <GLFW/glfw3.h>

class Window : public BaseWindow 
{
public:
    using BaseWindow::BaseWindow;
private:
    void Draw(int width, int height) override;
    void OnRunStart() override;
    void SetupProjectionMatrix(int width, int height);
};

