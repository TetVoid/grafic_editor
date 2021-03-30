#include "models.h"
#include <fstream>
#include <string>

Figure::Figure(){}

Figure::Figure(HDC hDC, int x, int y, int width,int height)
{
    cords_x[0] = x;
    cords_y[0] = y;

    cords_x[1] = x + width;
    cords_y[1] = y;

    cords_x[2] = x + width;
    cords_y[2] = y + height;

    cords_x[3] = x;
    cords_y[3] = y + height;

    prev.x = cords_x[0];
    prev.y = cords_y[0];

    this->height = height;
    this->width = width;
    center.x = x + int(width / 2);
    center.y = y + int(height / 2);
}

Figure::~Figure()
{
}

void Figure::draw(HDC hDC)
{
    HBRUSH yBrush;
    yBrush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hDC, yBrush);
   
    BeginPath(hDC);
    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
    LineTo(hDC, round(cords_x[1]), round(cords_y[1]));
    LineTo(hDC, round(cords_x[2]), round(cords_y[2]));
    LineTo(hDC, round(cords_x[3]), round(cords_y[3]));
    LineTo(hDC, round(cords_x[0]), round(cords_y[0]));
    EndPath(hDC);
    FillPath(hDC);
}

void Figure::rotate(HWND hWnd)
{
    static int index = 0;
    index++;
    RECT rc;
    SetRect(&rc, 0, 0, 2000, 2000);
    InvalidateRect(hWnd, &rc, TRUE);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    
    index = 1;
    int height = pt.y - center.y;
    int width = pt.x - center.x;
    double a = atan(abs(double(height)/ double(width)));

    int height_prev = prev.y - center.y;
    int width_prev = prev.x - center.x;
    a -= atan(abs(double(height_prev) / double(width_prev)));
    a = abs(a);

    if (height < 0 && pt.x < prev.x)
        index = -1;
    else if (height > 0 && pt.x > prev.x)
        index = -1;
    else if (width < 0 && pt.y>prev.y)
        index = -1;
    else if (width > 0 && pt.y < prev.y)
        index = -1;

    a = a * index;
    for (int i = 0; i < 4; i++)
    {
        double  relative_x = cords_x[i] - center.x;
        double  relative_y = cords_y[i] - center.y;

        double p = sqrt(relative_x * relative_x + relative_y * relative_y);
        double b = 0.0;

        if (relative_x <= 0 && relative_y > 0)
        {
            b = a + atan(abs(double(relative_x) / double(relative_y)));
            b += 3.14 / 2.0;
        }
        else if (relative_x < 0 && relative_y <= 0)
        {
            b = a + atan(abs(double(relative_y) / double(relative_x)));
            b += 3.14;
        }
        else if (relative_x >= 0 && relative_y < 0)
        {
            b = a + atan(abs(double(relative_x) / double(relative_y)));
            b += 3.14*3/2;
        }
        else if (relative_x > 0 && relative_y >= 0)
            b = a + atan(abs(double(relative_y) / double(relative_x)));
       

        relative_x = p * cos(b);
        relative_y = p * sin(b);

        cords_x[i] = center.x + relative_x;
        cords_y[i] = center.y + relative_y;
       
        
        
    }
    prev.x = pt.x;
    prev.y = pt.y;

    

    //InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::update(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SetRect(&rc, cords_x[0]-1, cords_y[0]-1, cords_x[2] +1, cords_y[2] +1);
    InvalidateRect(hWnd, &rc, TRUE);

    int x = prev.x - pt.x;
    int y = prev.y - pt.y;
    prev.x = pt.x;
    prev.y = pt.y;
    for (int i = 0; i < 4; i++)
    {
        cords_x[i] -= x;
        cords_y[i] -= y;
    }
    

    SetRect(&rc, cords_x[0]-1, cords_y[0]-1, cords_x[2] +1, cords_y[2] +1);
    InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::init(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);

    SetRect(&rc, cords_x[0] - 1, cords_y[0] - 1, cords_x[0] + width + 1, cords_y[0] + height + 1);
    InvalidateRect(hwnd, &rc, TRUE);
}

BOOL Figure::check_position(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    SetRect(&rc, cords_x[0], cords_y[0], cords_x[0] + width, cords_y[0] + height);
    
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