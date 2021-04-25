#pragma once
#include "models.h"
#include <map>

class FigureMemory
{
public:
	FigureMemory();
	~FigureMemory();
	Figure* operator[](int index);
	void add(Figure* figure, int index);
	void del();
	void del(int index);
	void move(HWND hWnd);
	void rotate(HWND hWnd);
	void resize(HWND hWnd);
	void select(HWND hWnd);
	void update(HWND hWnd, double x, double y);

	void stop_move(HWND hWnd);
	void stop_rotate(HWND hWnd);
	void stop_resize(HWND hWnd);

	void draw(HDC hDC);
	void set_color(COLOR color,HWND hWnd, BOOL color_flag);
	void set_brush_style(int style, HWND hWnd, BOOL style_flag);
	void set_pen_style(int style, HWND hWnd, BOOL style_flag);
	void set_pen_size(int size, HWND hWnd, BOOL size_flag);
	void set_prev_cords(HWND hWnd);
	Figure* get_selected();
	BOOL is_selected();

	BOOL check_position(HWND hWnd);
	BOOL check_name(std::wstring name);
	BOOL check_id(int id);
	
	POINT get_max_point(HWND hWnd);
	POINT get_min_point();

private:
	std::map<int, Figure*>figure_list;
	int figure_index = -1;
};

