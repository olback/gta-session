/*
 *  Made by olback.
 *  GitHub: github.com/olback
 *  Twitter: @Mrolback
 *  Licenced under GNU Lesser General Public License v3.0.
 *
 *  printf() is only used for debugging. Output will never be shown to the user.
 *
 */

#include <windows.h>
#include <stdio.h>
#include <unistd.h>

#define btnW 120 // Button/Static width
#define btnH 30 // Button/Static height

static const char name[] = "GTAToggle 2.1";							  // Window title
static const int wWidth = 450;                                        // Window width.
static const int wHeight = 150;                                       // Window  height.
static const int tabInTime = 5;                                       // Time before the process begins. AKA the time you have to tab back in to the game.
static const int sleepTime = 10;                                      // Time to block ports. Increase if it doesn't work. Decrease if you get kicked from your session.

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode)
{
	WNDCLASSEX WinClass = { 0 };

	WinClass.cbSize        = sizeof(WNDCLASSEX);
	WinClass.hInstance     = hThisInst;
	WinClass.lpszClassName = "BUTEXP";
	WinClass.lpfnWndProc   = WindowFunc;
	WinClass.style         = CS_NOCLOSE;
	WinClass.hIcon         = LoadImage(hThisInst, "AppIcon", IMAGE_ICON, 256, 256, LR_DEFAULTCOLOR);
    WinClass.hIconSm       = LoadImage(hThisInst, "AppIcon", IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	WinClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WinClass.lpszMenuName  = NULL;
	WinClass.cbClsExtra    = 0;
	WinClass.cbWndExtra    = 0;
	WinClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH | WHITE_PEN);

	if (!RegisterClassEx(&WinClass)) {
		MessageBox(NULL, "Cannot register class", "Windows error", MB_OK);
		return 1;
	}

	HWND hWnd;
	if (!(hWnd = CreateWindow("BUTEXP", name, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, wWidth, wHeight, NULL, NULL, hThisInst, NULL))) {
		MessageBox(NULL, "Cannot create main window", "Windows error", MB_OK);
		return 2;

	}

	ShowWindow(hWnd, WinMode);
	UpdateWindow(hWnd);

	MSG Message;

	while (GetMessage(&Message, NULL, 0, 0) > 0) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}


LRESULT CALLBACK WindowFunc(HWND hWnd,UINT Message ,WPARAM wParam,LPARAM lParam)
{
	switch(Message)
	{

		case WM_CREATE:
			CreateWindow("button", "Run", WS_VISIBLE | WS_CHILD | BS_FLAT, 20, 20, btnW, btnH, hWnd, (HMENU) 1001, NULL, NULL);
            CreateWindow("button", "Close", WS_VISIBLE | WS_CHILD | BS_FLAT, 160, 20, btnW, btnH, hWnd, (HMENU) 1002, NULL, NULL);
            CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD | BS_FLAT, 300, 20, btnW, btnH, hWnd, (HMENU) 1003, NULL, NULL);

            UpdateWindow(hWnd);
			break;

		case WM_COMMAND:
			switch (HIWORD(wParam))
			{
				case BN_CLICKED:

                    switch(wParam){
                        case 1001: // Run
                            printf("Run\n");
                            CreateWindow("BUTTON", "Run", WS_DISABLED | WS_CHILD | SS_CENTER | BS_CENTER, 20, 20, btnW, btnH, hWnd, (HMENU) 1001, NULL, NULL);
                            UpdateWindow(hWnd);

                            /* Wait X amount of seconds for the user to tab back in to GTA */
                            CreateWindow("STATIC", "Waiting...", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_CENTER, 160, 70, btnW, btnH, hWnd, (HMENU) 1004, NULL, NULL);
                            UpdateWindow(hWnd);
                            printf("Waiting...\n");
                            sleep(tabInTime);
                            CreateWindow("STATIC", "Running...", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_CENTER, 160, 70, btnW, btnH, hWnd, (HMENU) 1004, NULL, NULL);
                            UpdateWindow(hWnd);
                            UpdateWindow(hWnd); // Requires two updates, i dunno why :/
                            printf("Running...\n");

                            if(startTimeout() == 0) {
                                CreateWindow("STATIC", "Done!", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_CENTER, 160, 70, btnW, btnH, hWnd, (HMENU) 1004, NULL, NULL);
                                CreateWindow("BUTTON", "Run", WS_VISIBLE | WS_CHILD | BS_FLAT, 20, 20, btnW, btnH, hWnd, (HMENU) 1001, NULL, NULL);
                                UpdateWindow(hWnd);
                                printf("Done.\n");
                            } else {
                                CreateWindow("STATIC", "Failed!", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_CENTER, 160, 70, btnW, btnH, hWnd, (HMENU) 1004, NULL, NULL);
                            }

                            break;

                        case 1002: // Close
                            printf("Exit\n");
                            exit(0);

                        case 1003: // Help
                            printf("Help\n");
                            WinExec("cmd /c start https://github.com/olback/gta-session/blob/master/README.md", SW_HIDE);
                            break;

                        default:
                            break;
                    }

					break;

				default:
					break;
			}
			break;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}

    return 0;
}

int startTimeout() {

    // Block ports
    WinExec("cmd /c netsh advfirewall firewall del rule name=GTAToggle", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall add rule name=GTAToggle dir=in action=block protocol=TCP localport=80,443", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall add rule name=GTAToggle dir=out action=block protocol=TCP localport=80,443", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall add rule name=GTAToggle dir=in action=block protocol=UDP localport=6672,61455,61457,61456,61458", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall add rule name=GTAToggle dir=out action=block protocol=UDP localport=6672,61455,61457,61456,61458", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall set rule name=GTAToggle new enable=yes", SW_HIDE);

	// Wait ~10 seconds
    sleep(sleepTime);

    // Unblock ports
    WinExec("cmd /c netsh advfirewall firewall set rule name=GTAToggle new enable=no", SW_HIDE);
    WinExec("cmd /c netsh advfirewall firewall del rule name=GTAToggle", SW_HIDE);

    printf("Step 2 done.\n");

    return 0;

}