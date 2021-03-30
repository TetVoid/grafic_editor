#include <iostream>
#include <windows.h>
#include <vector>

#include <fstream>
#include "main_window.h"
#include "models.h"
#include "figure_fabric.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

std::vector<Figure> figure_list;
int figure_index=-1;
std::ofstream fout("log.txt", std::ios::app);

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
    return msg.wParam; 
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HDC hDC; 
    PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect; 
    static HCURSOR hcur = LoadCursor(NULL, IDC_SIZEALL);
    static HCURSOR scur = LoadCursor(NULL, IDC_ARROW);
    static BOOL create_flag = true;

    static Figure_fabric fabric;
    SetCursor(scur);
    switch (uMsg) {
    case WM_PAINT: 
    {
    
        hDC = BeginPaint(hWnd, &ps); 

        for(int i = 0; i<figure_list.size();i++)
            figure_list[i].draw(hDC);

        EndPaint(hWnd, &ps); 
        break;
    }
    case WM_DESTROY: 
        PostQuitMessage(NULL);
        break;
    case WM_MOUSEMOVE:
        if (figure_index!=-1 && figure_list[figure_index].is_move())
            figure_list[figure_index].update(hWnd);

        if (figure_index != -1 && figure_list[figure_index].is_rotate())
            figure_list[figure_index].rotate(hWnd);

        if (fabric.is_draw())
            fabric.draw_focus(hWnd);

        if (figure_index != -1)
            figure_list[figure_index].set_prev_cords(hWnd);
            
        break;
    case WM_RBUTTONDOWN://WM_LBUTTONDBLCLK:
        OutputDebugStringW(L"1");
        for (int i = 0; i < figure_list.size(); i++)
        {
            int prev_index = figure_index;
            if (figure_list[i].select(hWnd))
            {
                if (figure_index != -1 && figure_index!=i)
                    figure_list[figure_index].stop_select();
                figure_index = i;
                figure_list[i].init(hWnd);
            }
            if(prev_index!=-1)
                figure_list[prev_index].init(hWnd);
        }


        break;
    case WM_LBUTTONDOWN:
        OutputDebugStringW(L"2");
        create_flag = true;
        for (int i =0; i < figure_list.size(); i++)
            if (figure_list[i].check_position(hWnd))
            {
                create_flag = false;
                break;
            }

        if (create_flag)
            fabric.set_start_cords(hWnd);

        break;
    case WM_LBUTTONUP:

            if (figure_index!=-1 && figure_list[figure_index].is_move())
            {
                figure_list[figure_index].stop_move();
                SetCursor(scur);
            }
            if (figure_index != -1 && figure_list[figure_index].is_rotate())
            {
                figure_list[figure_index].stop_rotate();
                SetCursor(scur);
            }
            else if(create_flag)
            {
                fabric.set_width_height(hWnd);
                Figure new_pict = fabric.create_figure(hWnd);
                figure_list.push_back(new_pict);

                new_pict.init(hWnd);
            }
            
        break;
    case WM_SETCURSOR:
        if (figure_index != -1 && !figure_list[figure_index].is_move())
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
    }
  
    return NULL;
    
}



