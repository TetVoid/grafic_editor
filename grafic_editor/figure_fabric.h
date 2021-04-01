#pragma once

#include "models.h"

class Figure_fabric
{
public:
	Figure_fabric();
	void set_start_cords(HWND hWnd);
	void set_width_height(HWND hWnd);
	Figure create_figure(HWND hWnd);
	BOOL is_draw();
	void draw_focus(HWND hWnd);
	void set_color(COLOR color);

private:
	COLOR color;
	int x;
	int y;
	int width;
	int height;
	BOOL draw = false;
	RECT prev_rc;
};