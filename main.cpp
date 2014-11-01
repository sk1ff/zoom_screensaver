#include <Windows.h>
#include <Scrnsave.h>
#include <assert.h>

#include "screen_saver_app.h"

/* Scrnsave.lib relies on the implementation of the following three functions in our code: ScreenSaverProc, 
   ScreenSaverConfigureDialog and RegisterDialogClasses This file contains the implementation for them.
 */

ScreenSaverApp * g_app_ptr = 0;

LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
        case WM_CREATE:
            assert(g_app_ptr == 0);
            g_app_ptr = new ScreenSaverApp(hwnd);
            break;

        case WM_TIMER:
            assert(g_app_ptr != 0);
            g_app_ptr->onTimer();
            break;

        case WM_ERASEBKGND:
            return 1;

        case WM_PAINT:
            assert(g_app_ptr != 0);
            g_app_ptr->onPaint();
            break;

        case WM_DESTROY:
            delete g_app_ptr;
            break;
    }

    return ::DefScreenSaverProc(hwnd, message, wparam, lparam);
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
    return FALSE;
}

