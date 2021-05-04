#include "tableInfo.h"
#include <fstream>


Figure* changed_figure1;


HWND parent_hWnd1;
FigureMemory* copy_memory1;

std::vector<TableRow*> table_vector;

LRESULT CALLBACK TableProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    switch (uMsg) {
    case WM_PAINT:
    {
       HDC hDC = BeginPaint(hWnd, &ps);

        for(int i =0; i < table_vector.size();i++)
            table_vector[i]->draw(hDC);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_COMMAND:
    {
    
       
        if ( (LOWORD(wParam) - 3000<100) && (LOWORD(wParam) - 3000 >= 0))
        {
            int index = LOWORD(wParam) - 3000;
            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);
            POINT pt;
            GetCursorPos(&pt);

            HMENU hPopMenuImage = CreatePopupMenu();

            AppendMenu(hPopMenuImage, MF_STRING, 2100 + index, L"HS_BDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2200 + index, L"HS_CROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 2300 + index, L"HS_DIAGCROSS");
            AppendMenu(hPopMenuImage, MF_STRING, 2400 + index, L"HS_FDIAGONAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2500 + index, L"HS_HORIZONTAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2600 + index, L"HS_VERTICAL");
            AppendMenu(hPopMenuImage, MF_STRING, 2700 + index, L"HS_SOLID");

            TrackPopupMenu(hPopMenuImage,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x , pt.y , 0, hWnd, NULL);

            DestroyMenu(hPopMenuImage);
        }
        if ((LOWORD(wParam) - 3100 < 100) && (LOWORD(wParam) - 3100 >= 0))
        {
            int index = LOWORD(wParam) - 3100;
            RECT temp_rc;
            GetWindowRect(hWnd, &temp_rc);

            POINT pt;
            GetCursorPos(&pt);

            HMENU border_menu = CreatePopupMenu();
            AppendMenu(border_menu, MF_STRING, 4100 +index, L"PS_DASH");
            AppendMenu(border_menu, MF_STRING, 4200 + index, L"PS_DOT");
            AppendMenu(border_menu, MF_STRING, 4300 + index, L"PS_DASHDOT");
            AppendMenu(border_menu, MF_STRING, 4400 + index, L"PS_DASHDOTDOT");
            AppendMenu(border_menu, MF_STRING, 4500 + index, L"PS_SOLID");

            HMENU arrow_menu = CreatePopupMenu();
            AppendMenu(border_menu, MF_STRING | MF_POPUP, (UINT)arrow_menu, L"ARROW TYPE");
            AppendMenu(arrow_menu, MF_STRING, 4600 + index, L"--->");
            AppendMenu(arrow_menu, MF_STRING, 4700 + index, L"---");
            AppendMenu(arrow_menu, MF_STRING, 4800 + index, L"<--->");

            TrackPopupMenu(border_menu,
                TPM_CENTERALIGN | TPM_LEFTBUTTON,
                pt.x , pt.y , 0, hWnd, NULL);

            DestroyMenu(border_menu);
        }
        if ((LOWORD(wParam) - 2100 < 100) && (LOWORD(wParam) - 2100 >= 0))
        {
            
            int index = LOWORD(wParam) - 2100;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_BDIAGONAL);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_BDIAGONAL");
        }

        if ((LOWORD(wParam) - 2200 < 100) && (LOWORD(wParam) - 2200 >= 0))
        {
            int index = LOWORD(wParam) - 2200;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_CROSS);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_CROSS");
        }
        if ((LOWORD(wParam) - 2300 < 100) && (LOWORD(wParam) - 2300 >= 0))
        {
            int index = LOWORD(wParam) - 2300;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_DIAGCROSS);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_DIAGCROSS");
        }
        if ((LOWORD(wParam) - 2400 < 100) && (LOWORD(wParam) - 2400 >= 0))
        {
            int index = LOWORD(wParam) - 2400;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_FDIAGONAL);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_FDIAGONAL");
        }
        if ((LOWORD(wParam) - 2500 < 100) && (LOWORD(wParam) - 2500 >= 0))
        {
            int index = LOWORD(wParam) - 2500;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_HORIZONTAL);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_HORIZONTAL");
        }
        if ((LOWORD(wParam) - 2600 < 100) && (LOWORD(wParam) - 2600 >= 0))
        {
            int index = LOWORD(wParam) - 2600;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(HS_VERTICAL);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_VERTICAL");
        }
        if ((LOWORD(wParam) - 2700 < 100) && (LOWORD(wParam) - 2700 >= 0))
        {
            int index = LOWORD(wParam) - 2700;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(7);
            SetWindowText(table_vector[index]->brush_style_buttom, L"HS_SOLID");
        }
        if ((LOWORD(wParam) - 4100 < 100) && (LOWORD(wParam) - 4100 >= 0))
        {
            int index = LOWORD(wParam) - 4100;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_pen_style(PS_DASH);
            SetWindowText(table_vector[index]->pen_style_buttom, L"PS_DASH");
        }
        if ((LOWORD(wParam) - 4200 < 100) && (LOWORD(wParam) - 4200 >= 0))
        {
            int index = LOWORD(wParam) - 4200;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_pen_style(PS_DOT);
            SetWindowText(table_vector[index]->pen_style_buttom, L"PS_DOT");
        }
        if ((LOWORD(wParam) - 4300 < 100) && (LOWORD(wParam) - 4300 >= 0))
        {
            int index = LOWORD(wParam) - 4300;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_pen_style(PS_DASHDOT);
            SetWindowText(table_vector[index]->pen_style_buttom, L"PS_DASHDOT");
        }
        if ((LOWORD(wParam) - 4400 < 100) && (LOWORD(wParam) - 4400 >= 0))
        {
            int index = LOWORD(wParam) - 4400;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_pen_style(PS_DASHDOTDOT);
            SetWindowText(table_vector[index]->pen_style_buttom, L"PS_DASHDOTDOT");
        }
        if ((LOWORD(wParam) - 4500 < 100) && (LOWORD(wParam) - 4500 >= 0))
        {
            int index = LOWORD(wParam) - 4500;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_pen_style(PS_SOLID);
            SetWindowText(table_vector[index]->pen_style_buttom, L"PS_SOLID");
        }

        if ((LOWORD(wParam) - 4600 < 100) && (LOWORD(wParam) - 4600 >= 0))
        {
            int index = LOWORD(wParam) - 4600;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(1);
        }

        if ((LOWORD(wParam) - 4700 < 100) && (LOWORD(wParam) - 4700 >= 0))
        {
            int index = LOWORD(wParam) - 4700;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(0);
        }

        if ((LOWORD(wParam) - 4800 < 100) && (LOWORD(wParam) - 4800 >= 0))
        {
            int index = LOWORD(wParam) - 4800;
            changed_figure1 = (*copy_memory1)[index];
            changed_figure1->set_brush_style(2);
        }
        if ((LOWORD(wParam) - 3200 < 100) && (LOWORD(wParam) - 3200 >= 0))
        {

            TCHAR a[20];
            int i = LOWORD(wParam) - 3200;
            changed_figure1 = (*copy_memory1)[i];
            COLOR color;
            GetWindowText(table_vector[i]->edit1, a, 9);
            color.R = _wtoi(a);
            GetWindowText(table_vector[i]->edit2, a, 9);
            color.G = _wtoi(a);
            GetWindowText(table_vector[i]->edit3, a, 9);
            color.B = _wtoi(a);
            changed_figure1->set_color(color, parent_hWnd1);

            GetWindowText(table_vector[i]->edit4, a, 9);
            color.R = _wtoi(a);
            GetWindowText(table_vector[i]->edit5, a, 9);
            color.G = _wtoi(a);
            GetWindowText(table_vector[i]->edit6, a, 9);
            color.B = _wtoi(a);
            changed_figure1->set_border_color(color, parent_hWnd1);

            GetWindowText(table_vector[i]->edit7, a, 9);
            int x = _wtoi(a);
            GetWindowText(table_vector[i]->edit8, a, 9);
            int y = _wtoi(a);
            changed_figure1->update(parent_hWnd1, x, y);

            GetWindowText(table_vector[i]->edit9, a, 9);
            changed_figure1->set_pen_size(_wtoi(a));

            GetWindowText(table_vector[i]->edit10, a, 20);
            std::wstring name = a;
            std::wstring copy_name = changed_figure1->get_name();
            changed_figure1->set_name(name);

            if (copy_memory1->check_name(name))
            {
                GetWindowText(table_vector[i]->edit11, a, 9);
                int new_id = _wtoi(a);
                int copy_id = changed_figure1->get_id();


                if (new_id == copy_id)
                {

                    InvalidateRect(parent_hWnd1, NULL, FALSE);

                }
                else if (copy_memory1->check_id(new_id))
                {
                    copy_memory1->del(copy_id);
                    changed_figure1->stop_select();
                    changed_figure1->set_id(new_id);
                    copy_memory1->add(changed_figure1, new_id);

                    InvalidateRect(parent_hWnd1, NULL, FALSE);
                }
                else
                {
                    SetWindowText(table_vector[i]->edit11, (LPCWSTR)L"wrong id");
                }

            }
            else
            {
                changed_figure1->set_name(copy_name);
                SetWindowText(table_vector[i]->edit10, (LPCWSTR)L"wrong name");

            }
        }
        if ((LOWORD(wParam) - 3300 < 100) && (LOWORD(wParam) - 3300 >= 0))
        {
            int i = LOWORD(wParam) - 3300;
            changed_figure1 = (*copy_memory1)[i];
            copy_memory1->del(changed_figure1->get_id());

            TableRow* a = table_vector[i];
            table_vector.erase(table_vector.begin() + i);
            delete a;
            UpdateWindow(hWnd);
            InvalidateRect(hWnd, NULL, true);
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

TableInfoWindow::TableInfoWindow(HINSTANCE hInstance, HWND hWnd, FigureMemory* mem)
{
    copy_memory1 = mem;
    parent_hWnd1 = hWnd;
    hInst = hInstance;

    WNDCLASS wi;
    memset(&wi, 0, sizeof(WNDCLASS));
    wi.lpfnWndProc = TableProc;
    wi.hInstance = hInstance;
    wi.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wi.lpszClassName = L"ChildTabloW";
    wi.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wi);

    RECT rect;
    GetClientRect(hWnd, &rect);
    POINT pt;
    pt.x = 0;
    pt.y = 0;
    //ClientToScreen(hWnd,&pt);
    HWND child;

    child = CreateWindowEx( 
        0,
        L"ChildTabloW",
        (LPCTSTR)NULL,
         WS_CHILD | WS_BORDER | WS_VISIBLE ,
        pt.x, pt.y,
        rect.right, rect.bottom,
        hWnd,
        NULL,
        hInstance,
        NULL);
    hInfoSubWnd = child;

    for (int i = 0; i < mem->size(); i++)
    {
        TableRow* row = new TableRow(hInstance, child, (*mem)[i], i);
        table_vector.push_back(row);
    }

}
TableInfoWindow::~TableInfoWindow()
{

}
HWND TableInfoWindow::get_window()
{
    return hInfoSubWnd;
}

TableRow::TableRow(HINSTANCE hInstance, HWND hWnd, Figure* figure, int index)
{
    this->figure = figure;
    y = 2 + index * 23;
    edit10 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 40, y, 125, 20, hWnd, 0, hInstance, 0);
    SetWindowText(edit10, (LPCWSTR)figure->get_name().c_str());

    edit11 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 185, y, 55, 20, hWnd, 0, hInstance, 0);
    SetWindowText(edit11, (LPCWSTR)std::to_wstring(figure->get_id()).c_str());

    if (figure->get_type() != L"arrow")
    {
        edit1 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 295, y, 30, 20, hWnd, 0, hInstance, 0);
        SetWindowText(edit1, (LPCWSTR)std::to_wstring(figure->get_color().R).c_str());

        edit2 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 345, y, 30, 20, hWnd, 0, hInstance, 0);
        SetWindowText(edit2, (LPCWSTR)std::to_wstring(figure->get_color().G).c_str());

        edit3 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 395, y, 30, 20, hWnd, 0, hInstance, 0);
        SetWindowText(edit3, (LPCWSTR)std::to_wstring(figure->get_color().B).c_str());
    }
    edit4 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 467, y, 30, 20, hWnd, 0, hInstance, 0);
    SetWindowText(edit4, (LPCWSTR)std::to_wstring(figure->get_border_color().R).c_str());

    edit5 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 517, y, 30, 20, hWnd, 0, hInstance, 0);
    SetWindowText(edit5, (LPCWSTR)std::to_wstring(figure->get_border_color().G).c_str());

    edit6 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 567, y, 30, 20, hWnd, 0, hInstance, 0);
    SetWindowText(edit6, (LPCWSTR)std::to_wstring(figure->get_border_color().B).c_str());

    if (figure->get_type() != L"arrow")
    {
        edit7 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 617, y, 30, 20, hWnd, 0, hInstance, 0);
        SetWindowText(edit7, (LPCWSTR)std::to_wstring(figure->get_center().x).c_str());


        edit8 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 665, y, 30, 20, hWnd, 0, hInstance, 0);
        SetWindowText(edit8, (LPCWSTR)std::to_wstring(figure->get_center().y).c_str());
    }

    edit9 = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 745, y, 30, 20, hWnd, 0, hInstance, 0);
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
    if(figure->get_type()!=L"arrow")
    brush_style_buttom = CreateWindow(L"BUTTON", buttom_brush_name, WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        780,         // starting x position 
        y,         // starting y position 
        125,        // button width 
        20,        // button height 
        hWnd,
        (HMENU)(3000 + index),
        hInstance,
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

        905,         // starting x position 
        y,         // starting y position 
        125,        // button width 
        20,        // button height 
        hWnd,
        (HMENU)(3100 + index),
        hInstance,
        NULL);


    ok_buttom = CreateWindow(L"BUTTON", L"Apply", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        1030,         // starting x position 
        y,         // starting y position 
        45,        // button width 
        20,        // button height 
        hWnd,
        (HMENU)(3200 + index),
        hInstance,
        NULL);


    del_buttom = CreateWindow(L"BUTTON", L"Del", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

        1075,         // starting x position 
        y,         // starting y position 
        30,        // button width 
        20,        // button height 
        hWnd,
        (HMENU)(3300 + index),
        hInstance,
        NULL);


    ShowWindow(hWnd, SW_NORMAL);
    UpdateWindow(hWnd);

    PAINTSTRUCT ps;

    HDC dc = GetDC(hWnd);
   

}
void TableRow::draw(HDC dc)
{
    HFONT font = CreateFont(16, 5, 0, 0, 3, 3, 4, 0, 0, 0, 0, 0, 0, L"Arial");
    SelectObject(dc, font);

    HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    SelectObject(dc, pen);


    TextOutW(dc, 2, y, L"Name", lstrlen(L"Name"));
    TextOutW(dc, 167, y, L"Id", lstrlen(L"Id"));

    if (figure->get_type() != L"arrow")
    {
        TextOutW(dc, 245, y, L"Brush:", lstrlen(L"Brush:"));
        TextOutW(dc, 278, y, L"R:", lstrlen(L"R:"));
        TextOutW(dc, 328, y, L"G:", lstrlen(L"G:"));
        TextOutW(dc, 378, y, L"B:", lstrlen(L"B:"));
    }

    TextOutW(dc, 426, y, L"Pen:", lstrlen(L"Pen:"));
    TextOutW(dc, 450, y, L"R:", lstrlen(L"R:"));
    TextOutW(dc, 500, y, L"G:", lstrlen(L"G:"));
    TextOutW(dc, 550, y, L"B:", lstrlen(L"B:"));

    if (figure->get_type() != L"arrow")
    {
        TextOutW(dc, 600, y, L"X:", lstrlen(L"X:"));
        TextOutW(dc, 650, y, L"Y:", lstrlen(L"Y:"));
    }

    TextOutW(dc, 700, y, L"Pen size", lstrlen(L"Pen size"));
}

TableRow::~TableRow()
{
   

    DestroyWindow(edit1);
    DestroyWindow(edit2);
    DestroyWindow(edit3);
    DestroyWindow(edit4);
    DestroyWindow(edit5);
    DestroyWindow(edit6);
    DestroyWindow(edit7);
    DestroyWindow(edit8);
    DestroyWindow(edit9);
    DestroyWindow(edit10);
    DestroyWindow(edit11);

    DestroyWindow(ok_buttom);
    DestroyWindow(del_buttom);
    DestroyWindow(brush_style_buttom);
    DestroyWindow(pen_style_buttom);
}