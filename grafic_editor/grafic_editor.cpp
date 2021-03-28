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
    HDC hDC; // создаём дескриптор ориентации текста на экране
    PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect; 
    HCURSOR hcur = LoadCursor(NULL, IDC_SIZEALL);
    HCURSOR scur = LoadCursor(NULL, IDC_ARROW);
    static BOOL create_flag = true;

    static Figure_fabric fabric;

   
    switch (uMsg) {
    case WM_PAINT: 
    {
    
        hDC = BeginPaint(hWnd, &ps); // инициализируем контекст устройств

        for(int i = 0; i<figure_list.size();i++)
            figure_list[i].draw(hDC);

        EndPaint(hWnd, &ps); // заканчиваем рисовать
        break;
    }
    case WM_DESTROY: // если окошко закрылось, то:
        PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
        break;
    case WM_MOUSEMOVE:
        if (figure_index!=-1 && figure_list[figure_index].is_move())
            figure_list[figure_index].update(hWnd);
        if (fabric.is_draw())
            fabric.draw_focus(hWnd);
            
        break;
    case WM_LBUTTONDOWN:
        create_flag = true;
        for (int i = 0; i < figure_list.size(); i++)
            if (figure_list[i].check_position(hWnd))
            {
                figure_index = i;
                create_flag = false;
                SetCursor(hcur);
                break;
            }

        if (create_flag)
            fabric.set_start_cords(hWnd);

        break;
    case WM_LBUTTONUP:

            if (figure_index!=-1 && figure_list[figure_index].is_move())
            {
                figure_list[figure_index].set_move(false);
                SetCursor(scur);
            }
            else if(create_flag)
            {
                fabric.set_width_height(hWnd);
                Figure new_pict = fabric.create_figure(hWnd);
                figure_list.push_back(new_pict);

                hDC = BeginPaint(hWnd, &ps);
                new_pict.init(hWnd);
                EndPaint(hWnd, &ps);
            }
            
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
    }
    return NULL;
}



