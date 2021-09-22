// GuiManagement.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GuiManagement.h"

#define MAX_LOADSTRING 100

#include "MainWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    pCmdLine,
    _In_ int       nCmdShow)
{
    MainWindow win;
    win.setG_Hinst(hInstance);
    if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }


    ShowWindow(win.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}