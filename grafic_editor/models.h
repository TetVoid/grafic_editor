#pragma once
#include <windows.h>

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
	Figure(HDC hDC, int x, int y, int width, int height,COLOR color, COLOR border_color);
	~Figure();
	void draw(HDC hDC);
	void update(HWND hwnd);
	void init(HWND hwnd);
	void rotate(HWND hWnd);
	void resize(HWND hWnd);

	void set_prev_cords(HWND hWnd);
	void stop_move();
	void stop_rotate();
	void stop_select();
	void stop_resize();

	void set_color(COLOR color, HWND hWnd);
	void set_border_color(COLOR color, HWND hWnd);

	BOOL check_position(HWND hwnd);
	BOOL select(HWND hWnd);
	BOOL is_rotate();
	BOOL is_selected();
	BOOL is_move();
	BOOL is_resize();


private:
	POINT center;
	COLOR color;
	COLOR border_color;
	double start_cords_x[4], start_cords_y[4];
	double cords_x[4], cords_y[4];
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
};
