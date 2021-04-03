#include "interface.h"

Interface::Interface()
{

}
Interface::~Interface()
{

}

void Interface::draw(HWND hWnd)
{
    RECT rect;
    GetWindowRect(hWnd, &rect);
    int start_x = (rect.right - rect.left) / 7 * 4-2;
    int start_y = 3;

    HDC dc = GetDC(hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
    HPEN old_pen=(HPEN)SelectObject(dc, pen);

    MoveToEx(dc, start_x, start_y, nullptr);
    LineTo(dc, start_x+207, start_y );
    LineTo(dc, start_x+207, start_y + 46);
    LineTo(dc, start_x, start_y + 46);
    LineTo(dc, start_x, start_y );

    MoveToEx(dc, start_x, start_y+23, nullptr);
    LineTo(dc, start_x + 207, start_y+23);

    for (int i = 23; i < 207; i += 23)
    {
        MoveToEx(dc, start_x + i, start_y, nullptr);
        LineTo(dc, start_x + i, start_y + 46);
    }

    RECT rc;
    HBRUSH brush = CreateSolidBrush(RGB(101, 200, 255));
    if (pen_or_brush)
        SetRect(&rc, start_x - 52, start_y-3, start_x - 4, start_y + 65);
    else
        SetRect(&rc, start_x - 102, start_y-3, start_x - 54, start_y + 65);
    SelectObject(dc, brush);

    FillRect(dc, &rc, brush);
    DeleteObject(brush);

    MoveToEx(dc, start_x -50, start_y, nullptr);

    LineTo(dc, start_x - 7, start_y);
    LineTo(dc, start_x - 7, start_y + 43);
    LineTo(dc, start_x - 50 , start_y + 43);
    LineTo(dc, start_x - 50, start_y);


    MoveToEx(dc, start_x - 100, start_y, nullptr);

    LineTo(dc, start_x - 57, start_y);
    LineTo(dc, start_x - 57, start_y + 43);
    LineTo(dc, start_x - 100, start_y + 43);
    LineTo(dc, start_x - 100, start_y);

    HFONT font = CreateFont(13, 5, 0, 0, 3, 3, 4, 0, 0,0,0,0,0,L"Arial");
    SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    TextOutW(dc, start_x - 47, start_y + 48, L"Заливка", lstrlen(L"Заливка"));
    TextOutW(dc, start_x - 94, start_y + 48, L"Рамка", lstrlen(L"Рамка"));
    TextOutW(dc, start_x + 90, start_y + 48, L"Цвет", lstrlen(L"Цвет"));




    SelectObject(dc, old_pen);
    DeleteObject(pen);
}

void Interface::set_pen()
{
    pen_or_brush = false;
}
void Interface::set_brush()
{
    pen_or_brush = true;
}

