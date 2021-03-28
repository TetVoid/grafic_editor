#pragma once
#include <windows.h>

class Figure
{
public:
	Figure();
	Figure(HDC hDC, int x, int y, int width, int height);
	~Figure();
	void draw(HDC hDC);
	BOOL check_position(HWND hwnd);
	BOOL is_move();
	void set_move(BOOL condition);
	void update(HWND hwnd);
	void init(HWND hwnd);

private:
	POINT pt,pos,prev;
	BOOL move = false, first=true;
	int height, width;

};
