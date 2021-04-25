#pragma once
#include <windows.h>
#include "models.h"
#include "figure_memory.h"

class InfoSubWindow
{
public:
	InfoSubWindow(HINSTANCE hInstance, HWND hWnd,Figure *figure,BOOL*info,FigureMemory *memory);
	InfoSubWindow() {}
	~InfoSubWindow();
	HWND get_window();
private:
	HINSTANCE hInst;
	HWND hInfoSubWnd;
	Figure* figure;
};
