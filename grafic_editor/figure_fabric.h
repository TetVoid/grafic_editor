#pragma once

#include "models.h"
#include "figure_memory.h"
class Figure_fabric
{
public:
	Figure_fabric();
	void set_start_cords(HWND hWnd);
	void set_width_height(HWND hWnd);
	Figure* create_figure(HWND hWnd, FigureMemory mem);
	BOOL is_draw();
	void draw_focus(HWND hWnd);
	void set_color(COLOR color);
	void set_border_color(COLOR color);

	void set_figure_class(std::string figure_class);
	void set_brush_style(int stile);
	void set_pen_style(int stile);
	void set_pen_size(int size);

private:
	COLOR color;
	COLOR border_color;
	int x;
	int y;
	int width;
	int height;
	int pen_size = 2;
	int triangle_index = 0;
	int triangle_x[3];
	int triangle_y[3];
	int figure_number = 0;
	int brush_stile = 7;
	int pen_style = PS_SOLID;

	BOOL draw = false;
	RECT prev_rc;
	std::string figure_class = "rect";
	void calculate_ellips(double* cords_x, double* cords_y);
};