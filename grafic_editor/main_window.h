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
	double set_xPos(WPARAM wParam);
	double set_yPos(WPARAM wParam);
	void update_scrolls(POINT max, POINT min);

private:
	void init_color_buttoms();
	void init_scroll_bars();
	HINSTANCE hInst;
	HWND hMainWnd; 
	HWND hCanvasWnd;
	HWND hVerticalBar;
	HWND hHorizontBar;
	int xScrollPos = 0;
	int yScrollPos = 0;
	double one_segment_x;
	double one_segment_y;
};

