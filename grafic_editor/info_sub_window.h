#pragma once
#include <windows.h>
#include "models.h"

class InfoSubWindow
{
public:
	InfoSubWindow(HINSTANCE hInstance, HWND hWnd,Figure *figure,BOOL*info);
	InfoSubWindow() {}
	~InfoSubWindow();
	HWND get_window();
private:
	HINSTANCE hInst;
	HWND hInfoSubWnd;
	Figure* figure;
};
