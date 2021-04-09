#include "figure_fabric.h"

Figure_fabric::Figure_fabric()
{
	prev_rc.left = 0;
	prev_rc.right = 0;
	prev_rc.top = 0;
	prev_rc.bottom = 0;

	color.R = 255;
	color.G = 255;
	color.B = 255;
	border_color.R = 0;
	border_color.G = 0;
	border_color.B = 0;

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
Figure* Figure_fabric::create_figure(HWND hWnd,std::string figure_class)
{
	Figure* pict = NULL;
	if (figure_class == "ellips")
	{
		OutputDebugStringW(L"1");
		pict = new Elipse(GetDC(hWnd), x, y, width, height, color, border_color);
	}
	else if (figure_class == "rect")
		pict = new Figure(GetDC(hWnd), x, y, width, height, color, border_color);
	return pict;
}

void Figure_fabric::draw_focus(HWND hWnd)
{
	HBRUSH brush = CreateSolidBrush(RGB(color.R, color.G, color.B));

	HPEN pen = CreatePen(PS_SOLID, 2, RGB(border_color.R, border_color.G, border_color.B));
	SelectObject(GetDC(hWnd), pen);
	SelectObject(GetDC(hWnd), brush);

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

	HBRUSH white_brush = CreateSolidBrush(RGB(255, 255, 255));

	FillRect(GetDC(hWnd), &prev_rc, white_brush);
	SetRect(&prev_rc, x - 2, y - 2, pt.x + 2, pt.y + 2);
	DeleteObject(white_brush);

	HDC hDC = GetDC(hWnd);
	BeginPath(hDC);
	MoveToEx(hDC, x, y, nullptr);
	LineTo(hDC, pt.x, y);
	LineTo(hDC, pt.x, pt.y);
	LineTo(hDC, x, pt.y);
	LineTo(hDC, x, y);
	EndPath(hDC);
	FillPath(hDC);

	MoveToEx(hDC, x, y, nullptr);
	LineTo(hDC, pt.x, y);
	LineTo(hDC, pt.x, pt.y);
	LineTo(hDC, x, pt.y);
	LineTo(hDC, x, y);

	DeleteObject(brush);
	DeleteObject(pen);
}

BOOL Figure_fabric::is_draw()
{
	return draw;
}

void Figure_fabric::set_color(COLOR color)
{
	this->color.R = color.R;
	this->color.G = color.G;
	this->color.B = color.B;
}

void  Figure_fabric::set_border_color(COLOR color)
{
	this->border_color.R = color.R;
	this->border_color.G = color.G;
	this->border_color.B = color.B;
}

