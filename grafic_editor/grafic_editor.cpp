#include <iostream>
#include <windows.h>
#include <vector>

#include <fstream>
#include "main_window.h"
#include "models.h"
#include "figure_fabric.h"
#include "interface.h"
#include "figure_memory.h"
#include "info_sub_window.h"

HBRUSH brushes[] = {
   CreateSolidBrush(RGB(0, 0, 0)),
   CreateSolidBrush(RGB(125, 125, 125)),
   CreateSolidBrush(RGB(255, 0, 0)),
   CreateSolidBrush(RGB(0, 255, 0)),
   CreateSolidBrush(RGB(0, 0, 255)),
   CreateSolidBrush(RGB(255, 153, 51)),
   CreateSolidBrush(RGB(204, 0, 153)),
   CreateSolidBrush(RGB(51, 204, 255)),
   CreateSolidBrush(RGB(0, 102, 0)),
   CreateSolidBrush(RGB(255, 255, 255)),
   CreateSolidBrush(RGB(175, 175, 175)),
   CreateSolidBrush(RGB(255, 100, 100)),
   CreateSolidBrush(RGB(100, 255, 100)),
   CreateSolidBrush(RGB(100, 100, 255)),
   CreateSolidBrush(RGB(255, 203, 101)),
   CreateSolidBrush(RGB(254, 50, 203)),
   CreateSolidBrush(RGB(101, 254, 255)),
   CreateSolidBrush(RGB(50, 152, 50))
} ;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndButtomsProc(HWND, UINT, WPARAM, LPARAM);
FigureMemory memory;
Figure_fabric fabric;

Interface window_interface = Interface();
MainWindow mainWindow;
InfoSubWindow subWindow;
HWND hMainWnd;
HWND hCanvasWnd;

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, 
    int nCmdShow)
{
    MSG msg; 
    mainWindow = MainWindow(hInstance, WndProc, WndButtomsProc);
    hMainWnd = mainWindow.get_buttom_window();
    hCanvasWnd = mainWindow.get_canvas_window();

    ShowWindow(hMainWnd, nCmdShow); 
    UpdateWindow(hMainWnd); 

    ShowWindow(hCanvasWnd, nCmdShow);
    UpdateWindow(hCanvasWnd);


    while (GetMessage(&msg, NULL, NULL, NULL)) { 
        TranslateMessage(&msg); // интерпретируем сообщения
        DispatchMessage(&msg); // передаём сообщения обратно ОС
    }
    //fout.close();
    return msg.wParam; 
}


LRESULT CALLBACK WndButtomsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    HDC hDC;
    PAINTSTRUCT ps; 

    static int brush_index = 9;
    static int border_brush_index = 0;
    static BOOL pen_or_brus = true;
    
    COLOR color;
    int brush_stile = 7;
    int pen_style = PS_SOLID;
    int pen_size = 2;
    switch (uMsg) {
    case WM_PAINT:
    {
        hDC = BeginPaint(hWnd, &ps);

        window_interface.draw(hWnd);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CTLCOLORBTN:
        switch (GetWindowLong((HWND)lParam, GWL_ID))
        {
        case 1010:
            return (LRESULT)brushes[0];
            break;
        case 1011:
            return (LRESULT)brushes[1];
            break;
        case 1012:
            return (LRESULT)brushes[2];
            break;
        case 1013:
            return (LRESULT)brushes[3];
            break;
        case 1014:
            return (LRESULT)brushes[4];
            break;
        case 1015:
            return (LRESULT)brushes[5];
            break;
        case 1016:
            return (LRESULT)brushes[6];
            break;
        case 1017:
            return (LRESULT)brushes[7];
            break;
        case 1018:
            return (LRESULT)brushes[8];
            break;
        case 1110:
            return (LRESULT)brushes[9];
            break;
        case 1111:
            return (LRESULT)brushes[10];
            break;
        case 1112:
            return (LRESULT)brushes[11];
            break;
        case 1113:
            return (LRESULT)brushes[12];
            break;
        case 1114:
            return (LRESULT)brushes[13];
            break;
        case 1115:
            return (LRESULT)brushes[14];
            break;
        case 1116:
            return (LRESULT)brushes[15];
            break;
        case 1117:
            return (LRESULT)brushes[16];
            break;
        case 1118:
            return (LRESULT)brushes[17];
            break;
        case 1200:
            return (LRESULT)brushes[brush_index];
            break;
        case 1201:
            return (LRESULT)brushes[border_brush_index];
            break;
        }

        break;
    case WM_COMMAND:
    {
        BOOL set_color_flag = true;
        BOOL set_brush_stile = false;
        BOOL set_pen_stile = false;
        BOOL set_size = false;
        switch (LOWORD(wParam))
        {
        case 1010:
            color.R = 0;
            color.G = 0;
            color.B = 0;
            if (pen_or_brus)
                brush_index = 0;
            else
                border_brush_index = 0;

            break;
        case 1011:
            color.R = 125;
            color.G = 125;
            color.B = 125;

            if (pen_or_brus)
                brush_index = 1;
            else
                border_brush_index = 1;
            break;
        case 1012:
            color.R = 255;
            color.G = 0;
            color.B = 0;


            if (pen_or_brus)
                brush_index = 2;
            else
                border_brush_index = 2;
            break;
        case 1013:
            color.R = 0;
            color.G = 255;
            color.B = 0;


            if (pen_or_brus)
                brush_index = 3;
            else
                border_brush_index = 3;
            break;
        case 1014:
            color.R = 0;
            color.G = 0;
            color.B = 255;


            if (pen_or_brus)
                brush_index = 4;
            else
                border_brush_index = 4;
            break;
        case 1015:
            color.R = 255;
            color.G = 153;
            color.B = 51;


            if (pen_or_brus)
                brush_index = 5;
            else
                border_brush_index = 5;
            break;
        case 1016:
            color.R = 204;
            color.G = 0;
            color.B = 153;


            if (pen_or_brus)
                brush_index = 6;
            else
                border_brush_index = 6;
            break;
        case 1017:
            color.R = 51;
            color.G = 204;
            color.B = 255;


            if (pen_or_brus)
                brush_index = 7;
            else
                border_brush_index = 7;
            break;
        case 1018:
            color.R = 0;
            color.G = 102;
            color.B = 0;


            if (pen_or_brus)
                brush_index = 8;
            else
                border_brush_index = 8;
            break;
        case 1110:
            color.R = 255;
            color.G = 255;
            color.B = 255;


            if (pen_or_brus)
                brush_index = 9;
            else
                border_brush_index = 9;
            break;
        case 1111:
            color.R = 175;
            color.G = 175;
            color.B = 175;


            if (pen_or_brus)
                brush_index = 10;
            else
                border_brush_index = 10;
            break;
        case 1112:
            color.R = 255;
            color.G = 100;
            color.B = 100;


            if (pen_or_brus)
                brush_index = 11;
            else
                border_brush_index = 11;
            break;
        case 1113:
            color.R = 100;
            color.G = 255;
            color.B = 100;


            if (pen_or_brus)
                brush_index = 12;
            else
                border_brush_index = 12;
            break;
        case 1114:
            color.R = 100;
            color.G = 100;
            color.B = 255;


            if (pen_or_brus)
                brush_index = 13;
            else
                border_brush_index = 13;
            break;
        case 1115:
            color.R = 255;
            color.G = 203;
            color.B = 101;


            if (pen_or_brus)
                brush_index = 14;
            else
                border_brush_index = 14;
            break;
        case 1116:
            color.R = 254;
            color.G = 50;
            color.B = 203;


            if (pen_or_brus)
                brush_index = 15;
            else
                border_brush_index = 15;
            break;
        case 1117:
            color.R = 101;
            color.G = 254;
            color.B = 255;


            if (pen_or_brus)
                brush_index = 16;
            else
                border_brush_index = 16;
            break;
        case 1118:
            color.R = 50;
            color.G = 152;
            color.B = 50;


            if (pen_or_brus)
                brush_index = 17;
            else
                border_brush_index = 17;
            break;
        case 1200:
            pen_or_brus = true;
            set_color_flag = false;
            window_interface.set_brush();
            break;
        case 1201:
            pen_or_brus = false;
            set_color_flag = false;
            window_interface.set_pen();
            break;
        case 1300:
        {
            set_color_flag = false;
            std::string figure_class = "rect";
            fabric.set_figure_class(figure_class);
            break;
        }
        case 1301:
        {
            set_color_flag = false;
            std::string figure_class = "ellips";
            fabric.set_figure_class(figure_class);
            break;
        }

        case 1302:
        {
            set_color_flag = false;
            std::string figure_class = "triangle";
            fabric.set_figure_class(figure_class);
            break;
        }
        case 1400:
        {
            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);
            POINT pt;
            pt.x = (temp_rc.right - temp_rc.left) / 7 * 4;
            pt.y = 5;
            ClientToScreen(hWnd, &pt);

            HMENU hPopMenuImage = CreatePopupMenu();

            AppendMenu(hPopMenuImage, MF_STRING, 1401, L"HS_BDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 1402, L"HS_CROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 1403, L"HS_DIAGCROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 1404, L"HS_FDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 1405, L"HS_HORIZONTAL");
            AppendMenu(hPopMenuImage, MF_STRING, 1406, L"HS_VERTICAL");
            AppendMenu(hPopMenuImage, MF_STRING, 1407, L"HS_SOLID");

            TrackPopupMenu(hPopMenuImage,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x - 50, pt.y + 70, 0, hWnd, NULL);

            DestroyMenu(hPopMenuImage);

        }
        case 1401:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_BDIAGONAL;
            break;
        case 1402:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_CROSS;
            break;
        case 1403:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_DIAGCROSS;
            break;
        case 1404:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_FDIAGONAL;
            break;
        case 1405:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_HORIZONTAL;
            break;
        case 1406:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = HS_VERTICAL;
            break;
        case 1407:
            set_brush_stile = true;
            set_color_flag = false;
            brush_stile = 7;
            break;

        case 1500:
        {
            set_color_flag = false;
            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);
            POINT pt;
            pt.x = (temp_rc.right - temp_rc.left) / 7 * 4;
            pt.y = 5;
            ClientToScreen(hWnd, &pt);

            HMENU border_menu = CreatePopupMenu();
            AppendMenu(border_menu, MF_STRING, 1501, L"PS_DASH");
            AppendMenu(border_menu, MF_STRING, 1502, L"PS_DOT");
            AppendMenu(border_menu, MF_STRING, 1503, L"PS_DASHDOT");
            AppendMenu(border_menu, MF_STRING, 1504, L"PS_DASHDOTDOT");
            AppendMenu(border_menu, MF_STRING, 1505, L"PS_SOLID");

            HMENU size_menu = CreatePopupMenu();
            AppendMenu(border_menu, MF_STRING | MF_POPUP, (UINT)size_menu, L"BORDER SIZE");
            AppendMenu(size_menu, MF_STRING, 1506, L"1");
            AppendMenu(size_menu, MF_STRING, 1507, L"2");
            AppendMenu(size_menu, MF_STRING, 1508, L"3");
            AppendMenu(size_menu, MF_STRING, 1509, L"4");
            AppendMenu(size_menu, MF_STRING, 1510, L"5");

            TrackPopupMenu(border_menu,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x - 100, pt.y + 70, 0, hWnd, NULL);

            DestroyMenu(border_menu);
            break;

        }
        case 1501:
            set_pen_stile = true;
            set_color_flag = false;
            pen_style = PS_DASH;
            OutputDebugStringW(L"1");
            break;
        case 1502:
            set_pen_stile = true;
            set_color_flag = false;
            pen_style = PS_DOT;
            break;
        case 1503:
            set_pen_stile = true;
            set_color_flag = false;
            pen_style = PS_DASHDOT;
            break;
        case 1504:
            set_pen_stile = true;
            set_color_flag = false;
            pen_style = PS_DASHDOTDOT;
            break;
        case 1505:
            set_pen_stile = true;
            set_color_flag = false;
            pen_style = PS_SOLID;
            break;
        case 1506:
            set_size = true;
            set_color_flag = false;
            pen_size = 1;
            break;
        case 1507:
            set_size = true;
            set_color_flag = false;
            pen_size = 2;
            break;
        case 1508:
            set_size = true;
            set_color_flag = false;
            pen_size = 3;
            break;
        case 1509:
            set_size = true;
            set_color_flag = false;
            pen_size = 4;
            break;
        case 1510:
            set_size = true;
            set_color_flag = false;
            pen_size = 5;
            break;

        default:
        {
            set_color_flag = false;
        }

        }

        if (set_color_flag)
        {
            if (pen_or_brus)
                fabric.set_color(color);
            else
                fabric.set_border_color(color);
            memory.set_color(color, hCanvasWnd, pen_or_brus);
        }
        else if (set_brush_stile)
            fabric.set_brush_style(brush_stile);
        else if (set_pen_stile)
            fabric.set_pen_style(pen_style);
        else if (set_size)
            fabric.set_pen_size(pen_size);

        memory.set_brush_style(brush_stile, hCanvasWnd, set_brush_stile);
        memory.set_pen_style(pen_style, hCanvasWnd, set_pen_stile);
        memory.set_pen_size(pen_size, hCanvasWnd, set_size);

        SetFocus(hWnd);
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);

       
        break;
    }
     default:
         return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }


}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hDC; 
    PAINTSTRUCT ps;
    RECT rect; 
    static HCURSOR hcur = LoadCursor(NULL, IDC_SIZEALL);
    static HCURSOR scur = LoadCursor(NULL, IDC_ARROW);

    static BOOL create_flag = false;
    static BOOL info_flag = false;

    switch (uMsg) {
    case WM_PAINT: 
    {
        hDC = BeginPaint(hWnd, &ps); 

        memory.draw(hDC);
       
        EndPaint(hWnd, &ps); 
        break;
    }
    case WM_DESTROY: 
        PostQuitMessage(NULL);
        break;
    case WM_MOUSEMOVE:
        memory.move(hWnd);
        memory.rotate(hWnd);
        memory.resize(hWnd);
        memory.set_prev_cords(hWnd);
        
        if (fabric.is_draw())
            fabric.draw_focus(hWnd);

            
        break;
    case WM_LBUTTONDBLCLK:
        memory.select(hWnd);
        break;
    case WM_LBUTTONDOWN:
    {
        create_flag = memory.check_position(hWnd);
       
        if (create_flag)
            fabric.set_start_cords(hWnd);
        if (info_flag)
        {
            DestroyWindow(subWindow.get_window());
            info_flag = false;
        }
        break;
    }
    case WM_LBUTTONUP:
    {
            memory.stop_move(hWnd);
            memory.stop_resize(hWnd);
            memory.stop_rotate(hWnd);

        if (create_flag)
        {
            fabric.set_width_height(hWnd);
            if (!fabric.is_draw())
            {
                Figure* new_pict = fabric.create_figure(hWnd);
                memory.add(new_pict);

                new_pict->init(hWnd);
            }
        }

        SetCursor(scur);
            break;
    }
    case WM_RBUTTONDOWN:
    {
        if (!info_flag && memory.is_selected())
        {
            
            info_flag = true;
            subWindow = InfoSubWindow(mainWindow.get_hInst(), hWnd, memory.get_selected(),&info_flag);
        }
        break;
    }

    case WM_KEYDOWN:
        switch(wParam)
        {
        case VK_DELETE:
            memory.del();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    /*case WM_SETCURSOR:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;*/
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
    }
  
    return NULL;
    
}



//OutputDebugStringW(L"1");