#include "models.h"
#include <fstream>
#include <vector>
#include <algorithm>


bool comparator_max_min(double* a, double* b)
{
    return *a > *b;
}


bool comparator_min_max(double* a, double* b)
{
    return *a < *b;
}

Figure::Figure(){}

Figure::Figure(HDC hDC, int x, int y, int width,int height, COLOR color, COLOR border_color)
{
    cords_x = new double[4];
    cords_y = new double[4];

    start_cords_x = new double[4];
    start_cords_y = new double[4];

    this->color.R = color.R;
    this->color.G = color.G;
    this->color.B = color.B;

    this->border_color.R = border_color.R;
    this->border_color.G = border_color.G;
    this->border_color.B = border_color.B;
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

    HPEN pen = CreatePen(PS_SOLID,2,RGB(border_color.R, border_color.G, border_color.B));
    SelectObject(hDC, brush);
    SelectObject(hDC, pen);
   
    BeginPath(hDC);

    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
    for(int i =1; i< _msize(cords_x) / sizeof(cords_x[0]);i++)
        LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
    LineTo(hDC, round(cords_x[0]), round(cords_y[0]));

    EndPath(hDC);
    FillPath(hDC);

    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
   for(int i =1; i< _msize(cords_x) / sizeof(cords_x[0]);i++)
        LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
    LineTo(hDC, round(cords_x[0]), round(cords_y[0]));

    if(select_flag)
        draw_borders(hDC);
    DeleteObject(brush);
    DeleteObject(pen);
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
    calculate_rotation();
   

    

    //InvalidateRect(hWnd, &rc, TRUE);
}

void Figure::calculate_rotation()
{
    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
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
            b += 3.14 * 3 / 2;
        }
        else if (relative_x > 0 && relative_y >= 0)
            b = rotate_angle + atan(abs(double(relative_y) / double(relative_x)));


        relative_x = p * cos(b);
        relative_y = p * sin(b);

        cords_x[i] = center.x + relative_x;
        cords_y[i] = center.y + relative_y;
    }

    int max_x = cords_x[0], min_x = cords_x[0], max_y = cords_y[0], min_y = cords_y[0];

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
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

    update_cords_x[0] = min_x - half_side;
    update_cords_y[0] = min_y - half_side;

    update_cords_x[1] = max_x + half_side;
    update_cords_y[1] = min_y - half_side;

    update_cords_x[2] = max_x + half_side;
    update_cords_y[2] = max_y + half_side;

    update_cords_x[3] = min_x - half_side;
    update_cords_y[3] = max_y + half_side;
    prev.x = pt.x;
    prev.y = pt.y;
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
    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        cords_x[i] -= x;
        cords_y[i] -= y;

        start_cords_x[i] -= x;
        start_cords_y[i] -= y;
    }

    for (int i = 0; i < 4; i++)
    {
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
    
    std::vector<double*> up_x_cords;
    std::vector<double*> down_x_cords;

    std::vector<double*> left_y_cords;
    std::vector<double*> right_y_cords;

    std::vector<double*> start_up_x_cords;
    std::vector<double*> start_down_x_cords;

    std::vector<double*> start_left_y_cords;
    std::vector<double*> start_right_y_cords;

    for (int i = 0; i < _msize(cords_x)/sizeof(cords_x[0]); i++)
    {
        if (cords_y[i] - center.y > 0)
        {
            down_x_cords.push_back(&cords_x[i]);
            start_down_x_cords.push_back(&start_cords_x[i]);
        }
        else
        {
            up_x_cords.push_back(&cords_x[i]);
            start_up_x_cords.push_back(&start_cords_x[i]);
        }
    }

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        if (cords_x[i] - center.x > 0)
        {
            right_y_cords.push_back(&cords_y[i]);
            start_right_y_cords.push_back(&start_cords_y[i]);
        }
        else
        {
            left_y_cords.push_back(&cords_y[i]);
            start_left_y_cords.push_back(&start_cords_y[i]);
        }
    }


    switch (resize_index)
    {
   
    case 0:
    {     
        std::sort(down_x_cords.begin(), down_x_cords.end(), comparator_max_min);
        std::sort(up_x_cords.begin(), up_x_cords.end(), comparator_max_min);
        double need_point;
        if (*down_x_cords[0] < *up_x_cords[0])
            need_point = *down_x_cords[0];
        else
            need_point = *up_x_cords[0];
        if (abs(need_point - update_cords_x[0]) > 10 | delta_x < 0)
        {
            std::sort(start_down_x_cords.begin(), start_down_x_cords.end(), comparator_max_min);
            std::sort(start_up_x_cords.begin(), start_up_x_cords.end(), comparator_max_min);

           

            update_cords_x[0] += delta_x;
            update_cords_x[3] += delta_x;

            if(delta_x % 2==0)
                center.x += delta_x / 2;
            else
            {
                center.x += (delta_x + center_control_x) / 2;
                center_control_x *= -1;
            }

            double new_delta_up_x = double(delta_x) / (up_x_cords.size() - 1);
            for (int i = 1; i < up_x_cords.size(); i++)
            {
                *(up_x_cords[i]) += new_delta_up_x * i;
                *(start_up_x_cords[i]) += new_delta_up_x * i;

            }

            double new_delta_down_x = double(delta_x) / (down_x_cords.size() - 1);
            for (int i = 1; i < down_x_cords.size(); i++)
            {
                *(down_x_cords[i]) += new_delta_down_x * i;
                *(start_down_x_cords[i]) += new_delta_down_x * i;
            }

        }
        break;
    }
    case 1:
    {   
        std::sort(down_x_cords.begin(), down_x_cords.end(), comparator_min_max);
        std::sort(up_x_cords.begin(), up_x_cords.end(), comparator_min_max);
        double need_point;
        if (*down_x_cords[0] > *up_x_cords[0])
            need_point = *down_x_cords[0];
        else
            need_point = *up_x_cords[0];
        if (abs(need_point- update_cords_x[1]) > 10 | delta_x > 0)
        {
            std::sort(start_down_x_cords.begin(), start_down_x_cords.end(), comparator_min_max);
            std::sort(start_up_x_cords.begin(), start_up_x_cords.end(), comparator_min_max);

            update_cords_x[2] += delta_x;
            update_cords_x[1] += delta_x;

            if (delta_x % 2 == 0)
                center.x += delta_x / 2;
            else
            {
                center.x += (delta_x + center_control_x) / 2;
                center_control_x *= -1;
            }


            double new_delta_up_x = double(delta_x) / (up_x_cords.size() - 1);
            for (int i = 1; i < up_x_cords.size(); i++)
            {
                *(up_x_cords[i]) += new_delta_up_x * i;
                *(start_up_x_cords[i]) += new_delta_up_x * i;
            }


            double new_delta_down_x = double(delta_x) / (down_x_cords.size() - 1);
            for (int i = 1; i < down_x_cords.size(); i++)
            {
                *(down_x_cords[i]) += new_delta_down_x * i;
                *(start_down_x_cords[i]) += new_delta_down_x * i;

            }
        }
        break;
    }
    case 2:
    {
        std::sort(left_y_cords.begin(), left_y_cords.end(), comparator_max_min);
        std::sort(right_y_cords.begin(), right_y_cords.end(), comparator_max_min);

        double need_point;
        if (*left_y_cords[0] < *right_y_cords[0])
            need_point = *left_y_cords[0];
        else
            need_point = *right_y_cords[0];
        if (abs(need_point - update_cords_y[0]) > 10| delta_y < 0)
        {

            std::sort(start_left_y_cords.begin(), start_left_y_cords.end(), comparator_max_min);
            std::sort(start_right_y_cords.begin(), start_right_y_cords.end(), comparator_max_min);


            

            update_cords_y[0] += delta_y;
            update_cords_y[1] += delta_y;

            if (delta_y % 2 == 0)
                center.y += delta_y / 2;
            else
            {
                center.y += (delta_y + center_control_y) / 2;
                center_control_y *= -1;
            }


            double new_delta_left_y = double(delta_y) / (left_y_cords.size() - 1);
            for (int i = 1; i < left_y_cords.size(); i++)
            {
                *(left_y_cords[i]) += new_delta_left_y * i;
                *(start_left_y_cords[i]) += new_delta_left_y * i;
            }


            double new_delta_right_y = double(delta_y) / (right_y_cords.size() - 1);
            for (int i = 1; i < right_y_cords.size(); i++)
            {
                *(right_y_cords[i]) += new_delta_right_y * i;
                *(start_right_y_cords[i]) += new_delta_right_y * i;
            }
        }
        break;
    }
    case 3:
    {

        std::sort(left_y_cords.begin(), left_y_cords.end(), comparator_min_max);
        std::sort(right_y_cords.begin(), right_y_cords.end(), comparator_min_max);

        double need_point;
        if (*left_y_cords[0] > *right_y_cords[0])
            need_point = *left_y_cords[0];
        else
            need_point = *right_y_cords[0];

        if (abs(need_point - update_cords_y[2]) > 14 | delta_y > 0)
        {

            std::sort(start_left_y_cords.begin(), start_left_y_cords.end(), comparator_min_max);
            std::sort(start_right_y_cords.begin(), start_right_y_cords.end(), comparator_min_max);


            update_cords_y[2] += delta_y;
            update_cords_y[3] += delta_y;

            if (delta_y % 2 == 0)
                center.y += delta_y / 2;
            else
            {
                center.y += (delta_y + center_control_y) / 2;
                center_control_y *= -1;
            }


            double new_delta_left_y = double(delta_y) / (left_y_cords.size() - 1);
            for (int i = 1; i < left_y_cords.size(); i++)
            {
                *(left_y_cords[i]) += new_delta_left_y * i;
                *(start_left_y_cords[i]) += new_delta_left_y * i;
            }


            double new_delta_right_y = double(delta_y) / (right_y_cords.size() - 1);
            for (int i = 1; i < right_y_cords.size(); i++)
            {
                *(right_y_cords[i]) += new_delta_right_y * i;
                *(start_right_y_cords[i]) += new_delta_right_y * i;
            }
        }

        break;
    }
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
    rotate_angle = 0;

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        start_cords_x[i] = cords_x[i];
        start_cords_y[i] = cords_y[i];
    }
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

void Figure::set_border_color(COLOR color, HWND hWnd)
{
    this->border_color.R = color.R;
    this->border_color.G = color.G;
    this->border_color.B = color.B;
    init(hWnd);
}


Elipse::Elipse(HDC hDC, int x, int y, int width, int height, COLOR color, COLOR border_color)
{
    this->height = height;
    this->width = width;

    cords_x = new double[96];
    cords_y = new double[96];

    start_cords_x = new double[96];
    start_cords_y = new double[96];

    this->color.R = color.R;
    this->color.G = color.G;
    this->color.B = color.B;

    this->border_color.R = border_color.R;
    this->border_color.G = border_color.G;
    this->border_color.B = border_color.B;
    
    center.x = x + int(width / 2);
    center.y = y + int(height / 2);
    
  
    calculate_cords();

    update_cords_x[0] = x - half_side;
    update_cords_y[0] = y - half_side;

    update_cords_x[1] = x + width + half_side;
    update_cords_y[1] = y - half_side;

    update_cords_x[2] = x + width + half_side;
    update_cords_y[2] = y + height + half_side;

    update_cords_x[3] = x - half_side;
    update_cords_y[3] = y + height + half_side;

    prev.x = x;
    prev.y = y;

    

}

void Elipse::calculate_cords()
{
    int size = _msize(cords_x) / sizeof(cords_x[0]);
    double delta = double(width / 6) / (size / 8);
    double delta_x = center.x;
    double delta_y = center.y;
    double delta_sum = 0;

    for (int i = 1; i < size / 8; i++)
    {
        delta_sum += delta;
        cords_x[i] = (-width) / 2 + delta_sum;
        start_cords_x[i] = (-width) / 2 + delta_sum;

        cords_x[size - i] = (-width) / 2 + delta_sum;
        start_cords_x[size - i] = (-width) / 2 + delta_sum;

        cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_x[i] += delta_x;
        start_cords_x[i] += delta_x;

        cords_x[size - i] += delta_x;
        start_cords_x[size - i] += delta_x;

    }
    delta = double((width / 3) * 2) / (size / 4);
    for (int i = size / 8; i < size / 8 + size / 4; i++)
    {
        delta_sum += delta;

        cords_x[i] = (-width) / 2 + delta_sum;
        start_cords_x[i] = (-width) / 2 + delta_sum;

        cords_x[size - i] = (-width) / 2 + delta_sum;
        start_cords_x[size - i] = (-width) / 2 + delta_sum;

        cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_x[i] += delta_x;
        start_cords_x[i] += delta_x;

        cords_x[size - i] += delta_x;
        start_cords_x[size - i] += delta_x;

    }

    delta = double(width / 6) / (size / 8);
    for (int i = size / 8 + size / 4; i < size / 2; i++)
    {
        delta_sum += delta;

        cords_x[i] = (-width) / 2 + delta_sum;
        start_cords_x[i] = (-width) / 2 + delta_sum;

        cords_x[size - i] = (-width) / 2 + delta_sum;
        start_cords_x[size - i] = (-width) / 2 + delta_sum;

        cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));
        start_cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

        cords_x[i] += delta_x;
        start_cords_x[i] += delta_x;

        cords_x[size - i] += delta_x;
        start_cords_x[size - i] += delta_x;

    }


    cords_x[0] = -width / 2;
    start_cords_x[0] = -width / 2;

    cords_y[0] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[0], 2)));
    start_cords_y[0] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[0], 2)));

    cords_x[0] += delta_x;
    start_cords_x[0] += delta_x;


    cords_x[size / 2] = width / 2;
    start_cords_x[size / 2] = width / 2;

    cords_y[size / 2] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[size / 2], 2)));
    start_cords_y[size / 2] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[size / 2], 2)));


    cords_x[size / 2] += delta_x;
    start_cords_x[size / 2] += delta_x;
}

void  Elipse::resize(HWND hWnd)
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
    {
        update_cords_x[0] += delta_x;
        update_cords_x[3] += delta_x;

        width -= delta_x;

        if (delta_x % 2 == 0)
            center.x += delta_x / 2;
        else
        {
            center.x += (delta_x + center_control_x) / 2;
            center_control_x *= -1;
        }
        break;
    }
    case 1:
    {
        update_cords_x[2] += delta_x;
        update_cords_x[1] += delta_x;

        width += delta_x;
        if (delta_x % 2 == 0)
            center.x += delta_x / 2;
        else
        {
            center.x += (delta_x + center_control_x) / 2;
            center_control_x *= -1;
        }
        break;
    }
    case 2:
    {
        update_cords_y[0] += delta_y;
        update_cords_y[1] += delta_y;

        height -= delta_y;
        if (delta_y % 2 == 0)
            center.y += delta_y / 2;
        else
        {
            center.y += (delta_y + center_control_y) / 2;
            center_control_y *= -1;
        }
        break;
    }
    case 3:
    {
        update_cords_y[2] += delta_y;
        update_cords_y[3] += delta_y;

        height += delta_y;
        if (delta_y % 2 == 0)
            center.y += delta_y / 2;
        else
        {
            center.y += (delta_y + center_control_y) / 2;
            center_control_y *= -1;
        }
        break;
    }

    }
    calculate_cords();
    if(rotate_angle!=0)
        calculate_rotation();
}

void  Elipse::stop_resize()
{
    resize_flag = false;
    resize_index = -1;
}

Triangle::Triangle(HDC hDC, int* x, int* y, COLOR color, COLOR border_color)
{
    this->color.R = color.R;
    this->color.G = color.G;
    this->color.B = color.B;

    this->border_color.R = border_color.R;
    this->border_color.G = border_color.G;
    this->border_color.B = border_color.B;
    
    cords_x = new double[3];
    cords_y = new double[3];

    start_cords_x = new double[3];
    start_cords_y = new double[3];

    for(int i = 0; i < 3; i++)
    {
        cords_x[i] = x[i];
        cords_y[i] = y[i];

        start_cords_x[i] = x[i];
        start_cords_y[i] = y[i];
    }

    int max_x = x[0], max_y = y[0], min_x = x[0], min_y = y[0];
    for (int i = 0; i < 3; i++)
    {
        if (max_x < x[i])
            max_x = x[i];
        if (min_x > x[i])
            min_x = x[i];
        if (max_y < y[i])
            max_y = y[i];
        if (min_y > y[i])
            min_y = y[i];
    }
    center.x = min_x + int((max_x-min_x) / 2);
    center.y = min_y + int((max_x-min_x) / 2);

    update_cords_x[0] = min_x - half_side;
    update_cords_y[0] = min_y - half_side;

    update_cords_x[1] = max_x + width + half_side;
    update_cords_y[1] = min_y - half_side;

    update_cords_x[2] = max_x + width + half_side;
    update_cords_y[2] = max_y + height + half_side;

    update_cords_x[3] = min_x - half_side;
    update_cords_y[3] = max_y + height + half_side;

    prev.x = min_x;
    prev.y = min_y;
}

void Triangle::resize(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    int delta_x = pt.x - prev.x;
    int delta_y = pt.y - prev.y;

    SetRect(&rc, update_cords_x[0] - 1, update_cords_y[0] - 1, update_cords_x[2] + 1, update_cords_y[2] + 1);
    InvalidateRect(hWnd, &rc, TRUE);
    int index_min_x=0;
    int index_max_x=0;
    int index_min_y=0;
    int index_max_y=0;

    switch (resize_index)
    {

    case 0:
    {
        update_cords_x[0] += delta_x;
        update_cords_x[3] += delta_x;

        for (int i = 0; i < 3; i++)
            if (cords_x[index_max_x] < cords_x[i])
                index_max_x = i;
        for (int i = 0; i < 3; i++)
        {
            if (i == index_max_x)
                continue;
            cords_x[i] += delta_x;
            start_cords_x[i] += delta_x;
        }

        if (delta_x % 2 == 0)
            center.x += delta_x / 2;
        else
        {
            center.x += (delta_x + center_control_x) / 2;
            center_control_x *= -1;
        }
        break;
    }
    case 1:
    {
        update_cords_x[2] += delta_x;
        update_cords_x[1] += delta_x;

        for (int i = 0; i < 3; i++)
            if (cords_x[index_min_x] > cords_x[i])
                index_min_x = i;
        for (int i = 0; i < 3; i++)
        {
            if (i == index_min_x)
                continue;
            cords_x[i] += delta_x;
            start_cords_x[i] += delta_x;
        }

        if (delta_x % 2 == 0)
            center.x += delta_x / 2;
        else
        {
            center.x += (delta_x + center_control_x) / 2;
            center_control_x *= -1;
        }
        break;
    }
    case 2:
    {
        update_cords_y[0] += delta_y;
        update_cords_y[1] += delta_y;

        for (int i = 0; i < 3; i++)
            if (cords_y[index_max_y] < cords_y[i])
                index_max_y = i;
        for (int i = 0; i < 3; i++)
        {
            if (i == index_max_y)
                continue;
            cords_y[i] += delta_y;
            start_cords_y[i] += delta_y;
        }

        if (delta_y % 2 == 0)
            center.y += delta_y / 2;
        else
        {
            center.y += (delta_y + center_control_y) / 2;
            center_control_y *= -1;
        }
        break;
    }
    case 3:
    {
        update_cords_y[2] += delta_y;
        update_cords_y[3] += delta_y;

        for (int i = 0; i < 3; i++)
            if (cords_y[index_min_y] > cords_y[i])
                index_min_y = i;
        for (int i = 0; i < 3; i++)
        {
            if (i == index_min_y)
                continue;
            cords_y[i] += delta_y;
            start_cords_y[i] += delta_y;
        }

        if (delta_y % 2 == 0)
            center.y += delta_y / 2;
        else
        {
            center.y += (delta_y + center_control_y) / 2;
            center_control_y *= -1;
        }
        break;
    }

    }
}

/*std::ofstream fout("log.txt", std::ios::app);
    fout << pos.x<<" "<< prev.x<<" "<< pt.x<<" "<< delta.x<<"\n";
    fout.close();*/