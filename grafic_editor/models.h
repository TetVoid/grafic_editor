#pragma once
#include <windows.h>
#include <string>

struct COLOR
{
	int R;
	int G;
	int B;
};

class Figure
{
public:
	Figure();
	Figure(HDC hDC, int x, int y, int width, int height,COLOR color,int brush_stile, COLOR border_color, int pen_style, int pen_size);
	~Figure();
	void draw(HDC hDC);
	void update(HWND hwnd);
	void init(HWND hwnd);
	void rotate(HWND hWnd);
	void virtual resize(HWND hWnd);

	void set_prev_cords(HWND hWnd);
	void stop_move();
	void stop_rotate();
	void stop_select();
	void virtual stop_resize();

	void set_color(COLOR color, HWND hWnd);
	void set_border_color(COLOR color, HWND hWnd);
	void set_brush_style(int style);
	void set_pen_style(int style);
	void set_pen_size(int size);

	BOOL check_position(HWND hwnd);
	BOOL select(HWND hWnd);
	BOOL is_rotate();
	BOOL is_selected();
	BOOL is_move();
	BOOL is_resize();


protected:
	POINT center;
	COLOR color;
	COLOR border_color;
	int brush_stile = 7;
	int pen_size = 2;
	int pen_style = PS_INSIDEFRAME;
	double *start_cords_x, *start_cords_y;
	double *cords_x, *cords_y;
	double update_cords_x[4], update_cords_y[4];
	POINT pt,prev;
	BOOL move_flag = false, resize_flag=false,select_flag=false,rotate_flag=false;
	int height, width;
	double rotate_angle = 0;
	int half_side = 5;
	int resize_index = -1;

	int center_control_x = 1;
	int center_control_y = 1;

	void draw_borders(HDC hDC);
	void calculate_rotation();
};

class Elipse : public Figure
{
public:
	Elipse(HDC hDC, int x, int y, int width, int height, COLOR color,int style, COLOR border_color, int pen_style, int pen_size);
	void resize(HWND hWnd);
	void stop_resize();
private:
	void calculate_cords();
};

class Triangle : public Figure
{
public:
	Triangle(HDC hDC, int *x, int *y, COLOR color, int style, COLOR border_color, int pen_style, int pen_size);
	void resize(HWND hWnd);
};