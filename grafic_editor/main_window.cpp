#include "main_window.h"



MainWindow::MainWindow(HINSTANCE hInstance, WNDPROC WndProc, WNDPROC WndButtomsProc)
{
    hInst = hInstance;
    TCHAR szClassName[] = L"Main window"; // ������ � ������ ������

    WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
    wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
    wc.style = CS_HREDRAW | CS_VREDRAW| CS_DBLCLKS| CS_CLASSDC; // ����� ������ ������
    wc.lpfnWndProc = WndButtomsProc; // ��������� �� ���������������� �������
    wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
    wc.lpszClassName = szClassName; // ��������� �� ��� ������
    wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
    wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // ��������� �����������
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // ���������� ��������� ����������� (� ����)
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ��� �������� ���� ����
    wc.hInstance = hInstance; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
    }

    hMainWnd = CreateWindow(
        szClassName, // ��� ������
        L"����������� ������� ���������", // ��� ������ (�� ��� ������)
        WS_OVERLAPPEDWINDOW, // ������ ����������� ������
        CW_USEDEFAULT, // ������� ������ �� ��� �
        NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
        CW_USEDEFAULT, // ������ ������
        NULL, // ������ ������ (��� ������ � ������, �� ������ �� �����)
        (HWND)NULL, // ���������� ������������� ����
        NULL, // ���������� ����
        HINSTANCE(hInstance), // ���������� ���������� ����������
        NULL); // ������ �� ������� �� WndProc

    if (!hMainWnd) {
        MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
    }

    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.lpszClassName = L"ChildWClass";
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.style =  CS_DBLCLKS | CS_CLASSDC;
    RegisterClass(&w);

    HWND child;
    RECT rect;
    GetWindowRect(hMainWnd, &rect);
    child = CreateWindowEx(
        0,
        L"ChildWClass",
        (LPCTSTR)NULL,
        WS_CHILD | WS_BORDER | WS_VISIBLE,
        0,90,
        rect.right, rect.bottom,
        hMainWnd,
        NULL,
        hInstance,
        NULL);
    hCanvasWnd = child;
    init_color_buttoms();
}

void MainWindow:: init_color_buttoms()
{
    RECT rect;
    GetWindowRect(hMainWnd, &rect);
    int start_x = (rect.right - rect.left) / 7 * 4;
    int start_y = 5;
    HWND black = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1010,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND gray = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 23,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1011,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND red = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON|BS_OWNERDRAW,

        start_x + 46,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,       
        (HMENU)1012,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND green = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 69,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,      
        (HMENU)1013,       
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND blue = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 92,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,       
        (HMENU)1014,      
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND orange = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 115,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1015,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND purple = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 138,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1016,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_blue = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 161,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1017,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND dark_green = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 184,         // starting x position 
        start_y,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1018,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);


    HWND white = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1110,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_gray = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 23,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1111,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_red = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 46,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1112,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_green = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 69,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1113,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_blue_1 = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 92,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1114,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_orange = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 115,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1115,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_purple = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 138,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1116,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_light_blue = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 161,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1117,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND light_dark_green = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x + 184,         // starting x position 
        start_y + 23,         // starting y position 
        20,        // button width 
        20,        // button height 
        hMainWnd,
        (HMENU)1118,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND show_color = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x - 50,         // starting x position 
        start_y,         // starting y position 
        40,        // button width 
        40,        // button height 
        hMainWnd,
        (HMENU)1200,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND show_border_color = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,

        start_x - 100,         // starting x position 
        start_y,         // starting y position 
        40,        // button width 
        40,        // button height 
        hMainWnd,
        (HMENU)1201,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND rect_buttom = CreateWindow(L"BUTTON", L"Rect", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,

        start_x - 170,         // starting x position 
        start_y,         // starting y position 
        60,        // button width 
        40,        // button height 
        hMainWnd,
        (HMENU)1300,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND ellips_buttom = CreateWindow(L"BUTTON", L"Ellips", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        start_x - 240,         // starting x position 
        start_y,         // starting y position 
        60,        // button width 
        40,        // button height 
        hMainWnd,
        (HMENU)1301,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND triangle_buttom = CreateWindow(L"BUTTON", L"Triangle", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        start_x - 310,         // starting x position 
        start_y,         // starting y position 
        60,        // button width 
        40,        // button height 
        hMainWnd,
        (HMENU)1302,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);



    HWND choose_stile = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        start_x - 50,         // starting x position 
        start_y+60,         // starting y position 
        40,        // button width 
        10,        // button height 
        hMainWnd,
        (HMENU)1400,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);

    HWND choose_pen_stile = CreateWindow(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        start_x - 100,         // starting x position 
        start_y + 60,         // starting y position 
        40,        // button width 
        10,        // button height 
        hMainWnd,
        (HMENU)1500,
        (HINSTANCE)GetWindowLong(hMainWnd, GWL_HINSTANCE),
        NULL);


}

MainWindow::~MainWindow()
{
}

HWND MainWindow:: get_buttom_window()
{
    return hMainWnd;
}

HWND MainWindow::get_canvas_window()
{
    return hCanvasWnd;
}

HINSTANCE MainWindow::get_hInst()
{
    return hInst;
}