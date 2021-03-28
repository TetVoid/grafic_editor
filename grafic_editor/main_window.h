#pragma once
#include <windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, WNDPROC WndProc);
	~MainWindow();
	HWND get_window();

private:
	HINSTANCE hInst;
	HWND hMainWnd; 
};

