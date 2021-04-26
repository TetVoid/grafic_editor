#include "models.h"
#include <fstream>
#include <algorithm>
#include<sstream>

bool comparator_max_min(double* a, double* b)
{
    return *a > *b;
}


bool comparator_min_max(double* a, double* b)
{
    return *a < *b;
}

Figure::Figure(){}

Figure::Figure(std::vector<std::wstring> load_string)
{
    type = load_string[0];
    name = load_string[1];
    id = std::stoi(load_string[2]);

    std::vector<std::wstring> temp = split(load_string[3]);
    color.R = std::stoi(temp[0]);
    color.G = std::stoi(temp[1]);
    color.B = std::stoi(temp[2]);

    temp = split(load_string[4]);
    border_color.R = std::stoi(temp[0]);
    border_color.G = std::stoi(temp[1]);
    border_color.B = std::stoi(temp[2]);
   
    brush_stile = std::stoi(load_string[5]);
    pen_style = std::stoi(load_string[6]);
    pen_size = std::stoi(load_string[7]);

    temp = split(load_string[8]);
    center.x = std::stoi(temp[0]);
    center.y = std::stoi(temp[1]);

    temp = split(load_string[9]);
    pt.x = std::stoi(temp[0]);
    pt.y = std::stoi(temp[1]);

    temp = split(load_string[10]);
    prev.x = std::stoi(temp[0]);
    prev.y = std::stoi(temp[1]);

    move_flag = std::stoi(load_string[11]);
    resize_flag = std::stoi(load_string[12]);
    select_flag = std::stoi(load_string[13]);
    rotate_flag = std::stoi(load_string[14]);

    width = std::stoi(load_string[15]);
    height = std::stoi(load_string[16]);

    rotate_angle = std::stod(load_string[17]);
    resize_index = std::stoi(load_string[18]);

    center_control_x += std::stoi(load_string[19]);
    center_control_y += std::stoi(load_string[20]);

    max_x = std::stod(load_string[21]);
    min_x = std::stod(load_string[22]);
    max_y = std::stod(load_string[23]);
    min_y = std::stod(load_string[24]);


    temp = split(load_string[25]);
    for (int i = 0; i < 4; i++)
    {
        update_cords_x[i] = std::stod(temp[i * 2]);
        update_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }

    temp = split(load_string[26]);
    start_cords_x = new double[4];
    start_cords_y = new double[4];
    for (int i = 0; i < 4; i++)
    {
        start_cords_x[i] = std::stod(temp[i * 2]);
        start_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }


    temp = split(load_string[27]);
    cords_x = new double[4];
    cords_y = new double[4];
    for (int i = 0; i < 4; i++)
    {
        cords_x[i] = std::stod(temp[i * 2]);
        cords_y[i] = std::stod(temp[i * 2 + 1]);
    }
}

Figure::Figure(HDC hDC,std::wstring name,int id, int x, int y, int width, int height, COLOR color, int brush_stile, COLOR border_color, int pen_style, int pen_size)
{
    this->id = id;
    this->name = name;
    this->pen_size = pen_size;
    this->pen_style = pen_style;
    this->brush_stile = brush_stile;
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

    min_x = cords_x[0];
    max_x = cords_x[1];
    min_y = cords_y[0];
    max_y = cords_y[2];
}

Figure::~Figure()
{
}

std::vector<std::wstring> Figure::split(std::wstring str)
{
    std::wstring temp;
    std::vector<std::wstring> parts;
    std::wstringstream wss(str);
    while (std::getline(wss, temp, L' '))
        parts.push_back(temp);

    return parts;
}

void Figure::draw(HDC hDC)
{
    
    HBRUSH brush = CreateHatchBrush(brush_stile,RGB(color.R, color.G, color.B));

    HPEN pen = CreatePen(pen_style,pen_size,RGB(border_color.R, border_color.G, border_color.B));
    SelectObject(hDC, brush);
    SelectObject(hDC, pen);
   
    BeginPath(hDC);

    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
    for(int i =1; i< _msize(cords_x) / sizeof(cords_x[0]);i++)
        LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
    LineTo(hDC, round(cords_x[0]), round(cords_y[0]));

    EndPath(hDC);
    FillPath(hDC);

    if (pen_style == PS_SOLID)
    {
        MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
        for (int i = 1; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
            LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
        LineTo(hDC, round(cords_x[0]), round(cords_y[0]));
    }
    else
        draw_borders(hDC);
    if(select_flag)
        draw_resize_rotate_zone(hDC);
    DeleteObject(brush);
    DeleteObject(pen);
}

void Figure::draw_segment(HDC hDC, int start, int finish, std::vector<int> desh_len,double *remainder, int *index, int* desh_index )
{
    double similarity_len = desh_len[*desh_index] - *remainder;
    double point_x = cords_x[start];
    double point_y = cords_y[start];
    while ((cords_x[start] != cords_x[finish] && point_x < cords_x[finish] && cords_x[start] < cords_x[finish])
        || (cords_x[start] != cords_x[finish] && point_x > cords_x[finish] && cords_x[start] > cords_x[finish])
        || (cords_x[start] == cords_x[finish] && point_y > cords_y[finish] && cords_y[start] > cords_y[finish])
        || (cords_x[start] == cords_x[finish] && point_y < cords_y[finish] && cords_y[start] < cords_y[finish]))
    {
        HPEN pen;
        if (*index == 1)
            pen = CreatePen(pen_style, pen_size, RGB(border_color.R, border_color.G, border_color.B));
        else
            pen = CreatePen(pen_style, pen_size, RGB(255, 255, 255));
       
        SelectObject(hDC, pen);

        double similarity_coeff = similarity_len / sqrt(pow(cords_x[start] - cords_x[finish], 2) + pow(cords_y[start] - cords_y[finish], 2));
        double new_point_x = cords_x[start] + (cords_x[finish] - cords_x[start]) * similarity_coeff;
        double new_point_y = cords_y[start] + (cords_y[finish] - cords_y[start]) * similarity_coeff;

        if ((cords_x[start] != cords_x[finish] && new_point_x < cords_x[finish] && cords_x[start] < cords_x[finish])
            || (cords_x[start] != cords_x[finish] && new_point_x > cords_x[finish] && cords_x[start] > cords_x[finish])
            || (cords_x[start] == cords_x[finish] && new_point_y > cords_y[finish] && cords_y[start] > cords_y[finish])
            || (cords_x[start] == cords_x[finish] && new_point_y < cords_y[finish] && cords_y[start] < cords_y[finish]))

        {
            LineTo(hDC, round(new_point_x), round(new_point_y));
            *index *= -1;
            *remainder = 0;
            *desh_index += 1;
            if (*desh_index == desh_len.size())
            {
                *index *= 1;
                *desh_index = 0;
            }
        }
        else
        {
            LineTo(hDC, round(cords_x[finish]), round(cords_y[finish]));
            
            *remainder += abs(sqrt(pow(cords_x[start]-cords_x[finish], 2) + pow(cords_y[start] - cords_y[finish], 2)) - sqrt(pow(cords_x[start] - point_x, 2) + pow(cords_y[start] - point_y, 2)));
            
            if (*remainder > desh_len[*desh_index])
            {
                *index *= -1;
                *remainder = 0;
                *desh_index += 1;
                if (*desh_index == desh_len.size() - 1)
                {
                    
                    *index *= 1;
                    *desh_index = 0;
                }
            }
        }
        point_x = new_point_x;
        point_y = new_point_y;

        similarity_len += desh_len[*desh_index];
        DeleteObject(pen);
    }
}

void Figure::draw_borders(HDC hDC)
{
    double perimeter = 0;
    int size = _msize(cords_x) / sizeof(cords_x[0]);
    std::vector<int> desh_len;
        switch (pen_style)
        {
        case PS_DASH:
            desh_len = { 10 + pen_size,10 + pen_size };
            break;
        case PS_DOT:
            desh_len = { 2 + pen_size,10 + pen_size };
            break;
        case PS_DASHDOT:
            desh_len={ 10 + pen_size, 10 + pen_size , 2 + pen_size, 10 + pen_size };
            break;
        case PS_DASHDOTDOT:
            desh_len = { 10 + pen_size, 10 + pen_size , 2 + pen_size, 10 + pen_size , 2 + pen_size, 10 + pen_size };
            break;
        }
    double remainder = 0;
    int index = 1;
    int desh_index = 0;
    MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
   
    for (int i = 0; i < size-1; i++)
    {
        draw_segment(hDC, i, i + 1,desh_len, &remainder,&index,&desh_index); 
     
    }
    draw_segment(hDC, size-1, 0, desh_len, &remainder, &index,&desh_index);
}

void Figure::draw_resize_rotate_zone(HDC hDC)
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
    InvalidateRect(hWnd, &rc, FALSE);

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

void Figure::update(HWND hWnd, int x_, int y_,BOOL delta_flag)
{
    RECT rc;
    int x = 0;
    int y = 0;
    if (delta_flag)
    {
       
        x = x_;
        y = y_;

        prev.x -= x;
        prev.y -= y;

    }
    else
    {
        if (x_ == 0 && y_ == 0)
        {
            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);

            x = prev.x - pt.x;
            y = prev.y - pt.y;
            prev.x = pt.x;
            prev.y = pt.y;
        }
        else
        {
            x = center.x - x_;
            y = center.y - y_;
            prev.x -= x;
            prev.y -= y;
        }
    }

    SetRect(&rc, update_cords_x[0]-1, update_cords_y[0]-1, update_cords_x[2] +1, update_cords_y[2] +1);
    InvalidateRect(hWnd, &rc, FALSE);

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

    min_x -= x;
    max_x -= x;
    min_y -= y;
    max_y -= y;

    SetRect(&rc, update_cords_x[0]-1, update_cords_y[0]-1, update_cords_x[2] +1, update_cords_y[2] +1);
    InvalidateRect(hWnd, &rc, FALSE);
}

void Figure::resize(HWND hWnd)
{
    RECT rc;
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    int delta_x = pt.x - prev.x;
    int delta_y = pt.y - prev.y;

    SetRect(&rc, update_cords_x[0] - 1, update_cords_y[0] - 1, update_cords_x[2] + 1, update_cords_y[2] + 1);
    InvalidateRect(hWnd, &rc, FALSE);
    
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
    InvalidateRect(hWnd, &rc, FALSE);

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
    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        if (cords_x[i] > max_x)
            max_x = cords_x[i];
        if(cords_x[i]<min_x)
            min_x = cords_x[i];
        if (cords_y[i] > max_y)
            max_y = cords_y[i];
        if (cords_y[i] < min_y)
            min_y = cords_y[i];
    }
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

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        if (cords_x[i] > max_x)
            max_x = cords_x[i];
        if (cords_x[i] < min_x)
            min_x = cords_x[i];
        if (cords_y[i] > max_y)
            max_y = cords_y[i];
        if (cords_y[i] < min_y)
            min_y = cords_y[i];
    }
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
void Figure::set_brush_style(int style)
{
    brush_stile = style;
}
void Figure::set_pen_style(int style)
{
    pen_style = style;
}
void Figure::set_pen_size(int size)
{
    pen_size = size;
}
void Figure::set_name(std::wstring name)
{
    this->name = name;
}
void Figure::set_id(int id)
{
    this->id = id;
}
void  Figure::set_type(std::wstring type)
{
    this->type = type;
}

COLOR  Figure::get_color()
{
    return color;
}
COLOR Figure::get_border_color()
{
    return border_color;
}
int Figure::get_brush_style()
{
    return brush_stile;
}
int Figure::get_pen_style()
{
    return pen_style;
}
int  Figure::get_pen_size()
{
    return pen_size;
}
POINT Figure::get_center()
{
    return center;
}
POINT Figure::get_max_point()
{
    POINT a;
    a.x = round(max_x);
    a.y = round(max_y);
    return a;

}
POINT Figure::get_min_point()
{
    POINT a;
    a.x = round(min_x);
    a.y = round(min_y);
    return a;
}
std::wstring  Figure::get_name()
{
    return name;
}
int  Figure::get_id()
{
    return id;
}

std::wstring Figure::save()
{
    std::wstring figure_info = L"";
    figure_info += type + L"\n";
    figure_info += name + L"\n";
    figure_info += std::to_wstring(id) + L"\n";
    figure_info += std::to_wstring(color.R)+L" "+std::to_wstring(color.G) + L" "+std::to_wstring(color.B) + L" " + L"\n";
    figure_info += std::to_wstring(border_color.R) + L" " + std::to_wstring(border_color.G) + L" " + std::to_wstring(border_color.B) + L" " + L"\n";
    figure_info += std::to_wstring(brush_stile) + L"\n";
    figure_info += std::to_wstring(pen_style) + L"\n";
    figure_info += std::to_wstring(pen_size) + L"\n";

    figure_info += std::to_wstring(center.x) + L" " + std::to_wstring(center.y) + L"\n";
    figure_info += std::to_wstring(pt.x) + L" " + std::to_wstring(pt.y) + L"\n";
    figure_info += std::to_wstring(prev.x) + L" " + std::to_wstring(prev.y) + L"\n";

    figure_info += std::to_wstring(move_flag) + L"\n";
    figure_info += std::to_wstring(resize_flag) + L"\n";
    figure_info += std::to_wstring(select_flag) + L"\n";
    figure_info += std::to_wstring(rotate_flag) + L"\n";

    figure_info += std::to_wstring(width) + L"\n";
    figure_info += std::to_wstring(height) + L"\n";

    figure_info += std::to_wstring(rotate_angle) + L"\n";
    figure_info += std::to_wstring(resize_index) + L"\n";

    figure_info += std::to_wstring(center_control_x) + L"\n";
    figure_info += std::to_wstring(center_control_y) + L"\n";

    figure_info += std::to_wstring(max_x) + L"\n";
    figure_info += std::to_wstring(min_x) + L"\n";
    figure_info += std::to_wstring(max_y) + L"\n";
    figure_info += std::to_wstring(min_y) + L"\n";

    for (int i = 0; i < 4; i++)
    {
        figure_info += std::to_wstring(update_cords_x[i]) + L" ";
        figure_info += std::to_wstring(update_cords_y[i]) + L" ";
    }
    figure_info += L"\n";

    for (int i = 0; i < _msize(start_cords_x)/sizeof(start_cords_x[0]); i++)
    {
        figure_info += std::to_wstring(start_cords_x[i]) + L" ";
        figure_info += std::to_wstring(start_cords_y[i]) + L" ";
    }
    figure_info += L"\n";

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        figure_info += std::to_wstring(cords_x[i]) + L" ";
        figure_info += std::to_wstring(cords_y[i]) + L" ";
    }

    return figure_info;
}

Elipse::Elipse(std::vector<std::wstring> load_string)
{
    type = load_string[0];
    name = load_string[1];
    id = std::stoi(load_string[2]);

    std::vector<std::wstring> temp = split(load_string[3]);
    color.R = std::stoi(temp[0]);
    color.G = std::stoi(temp[1]);
    color.B = std::stoi(temp[2]);

    temp = split(load_string[4]);
    border_color.R = std::stoi(temp[0]);
    border_color.G = std::stoi(temp[1]);
    border_color.B = std::stoi(temp[2]);

    brush_stile = std::stoi(load_string[5]);
    pen_style = std::stoi(load_string[6]);
    pen_size = std::stoi(load_string[7]);

    temp = split(load_string[8]);
    center.x = std::stoi(temp[0]);
    center.y = std::stoi(temp[1]);

    temp = split(load_string[9]);
    pt.x = std::stoi(temp[0]);
    pt.y = std::stoi(temp[1]);

    temp = split(load_string[10]);
    prev.x = std::stoi(temp[0]);
    prev.y = std::stoi(temp[1]);

    move_flag = std::stoi(load_string[11]);
    resize_flag = std::stoi(load_string[12]);
    select_flag = std::stoi(load_string[13]);
    rotate_flag = std::stoi(load_string[14]);

    width = std::stoi(load_string[15]);
    height = std::stoi(load_string[16]);

    rotate_angle = std::stod(load_string[17]);
    resize_index = std::stoi(load_string[18]);

    center_control_x += std::stoi(load_string[19]);
    center_control_y += std::stoi(load_string[20]);

    max_x = std::stod(load_string[21]);
    min_x = std::stod(load_string[22]);
    max_y = std::stod(load_string[23]);
    min_y = std::stod(load_string[24]);


    temp = split(load_string[25]);
    for (int i = 0; i < 4; i++)
    {
        update_cords_x[i] = std::stod(temp[i * 2]);
        update_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }

    temp = split(load_string[26]);
    start_cords_x = new double[96];
    start_cords_y = new double[96];
    for (int i = 0; i < 96; i++)
    {
        start_cords_x[i] = std::stod(temp[i * 2]);
        start_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }


    temp = split(load_string[27]);
    cords_x = new double[96];
    cords_y = new double[96];
    for (int i = 0; i < 96; i++)
    {
        cords_x[i] = std::stod(temp[i * 2]);
        cords_y[i] = std::stod(temp[i * 2 + 1]);
    }
}

Elipse::Elipse(HDC hDC, std::wstring name, int id, int x, int y, int width, int height, COLOR color,int style, COLOR border_color, int pen_style,int pen_size)
{
    this->id = id;
    this->name = name;
    this->pen_size = pen_size;
    this->pen_style = pen_style;
    brush_stile = style;
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

    
    max_x = cords_x[0];
    min_x = cords_x[0];
    max_y = cords_y[0];
    min_y = cords_y[0];
    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        if (cords_x[i] > max_x)
            max_x = cords_x[i];
        if (cords_x[i] < min_x)
            min_x = cords_x[i];
        if (cords_y[i] > max_y)
            max_y = cords_y[i];
        if (cords_y[i] < min_y)
            min_y = cords_y[i];
    }
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
    InvalidateRect(hWnd, &rc, FALSE);


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

    for (int i = 0; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
    {
        if (cords_x[i] > max_x)
            max_x = cords_x[i];
        if (cords_x[i] < min_x)
            min_x = cords_x[i];
        if (cords_y[i] > max_y)
            max_y = cords_y[i];
        if (cords_y[i] < min_y)
            min_y = cords_y[i];
    }
}

Triangle::Triangle(std::vector<std::wstring> load_string)
{
    type = load_string[0];
    name = load_string[1];
    id = std::stoi(load_string[2]);

    std::vector<std::wstring> temp = split(load_string[3]);
    color.R = std::stoi(temp[0]);
    color.G = std::stoi(temp[1]);
    color.B = std::stoi(temp[2]);

    temp = split(load_string[4]);
    border_color.R = std::stoi(temp[0]);
    border_color.G = std::stoi(temp[1]);
    border_color.B = std::stoi(temp[2]);

    brush_stile = std::stoi(load_string[5]);
    pen_style = std::stoi(load_string[6]);
    pen_size = std::stoi(load_string[7]);

    temp = split(load_string[8]);
    center.x = std::stoi(temp[0]);
    center.y = std::stoi(temp[1]);

    temp = split(load_string[9]);
    pt.x = std::stoi(temp[0]);
    pt.y = std::stoi(temp[1]);

    temp = split(load_string[10]);
    prev.x = std::stoi(temp[0]);
    prev.y = std::stoi(temp[1]);

    move_flag = std::stoi(load_string[11]);
    resize_flag = std::stoi(load_string[12]);
    select_flag = std::stoi(load_string[13]);
    rotate_flag = std::stoi(load_string[14]);

    width = std::stoi(load_string[15]);
    height = std::stoi(load_string[16]);

    rotate_angle = std::stod(load_string[17]);
    resize_index = std::stoi(load_string[18]);

    center_control_x += std::stoi(load_string[19]);
    center_control_y += std::stoi(load_string[20]);

    max_x = std::stod(load_string[21]);
    min_x = std::stod(load_string[22]);
    max_y = std::stod(load_string[23]);
    min_y = std::stod(load_string[24]);


    temp = split(load_string[25]);
    for (int i = 0; i < 4; i++)
    {
        update_cords_x[i] = std::stod(temp[i * 2]);
        update_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }

    temp = split(load_string[26]);
    start_cords_x = new double[3];
    start_cords_y = new double[3];
    for (int i = 0; i < 3; i++)
    {
        start_cords_x[i] = std::stod(temp[i * 2]);
        start_cords_y[i] = std::stod(temp[i * 2 + 1]);
    }


    temp = split(load_string[27]);
    cords_x = new double[3];
    cords_y = new double[3];
    for (int i = 0; i < 3; i++)
    {
        cords_x[i] = std::stod(temp[i * 2]);
        cords_y[i] = std::stod(temp[i * 2 + 1]);
    }
}

Triangle::Triangle(HDC hDC, std::wstring name, int id, int* x, int* y, COLOR color,int style, COLOR border_color, int pen_style,int pen_size)
{
    this->id = id;
    this->name = name;
   
    this->pen_size = pen_size;
    this->pen_style = pen_style;
    brush_stile = style;
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

    max_x = x[0];
    max_y = y[0];
    min_x = x[0]; 
    min_y = y[0];
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
    InvalidateRect(hWnd, &rc, FALSE);
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