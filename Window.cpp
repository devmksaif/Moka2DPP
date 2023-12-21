#include "Window.h"


LRESULT CALLBACK WinProc(HWND handle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg == WM_CLOSE ||
        Msg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(handle, Msg, wParam, lParam);
}
MOKA2DWINDOW::MOKA2DWINDOW(const int width, const int height, const char TITLE[])
{
    WNDCLASS windowClass = {};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = WinProc;
    windowClass.lpszClassName = "d3d_moka2d11";
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClass(&windowClass);
    handler = CreateWindow(
        "d3d_moka2d11", TITLE,
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
        100, 100, width, height, nullptr, nullptr
        , nullptr, nullptr
    );
}

MOKA2DWINDOW::~MOKA2DWINDOW()
{
    UnregisterClass("d3d_moka2d11", nullptr);
}




HWND MOKA2DWINDOW::getHandler()
{
    return handler;
}
