#pragma once

#pragma once
#include <windows.h>
#include "models.h"
#include "figure_memory.h"

class TableInfoWindow
{
public:
	TableInfoWindow(HINSTANCE hInstance, HWND hWnd,  FigureMemory* memory);
	TableInfoWindow() {}
	~TableInfoWindow();
	HWND get_window();
private:
	HINSTANCE hInst;
	HWND hInfoSubWnd;
};

class TableRow
{
public:
	TableRow(HINSTANCE hInstance, HWND hWnd, Figure* figure, int y);
	~TableRow();

	HWND ok_buttom;
	HWND del_buttom;
	HWND brush_style_buttom;
	HWND pen_style_buttom;
	HWND edit1;
	HWND edit2;
	HWND edit3;
	HWND edit4;
	HWND edit5;
	HWND edit6;
	HWND edit7;
	HWND edit8;
	HWND edit9;
	HWND edit10;
	HWND edit11;
	void draw(HDC dc);
private:
	int y;
};
