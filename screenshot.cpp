#include "screenshot.h"

#pragma once

#include <Windows.h>

Screenshot::Screenshot(void)
: hbmp_(0),
  width_(0),
  height_(0)
{
}

Screenshot::~Screenshot(void)
{
    destroy();
}

void Screenshot::destroy()
{
    if (hbmp_) {
        ::DeleteObject(hbmp_);
        height_ = width_ = 0;
    }
}

bool Screenshot::capture()
{
    bool rc = false;
    HDC screen_dc = ::CreateDCA("DISPLAY", NULL, NULL, NULL);
    if (screen_dc) {

        int screen_width = ::GetDeviceCaps(screen_dc, HORZRES);
        int screen_height = ::GetDeviceCaps(screen_dc, VERTRES);

        if (screen_width >= 0 && screen_height >= 0) {
            HDC mem_dc = ::CreateCompatibleDC(screen_dc);
            if (mem_dc) {
                HBITMAP bitmap = ::CreateCompatibleBitmap(screen_dc, screen_width, screen_height);
                if (bitmap) {
                    HBITMAP old_bitmap = (HBITMAP) ::SelectObject(mem_dc, bitmap);

                    ::BitBlt(mem_dc, 0, 0, screen_width, screen_height, screen_dc, 0, 0, SRCCOPY | CAPTUREBLT);
                    ::SelectObject(mem_dc, old_bitmap);

                    rc = true;

                    destroy();
                    hbmp_ = bitmap;
                    width_ = screen_width;
                    height_ = screen_height;
                }
                ::DeleteObject(mem_dc);
            }
        }

        ::DeleteDC(screen_dc);
    }

    return rc;
}

