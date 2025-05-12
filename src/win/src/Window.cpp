#include "Window.h"
#include <windowsx.h>

namespace Luna 
{
    void (*Window::inFocus)() = nullptr;
    void (*Window::lostFocus)() = nullptr;

    Window::Window() noexcept : windowId{}, windowPosX{}, windowPosY{}
    {
        windowWidth = GetSystemMetrics(SM_CXSCREEN);
        windowHeight = GetSystemMetrics(SM_CYSCREEN);
        windowIcon = LoadIcon(nullptr, IDI_APPLICATION);
        windowCursor = LoadCursor(nullptr, IDC_ARROW);
        windowColor = RGB(0,0,0);
        windowTitle = string("Windows Game");
        windowStyle = WS_POPUP | WS_VISIBLE;
        windowMode = FULLSCREEN;
        windowCenterX = windowWidth >> 2;
        windowCenterY = windowHeight >> 2;
    }

    void Window::Mode(const uint32 mode) noexcept
    {
        windowMode = mode;

        if (mode == WINDOWED)
            windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE; 
        else
            windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE; 
    }

    void Window::Size(const uint32 width, const uint32 height) noexcept
    { 
        windowWidth = width; 
        windowHeight = height;

        windowCenterX = windowWidth >> 2;
        windowCenterY = windowHeight >> 2;

        windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) >> 2;
        windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) >> 2;
    }

    bool Window::Create() noexcept
    {
        HINSTANCE appId = GetModuleHandle(nullptr);
        
        WNDCLASSEX wndClass{}; 	
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = Window::WinProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = appId;
        wndClass.hIcon = windowIcon;
        wndClass.hCursor = windowCursor; 
        wndClass.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(windowColor));
        wndClass.lpszMenuName = nullptr;
        wndClass.lpszClassName = "GameWindow";
        wndClass.hIconSm = windowIcon;

        if (!RegisterClassEx(&wndClass))
            return false;

        windowId = CreateWindowEx(
            0,
            wndClass.lpszClassName,
            windowTitle.c_str(),
            windowStyle,
            windowPosX, windowPosY,
            windowWidth, windowHeight,
            nullptr,
            nullptr,
            appId,
            nullptr);

        if (windowMode == WINDOWED)
        {
            RECT rect { 0, 0, windowWidth, windowHeight };

            AdjustWindowRectEx(&rect,
                GetWindowStyle(windowId),
                GetMenu(windowId) != nullptr,
                GetWindowExStyle(windowId));

            windowPosX = (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
            windowPosY = (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;

            MoveWindow(
                windowId,
                windowPosX,
                windowPosY,
                rect.right - rect.left,
                rect.bottom - rect.top,
                TRUE);
        }

        return (windowId ? true : false);
    }

    LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_KILLFOCUS:
            if (lostFocus)
                lostFocus();
            return 0;

        case WM_SETFOCUS:
            if (inFocus)
                inFocus();
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}