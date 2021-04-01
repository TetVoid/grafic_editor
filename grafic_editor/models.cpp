#include "models.h"
#include <fstream>
#include <string>

Figure::Figure(){}

Figure::Figure(HDC hDC, int x, int y, int width,int height, COLOR color)
{

    this->color.R = color.R;
    this->color.G = color.G;
    this->color.B = color.B;
    cords_x[0] = x;
    cords_y[0] = y;

    cords_x[1] = x + width;
    cords_y[1] = y;

    cords_x[2] = x + width;
    cords_y[2] = y + height;

    cords_x[3] = x;
    cords_y[3] = y + height;

    start_cords_x[0] = x;
    start_cords_y[0] = y;

    start_cords_x[1] = x + width;
    start_cords_y[1] = y;

    start_cords_x[2] = x + width;
    start_cords_y[2] = y + height;

    start_cords_x[3] = x;
    start_cords_y[3] = y + height;

    update_cords_x[0] = x-half_side;
    update_cords_y[0] = y-half_side;

    update_cords_x[1] = x + width+half_side;
    update_cords_y[1] = y-half_side;

    update_cords_x[2] = x + width+half_side;
    update_cords_y[2] = y + height+half_side;

    update_cords_x[3] = x-half_side;
    update_cords_y[3] = y + height+half_side;

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
    HBRUSH brush = CreateSolidBrush(RGB(color.R, color.G, color.B));
    SelectObject(hDC, brush);
   
    BeginPath(hDC);
    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
    LineTo(hDC, round(cords_x[1]), round(cords_y[1]));
    LineTo(hDC, round(cords_x[2]), round(cords_y[2]));
    LineTo(hDC, round(cords_x[3]), round(cords_y[3]));
    LineTo(hDC, round(cords_x[0]), round(cords_y[0]));
    EndPath(hDC);
    FillPath(hDC);

    if(select_flag)
        draw_borders(hDC);
    DeleteObject(brush);
}

void Figure::draw_borders(HDC hDC)
{
    RECT rc;
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    SetRect(&rc, update_cords_x[0], update_cords_y[0], update_cords_x[0] + half_side+half_side, update_cords_y[0] +half_side);
    FillRect(hDC, &rc, brush);
    SetRect(&rc, update_cords_x[0], update_cords_y[0], update_cords_x[0] + half_side , update_cords_y[0] + half_side + half_side);
    FillRect(hDC, &rc, brush);

    SetRect(&rc, update_cords_x[1]-half_side-half_side, update_cords_y[1], update_cords_x[1], update_cords_y[1] + half_side);
    FillRect(hDC, &rc, brush);
    SetRect(&rc, update_cords_x[1]-half_side, update_cords_y[1], update_cords_x[1], update_cords_y[1] + half_side + half_side);
    FillRect(hDC, &rc, brush);

    SetRect(&rc, update_cords_x[2], update_cords_y[2], update_cords_x[2] - half_side - half_side, update_cords_y[2] - half_side);
    FillRect(hDC, &rc, brush);
    SetRect(&rc, update_cords_x[2], update_cords_y[2], update_cords_x[2] - half_side, update_cords_y[2] - half_side - half_side);
    FillRect(hDC, &rc, brush);

    SetRect(&rc, update_cords_x[3] + half_side + half_side, update_cords_y[3], update_cords_x[3], update_cords_y[3] - half_side);
    FillRect(hDC, &rc, brush);
    SetRect(&rc, update_cords_x[3] + half_side, update_cords_y[3], update_cords_x[3], update_cords_y[3] - half_side - half_side);
    FillRect(hDC, &rc, brush);

    int start_x = update_cords_x[3];
    int start_y = (update_cords_y[3] + update_cords_y[0]) / 2 - half_side - half_side;
    int finish_x = update_cords_x[3]+half_side;
    int finish_y = (update_cords_y[3] + update_cords_y[0]) / 2 + half_side + half_side;
    SetRect(&rc, start_x, start_y, finish_x, finish_y);
    FillRect(hDC, &rc, brush);

    start_x = update_cords_x[2]-half_side;
    start_y = (update_cords_y[3] + update_cords_y[0]) / 2 - half_side - half_side;
    finish_x = update_cords_x[2] ;
    finish_y = (update_cords_y[3] + update_cords_y[0]) / 2 + half_side + half_side;
    SetRect(&rc, start_x, start_y, finish_x, finish_y);
    FillRect(hDC, &rc, brush);

    start_x = (update_cords_x[0]+ update_cords_x[1])/2 - half_side - half_side;
    start_y = update_cords_y[0];
    finish_x = (update_cords_x[0] + update_cords_x[1]) / 2 + half_side + half_side;
    finish_y = update_cords_y[0]+half_side;
    SetRect(&rc, start_x, start_y, finish_x, finish_y);
    FillRect(hDC, &rc, brush);

    start_x = (update_cords_x[2] + update_cords_x[3]) / 2 - half_side - half_side;
    start_y = update_cords_y[2] - half_side;
    finish_x = (update_cords_x[2] + update_cords_x[3]) / 2 + half_side + half_side;
    finish_y = update_cords_y[2];
    SetRect(&rc, start_x, start_y, finish_x, finish_y);
    FillRect(hDC, &rc, brush);
    DeleteObject(brush);
}

void Figure::rotate(HWND hWnd)
{
    static int index = 0;
    index++;
    RECT rc;
    SetRect(&rc, update_cords_x[0]-1, update_cords_y[0]-1, update_cords_x[2]+1, update_cords_y[2]+1);
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
    rotate_angle += a;
    for (int i = 0; i < 4; i++)
    {
        double  relative_x = start_cords_x[i] - center.x;
        double  relative_y = start_cords_y[i] - center.y;

        double p = sqrt(relative_x * relative_x + relative_y * relative_y);
        double b = 0.0;

        if (relative_x <= 0 && relative_y > 0)
        {
            b = rotate_angle + atan(abs(double(relative_x) / double(relative_y)));
            b += 3.14 / 2.0;
        }
        else if (relative_x < 0 && relative_y <= 0)
        {
            b = rotate_angle + atan(abs(double(relative_y) / double(relative_x)));
            b += 3.14;
        }
        else if (relative_x >= 0 && relative_y < 0)
        {
            b = rotate_angle + atan(abs(double(relative_x) / double(relative_y)));
            b += 3.14*3/2;
        }
        else if (relative_x > 0 && relative_y >= 0)
            b = rotate_angle + atan(abs(double(relative_y) / double(relative_x)));
       

        relative_x = p * cos(b);
        relative_y = p * sin(b);

        cords_x[i] = center.x + relative_x;
        cords_y[i] = center.y + relative_y;
    }

    int max_x = cords_x[0], min_x = cords_x[0], max_y = cords_y[0], min_y = cords_y[0];

    for (int i = 0; i < 4; i++)
    {
        if (max_x < cords_x[i])
            max_x = cords_x[i];
        if (min_x > cords_x[i])
            min_x = cords_x[i];
        if (max_y < cords_y[i])
            max_y = cords_y[i];
        if (min_y > cords_y[i])
            min_y = cords_y[i];
    }

    update_cords_x[0] = min_x-half_side;
    update_cords_y[0] = min_y-half_side;

    update_cords_x[1] = max_x+half_side;
    update_cords_y[1] = min_y-half_side;

    update_cords_x[2] = max_x+half_side;
    update_cords_y[2] = max_y+half_side;

    update_cords_x[3] = min_x-half_side;
    update_cords_y[3] = max_y+half_side;
    prev.x = pt.x;
    prev.y = pt.y;

    

    //InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::update(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    SetRect(&rc, update_cords_x[0]-1, update_cords_y[0]-1, update_cords_x[2] +1, update_cords_y[2] +1);
    InvalidateRect(hWnd, &rc, TRUE);

    int x = prev.x - pt.x;
    int y = prev.y - pt.y;
    prev.x = pt.x;
    prev.y = pt.y;
    for (int i = 0; i < 4; i++)
    {
        cords_x[i] -= x;
        cords_y[i] -= y;

        start_cords_x[i] -= x;
        start_cords_y[i] -= y;

        update_cords_x[i] -= x;
        update_cords_y[i] -= y;
    }
    
    center.x -= x;
    center.y -= y;

    SetRect(&rc, update_cords_x[0]-1, update_cords_y[0]-1, update_cords_x[2] +1, update_cords_y[2] +1);
    InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::resize(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    int delta_x = pt.x - prev.x;
    int delta_y = pt.y - prev.y;

    SetRect(&rc, update_cords_x[0] - 1, update_cords_y[0] - 1, update_cords_x[2] + 1, update_cords_y[2] + 1);
    InvalidateRect(hWnd, &rc, TRUE);

    switch (resize_index)
    {
        
    case 0:
       
        update_cords_x[0] += delta_x;
        update_cords_x[3] += delta_x;

        center.x += delta_x / 2;

        start_cords_x[0] += delta_x;
        start_cords_x[3] += delta_x;

        cords_x[0] += delta_x;
        cords_x[3] += delta_x;
        break;
    case 1:
        update_cords_x[2] += delta_x;
        update_cords_x[1] += delta_x;

        center.x += delta_x / 2;

        start_cords_x[2] += delta_x;
        start_cords_x[1] += delta_x;

        cords_x[2] += delta_x;
        cords_x[1] += delta_x;
        break;
    case 2:
        update_cords_y[0] += delta_y;
        update_cords_y[1] += delta_y;

        center.y += delta_y / 2;

        start_cords_y[0] += delta_y;
        start_cords_y[1] += delta_y;

        cords_y[0] += delta_y;
        cords_y[1] += delta_y;
        break;
        break;
    case 3:
        update_cords_y[2] += delta_y;
        update_cords_y[3] += delta_y;

        center.y += delta_y / 2;

        start_cords_y[2] += delta_y;
        start_cords_y[3] += delta_y;

        cords_y[2] += delta_y;
        cords_y[3] += delta_y;
        
        break;
    }

    SetRect(&rc, update_cords_x[0] - 1, update_cords_y[0] - 1, update_cords_x[2] + 1, update_cords_y[2] + 1);
    InvalidateRect(hWnd, &rc, TRUE);

}


BOOL Figure::check_position(HWND hWnd)
{
    BOOL flag = false;
    RECT rc[5], resize_rc[4];
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SetRect(&rc[0], update_cords_x[0], update_cords_y[0], update_cords_x[2], update_cords_y[2]);

    SetRect(&rc[1], update_cords_x[0], update_cords_y[0], update_cords_x[0] + half_side + half_side, update_cords_y[0] + half_side + half_side);
    SetRect(&rc[2], update_cords_x[1] - half_side - half_side, update_cords_y[1], update_cords_x[1], update_cords_y[1] + half_side + half_side);
    SetRect(&rc[3], update_cords_x[2] - half_side - half_side, update_cords_y[2] - half_side - half_side, update_cords_x[2], update_cords_y[2]);
    SetRect(&rc[4], update_cords_x[3], update_cords_y[3] - half_side - half_side, update_cords_x[3] + half_side + half_side, update_cords_y[3]);

    int start_x = update_cords_x[3];
    int start_y = (update_cords_y[3] + update_cords_y[0]) / 2 - half_side - half_side;
    int finish_x = update_cords_x[3] + half_side;
    int finish_y = (update_cords_y[3] + update_cords_y[0]) / 2 + half_side + half_side;
    SetRect(&resize_rc[0], start_x, start_y, finish_x, finish_y);

    start_x = update_cords_x[2] - half_side;
    start_y = (update_cords_y[3] + update_cords_y[0]) / 2 - half_side - half_side;
    finish_x = update_cords_x[2];
    finish_y = (update_cords_y[3] + update_cords_y[0]) / 2 + half_side + half_side;
    SetRect(&resize_rc[1], start_x, start_y, finish_x, finish_y);

    start_x = (update_cords_x[0] + update_cords_x[1]) / 2 - half_side - half_side;
    start_y = update_cords_y[0];
    finish_x = (update_cords_x[0] + update_cords_x[1]) / 2 + half_side + half_side;
    finish_y = update_cords_y[0] + half_side;
    SetRect(&resize_rc[2], start_x, start_y, finish_x, finish_y);

    start_x = (update_cords_x[2] + update_cords_x[3]) / 2 - half_side - half_side;
    start_y = update_cords_y[2] - half_side;
    finish_x = (update_cords_x[2] + update_cords_x[3]) / 2 + half_side + half_side;
    finish_y = update_cords_y[2];
    SetRect(&resize_rc[3], start_x, start_y, finish_x, finish_y);

    for (int i = 1; i < 5; i++)
    {
        if (PtInRect(&rc[i], pt)&&select_flag)
        {
            rotate_flag = true;
            flag = true;
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (PtInRect(&resize_rc[i], pt) && select_flag)
        {
            resize_index = i;
            resize_flag = true;
            flag = true;
            break;
        }
    }

    if (PtInRect(&rc[0], pt) && !rotate_flag && !resize_flag)
    {
        if(select_flag)
            move_flag = true;
        flag = true;
    }


    return flag;
}

void Figure::init(HWND hwnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hwnd, &pt);

    SetRect(&rc, update_cords_x[0] - 1, update_cords_y[0] - 1, update_cords_x[2] + 1, update_cords_y[2] + 1);
    InvalidateRect(hwnd, &rc, TRUE);
}

BOOL Figure::select(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SetRect(&rc, update_cords_x[0], update_cords_y[0], update_cords_x[2], update_cords_y[2]);

    if (PtInRect(&rc, pt))
        if (select_flag)
            select_flag = false;
        else
            select_flag = true;

   return select_flag;
}

void Figure::set_prev_cords(HWND hWnd)
{
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    prev.x = pt.x;
    prev.y = pt.y;
}

BOOL Figure::is_selected()
{
    return select_flag;
}

BOOL Figure::is_rotate()
{
    return rotate_flag;
}

BOOL Figure::is_move()
{
    return move_flag;
}

BOOL Figure::is_resize()
{
    return resize_flag;
}

void Figure::stop_move()
{
    move_flag = false;
}

void Figure::stop_rotate()
{
    rotate_flag = false;
}

void Figure::stop_select()
{
    select_flag = false;
}

void Figure::stop_resize()
{
    resize_flag = false;
    resize_index = -1;
}

void Figure::set_color(COLOR color,HWND hWnd)
{
    this->color.R = color.R;
    this->color.G = color.G;
    this->color.B = color.B;
    init(hWnd);
}


/*std::ofstream fout("log.txt", std::ios::app);
    fout << pos.x<<" "<< prev.x<<" "<< pt.x<<" "<< delta.x<<"\n";
    fout.close();*/