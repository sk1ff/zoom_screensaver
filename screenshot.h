#pragma once

#include <Windows.h>

class Screenshot
{
public:
    Screenshot(void);
    ~Screenshot(void);

    void destroy();
    bool capture();

    HBITMAP getBitmap() const                   { return hbmp_; }
    int getWidth() const                        { return width_; }
    int getHeight() const                       { return height_; }

private:
    int width_, height_;
    HBITMAP hbmp_;
};
