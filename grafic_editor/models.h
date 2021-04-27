#pragma once
#include <windows.h>
#include <string>
#include <vector>

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
	Figure(std::vector<std::wstring>);
	Figure(HDC hDC,std::wstring name, int id, int x, int y, int width, int height,COLOR color,int brush_stile, COLOR border_color, int pen_style, int pen_size);
	~Figure();
	void draw(HDC hDC);
	void update(HWND hwnd,int x=0,int y=0, BOOL delta_flag= false);
	void init(HWND hwnd);
	void rotate(HWND hWnd);
	void virtual resize(HWND hWnd);
	void virtual normalize(HWND hWnd);

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
	void set_name(std::wstring);
	void set_id(int);
	void set_type(std::wstring);

	COLOR get_color();
	COLOR get_border_color();
	int get_brush_style();
	int get_pen_style();
	int get_pen_size();
	POINT get_center();
	std::wstring get_name();
	int get_id();

	BOOL check_position(HWND hwnd);
	BOOL select(HWND hWnd);
	BOOL is_rotate();
	BOOL is_selected();
	BOOL is_move();
	BOOL is_resize();

	POINT get_max_point();
	POINT get_min_point();

	std::wstring save();

protected:
	std::wstring name;
	int id;
	POINT center;
	COLOR color;
	COLOR border_color;
	POINT pt, prev;

	int brush_stile = 7;
	int pen_size = 2;
	int pen_style = PS_SOLID;

	double *start_cords_x, *start_cords_y;
	double *cords_x, *cords_y;
	double update_cords_x[4], update_cords_y[4];

	BOOL move_flag = false, resize_flag=false,select_flag=false,rotate_flag=false;
	int height, width;
	double rotate_angle = 0;
	int half_side = 5;
	int resize_index = -1;

	int center_control_x = 1;
	int center_control_y = 1;

	double max_x;
	double min_x;
	double max_y;
	double min_y;

	std::wstring type = L"";

	void draw_resize_rotate_zone(HDC hDC);
	void calculate_rotation();
	void draw_borders(HDC hDC);
	void draw_segment(HDC hDC, int start, int finish, std::vector<int> desh_len, double* remainder, int* index, int* desh_index);

	std::vector<std::wstring> split(std::wstring);
};

class Elipse : public Figure
{
public:
	Elipse(std::vector<std::wstring>);
	Elipse(HDC hDC, std::wstring name, int id, int x, int y, int width, int height, COLOR color,int style, COLOR border_color, int pen_style, int pen_size);
	void resize(HWND hWnd);
	void stop_resize();
	void normalize(HWND hWnd);
private:
	void calculate_cords();
};

class Triangle : public Figure
{
public:
	Triangle(std::vector<std::wstring>);
	Triangle(HDC hDC, std::wstring name, int id, int *x, int *y, COLOR color, int style, COLOR border_color, int pen_style, int pen_size);
	void normalize(HWND hWnd);
	void resize(HWND hWnd);
};