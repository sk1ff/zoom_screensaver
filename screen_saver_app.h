#pragma once

#include "screenshot.h"
#include "chaotic_crawling.h"
#include "random.h"

class ScreenSaverApp
{
public:
    ScreenSaverApp(HWND hwnd);
    ~ScreenSaverApp(void);

    void onTimer();
    void onPaint();

private:
    HWND hwnd_;
    Screenshot screenshot_;
    ChaoticCrawling movement_;
    UINT timer_id_;

    void init();
    void shutdown();

    void drawZoomed(HDC dest_dc, int dest_width, int dest_height, int scale, HBITMAP src_bitmap, int src_x, int src_y);
};
