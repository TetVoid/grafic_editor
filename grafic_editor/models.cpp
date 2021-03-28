#include "models.h"
#include <fstream>
#include <string>

Figure::Figure(){}

Figure::Figure(HDC hDC, int x, int y, int width,int height)
{
    pos.x = x;
    pos.y = y;
    prev = pos;

    this->height = height;
    this->width = width;
}

Figure::~Figure()
{

}

void Figure::draw(HDC hDC)
{
    RECT r;
    r.left = pos.x;
    r.top = pos.y;
    r.right = pos.x + width;
    r.bottom = pos.y + height;
    FillRect(hDC, &r, (HBRUSH)CreateSolidBrush(RGB(255, 0, 0)));

}

void Figure::update(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SetRect(&rc, pos.x-1, pos.y-1, pos.x + width+1, pos.y + height+1);
    InvalidateRect(hWnd, &rc, TRUE);

    int x = pos.x - prev.x + pt.x;
    int y = pos.y - prev.y + pt.y;
    prev.x = pt.x;
    prev.y = pt.y;
    pos.x = x;
    pos.y = y;

    SetRect(&rc, pos.x-1, pos.y-1, pos.x + width+1, pos.y + height+1);
    InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::init(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);

    SetRect(&rc, pos.x - 1, pos.y - 1, pos.x + width + 1, pos.y + height + 1);
    InvalidateRect(hwnd, &rc, TRUE);
}

BOOL Figure::check_position(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    SetRect(&rc, pos.x, pos.y, pos.x + width, pos.y + height);
    
    if (PtInRect(&rc, pt)) 
    {
        move = true;
        prev = pt;
      
        return true;
    }
}

BOOL  Figure::is_move()
{
    return move;
}
void Figure::set_move(BOOL condition)
{
    move = condition;
}



/*std::ofstream fout("log.txt", std::ios::app);
    fout << pos.x<<" "<< prev.x<<" "<< pt.x<<" "<< delta.x<<"\n";
    fout.close();*/