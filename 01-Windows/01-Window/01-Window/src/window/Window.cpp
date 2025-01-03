#include "Window.h"
#include <iostream>

	Window::Window(int width, int height, const char* title):width(width),height(height){
		
        // Copy title to szAppName
		strncpy(szAppName, title, sizeof(szAppName) - 1);
		szAppName[sizeof(szAppName) - 1] = '\0'; // Ensure null-termination

		if(!init())
        {
            std::cerr<<"Window creation failed";
        }
	}

	Window::~Window() {
		// Clean up resources if needed
	}
    int Window::init() 
    {
        
        wndclass.cbSize = sizeof(WNDCLASSEX);
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.lpfnWndProc = WndProc;
        wndclass.hInstance = hInstance;
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.lpszClassName = szAppName;
        wndclass.lpszMenuName = NULL;
        wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        // Register WNDCLASSEX 
        RegisterClassEx(&wndclass);
        
        // create the window
        hwnd = CreateWindow(
            szAppName,
            TEXT(szAppName),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL);

        // show window
        ShowWindow(hwnd, iCmdShow);

        // update the window
        UpdateWindow(hwnd);

        // message loop
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0; // Return success
    }



    LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

        Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        if (!window) {
            return DefWindowProc(hwnd, iMsg, wParam, lParam);
        }

        switch (iMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            break;
        }

        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }
