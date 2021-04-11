#pragma once

#include "models.h"

class Figure_fabric
{
public:
	Figure_fabric();
	void set_start_cords(HWND hWnd);
	void set_width_height(HWND hWnd);
	Figure* create_figure(HWND hWnd);
	BOOL is_draw();
	void draw_focus(HWND hWnd);
	void set_color(COLOR color);
	void set_border_color(COLOR color);
	void set_figure_class(std::string figure_class);

private:
	COLOR color;
	COLOR border_color;
	int x;
	int y;
	int width;
	int height;
	int triangle_index = 0;
	int triangle_x[3];
	int triangle_y[3];

	BOOL draw = false;
	RECT prev_rc;
	std::string figure_class = "rect";
	void calculate_ellips(double* cords_x, double* cords_y);
};