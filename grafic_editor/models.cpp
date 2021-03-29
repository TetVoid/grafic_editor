#include "models.h"
#include <fstream>
#include <string>

Figure::Figure(){}

Figure::Figure(HDC hDC, int x, int y, int width,int height)
{
    points[0].x = x;
    points[0].y = y;

    points[1].x = x + width;
    points[1].y = y;

    points[2].x = x + width;
    points[2].y = y + height;

    points[3].x = x;
    points[3].y = y + height;
    prev = points[0];

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
    MoveToEx(hDC, points[0].x, points[0].y, nullptr);
    LineTo(hDC, points[1].x, points[1].y);
    LineTo(hDC, points[2].x, points[2].y);
    LineTo(hDC, points[3].x, points[3].y);
    LineTo(hDC, points[0].x, points[0].y);
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
       

        int  relative_x = points[i].x - center.x;
        int  relative_y = points[i].y - center.y;


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
        {
            b = a + atan(abs(double(relative_y) / double(relative_x)));
        }
       

        relative_x = round(p * cos(b));
        relative_y = round(p * sin(b));

        points[i].x = center.x + relative_x;
        points[i].y = center.y + relative_y;
       
        
        prev.x = pt.x;
        prev.y = pt.y;
    }
    //fout << "\n\n";
    //fout.close();

    

    //InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::update(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SetRect(&rc, points[0].x-1, points[0].y-1, points[2].x +1, points[2].y +1);
    InvalidateRect(hWnd, &rc, TRUE);

    int x = prev.x - pt.x;
    int y = prev.y - pt.y;
    prev.x = pt.x;
    prev.y = pt.y;
    for (int i = 0; i < 4; i++)
    {
        points[i].x -= x;
        points[i].y -= y;
    }
    

    SetRect(&rc, points[0].x-1, points[0].y-1, points[2].x +1, points[2].y +1);
    InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::init(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);

    SetRect(&rc, points[0].x - 1, points[0].y - 1, points[0].x + width + 1, points[0].y + height + 1);
    InvalidateRect(hwnd, &rc, TRUE);
}

BOOL Figure::check_position(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);
    SetRect(&rc, points[0].x, points[0].y, points[0].x + width, points[0].y + height);
    
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