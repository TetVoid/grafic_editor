#include "figure_memory.h"
#include <fstream>

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

void FigureMemory::add(Figure* figure,int index)
{
	figure_list[index] = figure;
}

void FigureMemory::del()
{
    if (figure_index != -1)
    {
        std::map <int, Figure*> ::iterator delete_el;
        delete_el = figure_list.find(figure_index);
        figure_list.erase(delete_el);
        figure_index = -1;
    }
}

void FigureMemory::del(int index)
{
    std::map <int, Figure*> ::iterator delete_el;
    delete_el = figure_list.find(index);
    figure_list.erase(delete_el);
    figure_index = -1;
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
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
    {
      
        int prev_index = figure_index;
        if (it->second->select(hWnd))
        {
            if (figure_index != -1 && figure_index != it->first)
                figure_list[figure_index]->stop_select();
            figure_index = it->first;
            it->second->init(hWnd);
        }
        else if (figure_index == it->first)
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

void FigureMemory::draw(HDC hDC)
{
    
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
    {
        it->second->draw(hDC);
    }
}

BOOL FigureMemory::check_position(HWND hWnd)
{
    BOOL position_flag = true;
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        if (it->second->check_position(hWnd))
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

POINT  FigureMemory::get_max_point(HWND hWnd)
{

    RECT rect;
    GetClientRect(hWnd, &rect);
    POINT a;
    if (figure_list.size() == 0)
    {
        a.x = rect.right;
        a.y = rect.bottom;
    }
    else
        a = figure_list.begin()->second->get_max_point();

    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
    {
        if (it->second->get_max_point().x > a.x)
            a.x =it->second->get_max_point().x;

        if (it->second->get_max_point().y > a.y)
            a.y = it->second->get_max_point().y;
    }
    return a;

}

POINT  FigureMemory::get_min_point()
{
    POINT a;
    if (figure_list.size() == 0)
    {
        a.x = 0;
        a.y = 0;
    }
    else
        a = figure_list.begin()->second->get_min_point();

    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
    {
        if (it->second->get_min_point().x < a.x)
            a.x = it->second->get_min_point().x;

        if (it->second->get_min_point().y < a.y)
            a.y = it->second->get_min_point().y;
    }
    return a;
}

void FigureMemory::update(HWND hWnd, double x, double y)
{
    for (int i = 0; i < figure_list.size(); i++)
        figure_list[i]->update(hWnd, x, y, true);
    InvalidateRect(hWnd, NULL, FALSE);
}

BOOL FigureMemory::check_name(std::wstring name)
{
    int repit_index = 0;

    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        if (it->second->get_name()._Equal(name))
            repit_index++;
    
    if (repit_index > 1)
        return false;
    else
        return true;
}

BOOL FigureMemory::check_id(int id)
{
    int repit_index = 0;

    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        if (it->second->get_id() == id)
            repit_index++;

    if (repit_index >= 1)
        return false;
    else
        return true;
}

void FigureMemory::save(std::wstring path)
{
    std::wstring save_string=L"";
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        save_string += it->second->save()+L"\n";

    path += L".gfe";
    std::wofstream fout(path, std::ios::app);
    fout << save_string;
    fout.close();
}

void  FigureMemory::load(std::wstring path)
{
    std::wstring string;
    std::vector< std::wstring> load_vector;
    std::wifstream file(path);
    int index = 0;
    while (getline(file, string))
    {
        load_vector.push_back(string);
        index++;
        if (index == 28)
        {
            Figure* pict = NULL;
            if (load_vector[0]._Equal(L"ellips"))
                pict = new Elipse(load_vector);
            else if (load_vector[0]._Equal(L"rect"))
                pict = new Figure(load_vector);
            else if (load_vector[0]._Equal(L"triangle"))
                pict = new Triangle(load_vector);

            figure_list[std::stoi(load_vector[2])] = pict;

            index = 0;
            load_vector.clear();      
        }
    }
}

void FigureMemory::clear()
{
    figure_list.clear();
}