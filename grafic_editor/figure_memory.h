#pragma once
#include "models.h"
#include <vector>

class FigureMemory
{
public:
	FigureMemory();
	~FigureMemory();
	Figure* operator[](int index);
	void add(Figure* figure);
	void del();
	void move(HWND hWnd);
	void rotate(HWND hWnd);
	void resize(HWND hWnd);
	void select(HWND hWnd);

	void stop_move(HWND hWnd);
	void stop_rotate(HWND hWnd);
	void stop_resize(HWND hWnd);
	void stop_select(HWND hWnd);

	void draw(HDC hDC);
	void set_color(COLOR color,HWND hWnd, BOOL color_flag);
	void set_brush_style(int style, HWND hWnd, BOOL style_flag);
	void set_pen_style(int style, HWND hWnd, BOOL style_flag);
	void set_pen_size(int size, HWND hWnd, BOOL size_flag);
	void set_prev_cords(HWND hWnd);

	BOOL check_position(HWND hWnd);
	


private:
	std::vector<Figure*> figure_list = {};
	int figure_index = -1;
};

