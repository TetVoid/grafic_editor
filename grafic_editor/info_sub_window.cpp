#include "info_sub_window.h"
#include <fstream>

HWND brush_style_buttom;
HWND pen_style_buttom;
Figure* changed_figure;
HWND edit1;
HWND edit2;
HWND edit3;
HWND edit4;
HWND edit5;
HWND edit6;
HWND edit7;
HWND edit8;
HWND edit9;
HWND parent_hWnd;
BOOL *info;
LRESULT CALLBACK childProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch (uMsg) {
    
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 2010:
        {

            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);
            POINT pt;
            pt.x = (temp_rc.right - temp_rc.left) / 7 * 4;
            pt.y = 5;
            ClientToScreen(hWnd, &pt);

            HMENU hPopMenuImage = CreatePopupMenu();

            AppendMenu(hPopMenuImage, MF_STRING, 2401, L"HS_BDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2402, L"HS_CROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 2403, L"HS_DIAGCROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 2404, L"HS_FDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2405, L"HS_HORIZONTAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2406, L"HS_VERTICAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2407, L"HS_SOLID");

            TrackPopupMenu(hPopMenuImage,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x + 58, pt.y + 88, 0, hWnd, NULL);

            DestroyMenu(hPopMenuImage);

            break;
        }
        case 2030:
        {
            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);
            POINT pt;
            pt.x = (temp_rc.right - temp_rc.left) / 7 * 4;
            pt.y = 5;
            ClientToScreen(hWnd, &pt);

            HMENU border_menu = CreatePopupMenu();
            AppendMenu(border_menu, MF_STRING, 2501, L"PS_DASH");
            AppendMenu(border_menu, MF_STRING, 2502, L"PS_DOT");
            AppendMenu(border_menu, MF_STRING, 2503, L"PS_DASHDOT");
            AppendMenu(border_menu, MF_STRING, 2504, L"PS_DASHDOTDOT");
            AppendMenu(border_menu, MF_STRING, 2505, L"PS_SOLID");

            TrackPopupMenu(border_menu,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x + 58, pt.y + 111, 0, hWnd, NULL);

            DestroyMenu(border_menu);
            break;
        }
        case 2401:
            changed_figure->set_brush_style(HS_BDIAGONAL);
            SetWindowText(brush_style_buttom, L"HS_BDIAGONAL");
            break;
        case 2402:
            changed_figure->set_brush_style(HS_CROSS);
            SetWindowText(brush_style_buttom, L"HS_CROSS");
            break;
        case 2403:
            changed_figure->set_brush_style(HS_DIAGCROSS);
            SetWindowText(brush_style_buttom, L"HS_DIAGCROSS");
            break;
        case 2404:
            changed_figure->set_brush_style(HS_FDIAGONAL);
            SetWindowText(brush_style_buttom, L"HS_FDIAGONAL");
            break;
        case 2405:
            changed_figure->set_brush_style(HS_HORIZONTAL);
            SetWindowText(brush_style_buttom, L"HS_HORIZONTAL");
            break;
        case 2406:
            changed_figure->set_brush_style(HS_VERTICAL);
            SetWindowText(brush_style_buttom, L"HS_VERTICAL");
            break;
        case 2407:
            changed_figure->set_brush_style(7);
            SetWindowText(brush_style_buttom, L"HS_SOLID");
            break;
        case 2501:
            changed_figure->set_pen_style(PS_DASH);
            SetWindowText(pen_style_buttom, L"PS_DASH");
            break;
        case 2502:
            changed_figure->set_pen_style(PS_DOT);
            SetWindowText(pen_style_buttom, L"PS_DOT");
            break;
        case 2503:
            changed_figure->set_pen_style(PS_DASHDOT);
            SetWindowText(pen_style_buttom, L"PS_DASHDOT");
            break;
        case 2504:
            changed_figure->set_pen_style(PS_DASHDOTDOT);
            SetWindowText(pen_style_buttom, L"PS_DASHDOTDOT");
            break;
        case 2505:
            changed_figure->set_pen_style(PS_SOLID);
            SetWindowText(pen_style_buttom, L"PS_SOLID");
            break;
        case 2040:
        {
            TCHAR a[9];

            COLOR color;
            GetWindowText(edit1, a, 9);
            color.R = _wtoi(a);
            GetWindowText(edit2, a, 9);
            color.G = _wtoi(a);
            GetWindowText(edit3, a, 9);
            color.B = _wtoi(a);
            changed_figure->set_color(color, parent_hWnd);

            GetWindowText(edit4, a, 9);
            color.R = _wtoi(a);
            GetWindowText(edit5, a, 9);
            color.G = _wtoi(a);
            GetWindowText(edit6, a, 9);
            color.B = _wtoi(a);
            changed_figure->set_border_color(color, parent_hWnd);
           
            GetWindowText(edit7, a, 9);
            int x = _wtoi(a);
            GetWindowText(edit8, a, 9);
            int y = _wtoi(a);
            changed_figure->update(parent_hWnd, x, y);

            GetWindowText(edit9, a, 9);
            changed_figure->set_pen_size(_wtoi(a));
            DestroyWindow(hWnd);
            *info = false;
            break;
        }
        }
        
        break;
    
    }
    
    case WM_DESTROY:
        return 0;
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    
}

InfoSubWindow::InfoSubWindow(HINSTANCE hInstance,HWND hWnd, Figure* figure,BOOL* info_flag)
{
    info = info_flag;
    parent_hWnd = hWnd;
    changed_figure = figure;
    hInst = hInstance;
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.lpfnWndProc = childProc;
    w.hInstance = hInstance;
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    w.lpszClassName = L"ChildWClass";
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&w);
    HWND child;
    
    child = CreateWindowEx(
        0,
        L"ChildWClass",
        (LPCTSTR)NULL,
        WS_CHILD | WS_BORDER | WS_VISIBLE,
        pt.x-2, pt.y-2,
        200, 170,
        hWnd,
        NULL,
        hInstance,
        NULL);
    hInfoSubWnd = child;

   edit1 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 60, 2, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit1, (LPCWSTR)std::to_wstring(figure->get_color().R).c_str());

   edit2 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 2, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit2, (LPCWSTR)std::to_wstring(figure->get_color().G).c_str());

   edit3 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 160, 2, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit3, (LPCWSTR)std::to_wstring(figure->get_color().B).c_str());

   edit4 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 60, 25, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit4, (LPCWSTR)std::to_wstring(figure->get_border_color().R).c_str());

   edit5 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 25, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit5, (LPCWSTR)std::to_wstring(figure->get_border_color().G).c_str());

   edit6 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 160, 25, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit6, (LPCWSTR)std::to_wstring(figure->get_border_color().B).c_str());

   edit7 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 80, 48, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit7, (LPCWSTR)std::to_wstring(figure->get_center().x).c_str());

   edit8 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 140, 48, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit8, (LPCWSTR)std::to_wstring(figure->get_center().y).c_str());

   edit9 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 110, 71, 30, 20, child, 0, hInst, 0);
   SetWindowText(edit9, (LPCWSTR)std::to_wstring(figure->get_pen_size()).c_str());

   LPCWSTR buttom_brush_name;
   switch (figure->get_brush_style())
   {
   case HS_BDIAGONAL:
       buttom_brush_name = L"HS_BDIAGONAL";
       break;
   case HS_CROSS:
       buttom_brush_name = L"HS_CROSS";
       break;
   case HS_DIAGCROSS:
       buttom_brush_name = L"HS_DIAGCROSS";
       break;
   case HS_FDIAGONAL:
       buttom_brush_name = L"HS_FDIAGONAL";
       break;
   case HS_HORIZONTAL:
       buttom_brush_name = L"HS_HORIZONTAL";
       break;
   case HS_VERTICAL:
       buttom_brush_name = L"HS_VERTICAL";
       break;
   case 7:
       buttom_brush_name = L"HS_SOLID";
       break;

   default:
       buttom_brush_name = L"HS_SOLID";
       break;
   }
   brush_style_buttom = CreateWindow(L"BUTTON", buttom_brush_name, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

       60,         // starting x position 
       94,         // starting y position 
       125,        // button width 
       20,        // button height 
       child,
       (HMENU)2010,
       hInst,
       NULL);
  
   LPCWSTR buttom_pen_name;
   switch (figure->get_pen_style())
   {
   case PS_DASH:
       buttom_pen_name = L"PS_DASH";
       break;
   case PS_DOT:
       buttom_pen_name = L"PS_DOT";
       break;
   case PS_DASHDOT:
       buttom_pen_name = L"PS_DASHDOT";
       break;
   case PS_DASHDOTDOT:
       buttom_pen_name = L"PS_DASHDOTDOT";
       break;
   case PS_SOLID:
       buttom_pen_name = L"PS_SOLID";
       break;
   
   default:
       buttom_pen_name = L"PS_SOLID";
       break;
   }

   pen_style_buttom = CreateWindow(L"BUTTON", buttom_pen_name, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

       60,         // starting x position 
       117,         // starting y position 
       125,        // button width 
       20,        // button height 
       child,
       (HMENU)2030,
       hInst,
       NULL);


   HWND ok_buttom = CreateWindow(L"BUTTON", L"Apply", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

       150,         // starting x position 
       143,         // starting y position 
       45,        // button width 
       20,        // button height 
       child,
       (HMENU)2040,
       hInst,
       NULL);


   ShowWindow(child, SW_NORMAL);
   UpdateWindow(child);

   PAINTSTRUCT ps;

   HDC dc = GetDC(child);
   HFONT font = CreateFont(16, 5, 0, 0, 3, 3, 4, 0, 0, 0, 0, 0, 0, L"Arial");
   SelectObject(dc, font);

   HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
   SelectObject(dc, pen);
   
   //SetBkMode(dc, TRANSPARENT);
   TextOutW(dc, 2, 2, L"Brush", lstrlen(L"Brush"));
   TextOutW(dc, 45, 2, L"R:", lstrlen(L"R:"));
   TextOutW(dc, 95, 2, L"G:", lstrlen(L"G:"));
   TextOutW(dc, 145, 2, L"B:", lstrlen(L"B:"));

   TextOutW(dc, 2, 25, L"Pen", lstrlen(L"Pen"));
   TextOutW(dc, 45, 25, L"R:", lstrlen(L"R:"));
   TextOutW(dc, 95, 25, L"G:", lstrlen(L"G:"));
   TextOutW(dc, 145, 25, L"B:", lstrlen(L"B:"));

   TextOutW(dc, 2, 48, L"Center", lstrlen(L"Center"));
   TextOutW(dc, 65, 48, L"X:", lstrlen(L"X:"));
   TextOutW(dc, 125, 48, L"Y:", lstrlen(L"Y:"));

   TextOutW(dc, 2, 71, L"Pen size", lstrlen(L"Pen size"));
   TextOutW(dc, 2, 94, L"Brush style", lstrlen(L"Brush style"));
   TextOutW(dc, 2, 117, L"Pen style", lstrlen(L"Pen style"));

}
InfoSubWindow::~InfoSubWindow()
{

}
HWND InfoSubWindow::get_window()
{
	return hInfoSubWnd;
}