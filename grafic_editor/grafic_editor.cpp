#include <iostream>
#include <windows.h>
#include <vector>

#include <fstream>
#include "main_window.h"
#include "models.h"
#include "figure_fabric.h"
#include "interface.h"

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

std::vector<Figure*> figure_list;
int figure_index=-1;
Interface window_interface = Interface();

//std::ofstream fout("log.txt", std::ios::app);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, 
    int nCmdShow)
{
    MSG msg; 
    MainWindow mainWindow = MainWindow(hInstance, WndProc);
    HWND hMainWnd = mainWindow.get_window();

    ShowWindow(hMainWnd, nCmdShow); 
    UpdateWindow(hMainWnd); 


    while (GetMessage(&msg, NULL, NULL, NULL)) { 
        TranslateMessage(&msg); // интерпретируем сообщения
        DispatchMessage(&msg); // передаём сообщения обратно ОС
    }
    //fout.close();
    return msg.wParam; 
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hDC; 
    PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect; 
    static HCURSOR hcur = LoadCursor(NULL, IDC_SIZEALL);
    static HCURSOR scur = LoadCursor(NULL, IDC_ARROW);
    static BOOL create_flag = true;
    static int brush_index = 9;
    static int border_brush_index = 0;
    static BOOL pen_or_brus = true;
    static std::string figure_class = "rect";

    COLOR color;

    
    static Figure_fabric fabric;
    SetCursor(scur);
    switch (uMsg) {
    case WM_PAINT: 
    {
        
        hDC = BeginPaint(hWnd, &ps); 
        for(int i = 0; i<figure_list.size();i++)
            figure_list[i]->draw(hDC);
        window_interface.draw(hWnd);


        EndPaint(hWnd, &ps); 
        break;
    }
    case WM_DESTROY: 
        PostQuitMessage(NULL);
        break;
    case WM_MOUSEMOVE:
        if (figure_index!=-1 && figure_list[figure_index]->is_move())
            figure_list[figure_index]->update(hWnd);

        if (figure_index != -1 && figure_list[figure_index]->is_rotate())
            figure_list[figure_index]->rotate(hWnd);

        if (figure_index != -1 && figure_list[figure_index]->is_resize())
            figure_list[figure_index]->resize(hWnd);

        if (fabric.is_draw())
            fabric.draw_focus(hWnd);

        if (figure_index != -1)
            figure_list[figure_index]->set_prev_cords(hWnd);
            
        break;
    case WM_LBUTTONDBLCLK://WM_RBUTTONDOWN:
        for (int i = 0; i < figure_list.size(); i++)
        {
            int prev_index = figure_index;
            if (figure_list[i]->select(hWnd))
            {
                if (figure_index != -1 && figure_index != i)
                    figure_list[figure_index]->stop_select();
                figure_index = i;
                figure_list[i]->init(hWnd);
            }
           
            if(prev_index!=-1)
                figure_list[prev_index]->init(hWnd);
        }


        break;
    case WM_LBUTTONDOWN:
        create_flag = true;
        for (int i =0; i < figure_list.size(); i++)
            if (figure_list[i]->check_position(hWnd))
            {
                create_flag = false;
                break;
            }

        if (create_flag)
            fabric.set_start_cords(hWnd);

        break;
    case WM_LBUTTONUP:
    {

        if (figure_index != -1 && figure_list[figure_index]->is_move())
        {
            figure_list[figure_index]->stop_move();
            SetCursor(scur);
        }
        else if (figure_index != -1 && figure_list[figure_index]->is_rotate())
        {
            figure_list[figure_index]->stop_rotate();
            SetCursor(scur);
        }
        else if (figure_index != -1 && figure_list[figure_index]->is_resize())
        {
            figure_list[figure_index]->stop_resize();
            SetCursor(scur);
        }
        else if (create_flag)
        {
            fabric.set_width_height(hWnd);
            Figure *new_pict = fabric.create_figure(hWnd,figure_class);
            figure_list.push_back(new_pict);

            new_pict->init(hWnd);
        }
        
        BOOL select_flag = true;
        for (int i = 0; i < figure_list.size(); i++)
            if (figure_list[i]->is_selected())
                select_flag = false;

        if (select_flag)
            figure_index = -1;
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
            color.B = 155;


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
            set_color_flag = false;
            figure_class = "rect";
            break;
        case 1301:
            set_color_flag = false;
            figure_class = "ellips";
            break;

        }

        if (set_color_flag)
        {
            if (pen_or_brus)
                fabric.set_color(color);
            else
                fabric.set_border_color(color);
            

            if (figure_index != -1)
                if (pen_or_brus)
                    figure_list[figure_index]->set_color(color, hWnd);
                else
                    figure_list[figure_index]->set_border_color(color, hWnd);
        }

        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
        break;
    }
    case WM_SETCURSOR:
        if (figure_index != -1 && !figure_list[figure_index]->is_move())
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
    }
  
    return NULL;
    
}



//OutputDebugStringW(L"1");