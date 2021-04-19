#include "figure_memory.h"

FigureMemory::FigureMemory()
{

}
FigureMemory::~FigureMemory()
{

}
Figure* FigureMemory::operator[](int index)
{
	return figure_list[index];
}
void FigureMemory::add(Figure* figure)
{
	figure_list.push_back(figure);
}
void FigureMemory::del()
{
    if (figure_index != -1)
    {
        figure_list.erase(figure_list.begin() + figure_index);
        figure_index = -1;
    }
}

void FigureMemory::set_prev_cords(HWND hWnd)
{

    if (figure_index != -1)
    {
        figure_list[figure_index]->set_prev_cords(hWnd);
    }
}
void FigureMemory:: move(HWND hWnd)
{
    if (figure_index != -1 && figure_list[figure_index]->is_move())
        figure_list[figure_index]->update(hWnd);   
}
void FigureMemory::rotate(HWND hWnd)
{
    if (figure_index != -1&& figure_list[figure_index]->is_rotate())
        figure_list[figure_index]->rotate(hWnd);
}
void FigureMemory::resize(HWND hWnd)
{
    if (figure_index != -1 && figure_list[figure_index]->is_resize())
        figure_list[figure_index]->resize(hWnd);
         
}

void  FigureMemory::select(HWND hWnd)
{
    for (int i = 0; i < figure_list.size(); i++)
    {
      
        int prev_index = figure_index;
        if (figure_list[i]->select(hWnd))
        {
            if (figure_index != -1 && figure_index != i)
                figure_list[figure_index]->stop_select();
            figure_index = i;
            figure_list[i]->init(hWnd);
        }
        else if (figure_index == i)
            figure_index = -1;

        if (prev_index != -1)
            figure_list[prev_index]->init(hWnd);
    }
}

void FigureMemory::stop_move(HWND hWnd)
{
    if (figure_index != -1 && figure_list[figure_index]->is_move())
        figure_list[figure_index]->stop_move();
}
void FigureMemory::stop_rotate(HWND hWnd)
{
    if (figure_index != -1 && figure_list[figure_index]->is_rotate())
        figure_list[figure_index]->stop_rotate();

}
void FigureMemory::stop_resize(HWND hWnd)
{
    if (figure_index != -1 && figure_list[figure_index]->is_resize())
        figure_list[figure_index]->stop_resize();
}
void FigureMemory::stop_select(HWND hWnd)
{

}


void FigureMemory::draw(HDC hDC)
{
    if (figure_index != -1)
        figure_list[figure_index]->draw(hDC);
    for (int i = 0; i < figure_list.size(); i++)
    {
        if (i == figure_index)
            continue;
        figure_list[i]->draw(hDC);
    }
}

BOOL FigureMemory::check_position(HWND hWnd)
{
    BOOL position_flag = true;
    for (int i = 0; i < figure_list.size(); i++)
        if (figure_list[i]->check_position(hWnd))
        {
            position_flag = false;
            break;
        }
    return position_flag;
}

void FigureMemory::set_color(COLOR color, HWND hWnd, BOOL color_flag)
{
    if (figure_index != -1)
        if (color_flag)
            figure_list[figure_index]->set_color(color, hWnd);
        else
            figure_list[figure_index]->set_border_color(color, hWnd);
}
void FigureMemory::set_brush_style(int style, HWND hWnd, BOOL style_flag)
{
    if (figure_index != -1 && style_flag)
        figure_list[figure_index]->set_brush_style(style);
}
void FigureMemory::set_pen_style(int style, HWND hWnd, BOOL style_flag)
{
    if (figure_index != -1 && style_flag)
        figure_list[figure_index]->set_pen_style(style);
}
void FigureMemory::set_pen_size(int size, HWND hWnd, BOOL size_flag)
{
    if (figure_index != -1 && size_flag)
        figure_list[figure_index]->set_pen_size(size);
}

Figure* FigureMemory:: get_selected()
{
    return figure_list[figure_index];
}
BOOL FigureMemory::is_selected()
{
    if (figure_index == -1)
        return false;
    else
        return true;
}