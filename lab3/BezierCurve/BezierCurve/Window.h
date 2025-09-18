#include "BaseWindow.h"
#include <GLFW/glfw3.h>
#include "Point.h"

class Window : public BaseWindow 
{
public:
    using BaseWindow::BaseWindow;
private:
 
    void Draw(int width, int height) override;
    void DrawControlPoints();
    void DrawControlLines(Point controlPoints[4]);
};

