#include "figure_fabric.h"

Figure_fabric::Figure_fabric()
{
	prev_rc.left = 0;
	prev_rc.right = 0;
	prev_rc.top = 0;
	prev_rc.bottom = 0;
}
void Figure_fabric:: set_start_cords(HWND hWnd)
{
	draw = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	x = pt.x;
	y = pt.y;
}
void  Figure_fabric::set_width_height(HWND hWnd)
{
	draw = false;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	
	width = abs(x - pt.x);
	height = abs(y - pt.y);

	if (x > pt.x)
		x = pt.x;

	if (y > pt.y)
		y = pt.y;

	prev_rc.left = 0;
	prev_rc.right = 0;
	prev_rc.top = 0;
	prev_rc.bottom = 0;
}
Figure Figure_fabric::create_figure(HWND hWnd)
{
	Figure pict = Figure(GetDC(hWnd), x, y, width, height);
	return pict;
}

void Figure_fabric::draw_focus(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	int x = this->x;
	int y = this->y;
	RECT rc;
	
	if (x > pt.x)
	{
		int buf = x;
		x = pt.x;
		pt.x = buf;
	}

	if (y > pt.y)
	{
		int buf = y;
		y = pt.y;
		pt.y = buf;
	}

	SetRect(&rc, x, y, pt.x, pt.y);
	FillRect(GetDC(hWnd), &prev_rc, (HBRUSH)CreateSolidBrush(RGB(255, 255, 255)));
	SetRect(&prev_rc, x-1, y-1, pt.x+1, pt.y+1);

	FillRect(GetDC(hWnd), &rc, (HBRUSH)CreateSolidBrush(RGB(255, 0,0)));
}

BOOL Figure_fabric::is_draw()
{
	return draw;
}

