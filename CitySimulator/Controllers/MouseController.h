#pragma once

class MouseController
{
public:
    MouseController();
    ~MouseController();
    static bool IsClicked();
private:
    static bool mousePressed;
};

