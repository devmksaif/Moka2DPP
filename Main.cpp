#include "Windows.h"
#include "Window.h"
#include "DirectXRenderer.h"

#define WIDTH 1280
#define HEIGHT 720
HWND handle;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


    //Initialize Window
    MOKA2DWINDOW Window(WIDTH, HEIGHT, "MOKA 2D");

    //Initialize Renderer
    DirectRenderer Renderer;
    Renderer.InitRenderer(Window.getHandler());
    
   

    // Main message loop
    MSG msg = {};
    while (true)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                
                break;
            }



        }
        Renderer.Draw();
        




    }
    Renderer.CleanUp();

    return 0;

}