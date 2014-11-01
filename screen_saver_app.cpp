#include "screen_saver_app.h"

ScreenSaverApp::ScreenSaverApp(HWND hwnd)
: hwnd_(hwnd)
{
    init();
}

ScreenSaverApp::~ScreenSaverApp(void)
{
}

void ScreenSaverApp::init()
{
    Random::init();

    timer_id_ = ::SetTimer(hwnd_, 1001, USER_TIMER_MINIMUM, NULL);
    screenshot_.capture();

    movement_.setBounds(0, 0, 1500, 1500);
}

void ScreenSaverApp::shutdown()
{
    if (timer_id_)
        ::KillTimer(hwnd_, timer_id_);
    screenshot_.destroy();
}

void ScreenSaverApp::onTimer()
{
    movement_.moveNext();

    ::RedrawWindow(hwnd_, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void ScreenSaverApp::onPaint()
{
    PAINTSTRUCT ps = {0};
    HDC dc = ::BeginPaint(hwnd_, &ps);

    ChaoticCrawling::Point pos = movement_.getPos();

    RECT rc = {0};
    ::GetClientRect(hwnd_, &rc);

    drawZoomed(dc, rc.right - rc.left, rc.bottom - rc.top, 16, screenshot_.getBitmap(), static_cast<int>(pos.x), static_cast<int>(pos.y));

    ::EndPaint(hwnd_, &ps);
}

void ScreenSaverApp::drawZoomed(HDC dest_dc, int dest_width, int dest_height, int scale, HBITMAP src_bitmap, int src_x, int src_y)
{
    HDC temp_dc = ::CreateCompatibleDC(dest_dc);
    HBITMAP old_bitmap = (HBITMAP) ::SelectObject(temp_dc, src_bitmap);

    int nx = src_x / scale;
    int ny = src_y / scale;

    int dx = src_x % scale;
    int dy = src_y % scale;

    ::StretchBlt(dest_dc, -dx, -dy, dest_width + scale, dest_height + scale, temp_dc, nx, ny, dest_width / scale + 1, dest_height / scale + 1, SRCCOPY);

    ::SelectObject(temp_dc, old_bitmap);
    ::DeleteDC(temp_dc);
}

