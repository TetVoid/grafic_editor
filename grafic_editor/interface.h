#pragma once
#include <windows.h>

class Interface
{
public:
	Interface();
	~Interface();
	void draw(HWND hWnd);
	void set_pen();
	void set_brush();
private:
	BOOL pen_or_brush = true;

 };