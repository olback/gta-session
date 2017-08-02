/*
 *  Made by olback.
 *  GitHub: github.com/olback
 *  Twitter: @Mrolback
 *  Licenced under GNU Lesser General Public License v3.0.
 *
 *  printf() is only used for debugging. Output will never be shown to the user.
 *
 *  You might say 'Just use system() instead of running a file with ShellExecute()'.
 *  No, i can't do that since the system opens a command prompt which minimizes a full screen application.
 *
 *  When you create files, use the %tmp% folder.
 *  Nope, doesn't work.
 *
 */

#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include "var.h"

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
	WinClass.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);

	if (!RegisterClassEx(&WinClass)) {
		MessageBox(NULL, "Cannot register class", "Windows error", MB_OK);
		return 1;
	}

	HWND hWnd;
	if (!(hWnd = CreateWindow("BUTEXP", name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wWidth, wHeight, NULL, NULL, hThisInst, NULL))) {
		MessageBox(NULL, "Cannot create main window", "Windows error", MB_OK);
		return 2;

	}

	ShowWindow(hWnd, WinMode);
	UpdateWindow(hWnd);

	MSG Message;

	while (GetMessage(&Message, NULL, 0, 0) > 0)
	{
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
                            system(helpURL);
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

/* --- */

int startTimeout() {

    FILE *fa = fopen("1.bat", "w");
    if (fa == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fa, "%s\n", script1);
    fclose(fa);
    ShellExecute(hwndExec, "open", "1.bat", NULL, NULL, 0);
    sleep(1);
    int del_scr1 = remove("1.bat");
    if (del_scr1 != 0) {
        printf("Error removing 1.bat.\n");
    }
    printf("Step 1 done.\n");

    printf("Slepping for %d seconds.\n",sleepTime);
    sleep(sleepTime);

    FILE *f2 = fopen("2.bat", "w");
    if (f2 == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f2, "%s\n", script2);
    fclose(f2);
    ShellExecute(hwndExec, "open", "2.bat", NULL, NULL, 0);
    sleep(1);
    int del_scr2 = remove("2.bat");
    if (del_scr2 != 0) {
        printf("Error removing 2.bat.\n");
    }
    printf("Step 2 done.\n");

    return 0;

}