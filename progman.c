#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 10000
#define MAX_BUFFER_SIZE 1024
#define lines 10
static HWND hStartEdit,hEndEdit,hButton,hButton2,thew,tthew[lines];
int xx = 2; // Define a posição horizontal
int yy = 2; // Define a posição vertical
 int nn,nnn;   
  static char startStr[1024], endStr[1024];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Temporizador");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    int iiii;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Este programa requer Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("button menu"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
        

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szBuffer[80];
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    char *menuss[50];
    char startStr[1025];
    time_t rawtime;
    struct tm *timeinfo;
    int iiii;
    menuss[0]="calc.exe";
    menuss[1]="notepad.exe";
    menuss[2]="write.exe";
    menuss[3]="keyboard.exe";
    menuss[4]="cmd.exe";
    menuss[5]="paint.exe";
    menuss[6]="control.exe";
    menuss[7]="calendar.exe";

   
    char buffer[MAX_BUFFER_SIZE];

    

    switch (message)
    {
        case WM_CREATE:
        
       for(nn=0;nn<8;nn++){
        int nnn=40+nn;
        tthew[nn] = CreateWindow("BUTTON", menuss[nn], WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            (nn-(nn/6)*6)*100+5,(nn/6)*30+5, 90, 30,  hwnd, (HMENU)nnn, GetModuleHandle(NULL), NULL);
       }
                
                
            
        
        break;
        case WM_COMMAND:
            iiii=(int)(LOWORD(wParam));
            if(iiii>=40 && iiii<=40+7){
                iiii=iiii-40;
                sprintf(startStr,"%d",iiii);
                 SetWindowText(hwnd,menuss[iiii] );
                 
                system(menuss[iiii]);
            }
            
           
    break;   

    case WM_PAINT:
            
            hdc = BeginPaint(hwnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            break;
    

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
