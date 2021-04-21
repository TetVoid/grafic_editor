#pragma once
#include <windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, WNDPROC WndProc, WNDPROC WndButtomsProc);
	MainWindow(){}
	~MainWindow();
	HWND get_canvas_window();
	HWND get_buttom_window();
	HINSTANCE get_hInst();
private:
	void init_color_buttoms();
	HINSTANCE hInst;
	HWND hMainWnd; 
	HWND hCanvasWnd;
};

