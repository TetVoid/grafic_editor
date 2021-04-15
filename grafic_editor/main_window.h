#pragma once
#include <windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, WNDPROC WndProc);
	~MainWindow();
	HWND get_window();
	HINSTANCE get_hInst();
private:
	void init_color_buttoms();
	HINSTANCE hInst;
	HWND hMainWnd; 
};

