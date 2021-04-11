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
	if (figure_class != "triangle")
	{
		x = pt.x;
		y = pt.y;
	}
	else
	{
		triangle_x[triangle_index] = pt.x;
		triangle_y[triangle_index] = pt.y;
		triangle_index++;
	}
	
}
void  Figure_fabric::set_width_height(HWND hWnd)
{
	if (figure_class != "triangle")
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
	else
		if (triangle_index == 3)
		{
			draw = false;

			prev_rc.left = 0;
			prev_rc.right = 0;
			prev_rc.top = 0;
			prev_rc.bottom = 0;

			triangle_index = 0;
			
		}
}
Figure* Figure_fabric::create_figure(HWND hWnd)
{
	Figure* pict = NULL;
	if (figure_class == "ellips")
		pict = new Elipse(GetDC(hWnd), x, y, width, height, color, border_color);
	else if (figure_class == "rect")
		pict = new Figure(GetDC(hWnd), x, y, width, height, color, border_color);
	else if (figure_class == "triangle")
		pict = new Triangle(GetDC(hWnd), triangle_x, triangle_y, color, border_color);
	return pict;
}

void Figure_fabric::draw_focus(HWND hWnd)
{
	HBRUSH brush = CreateSolidBrush(RGB(color.R, color.G, color.B));

	HPEN pen = CreatePen(PS_SOLID, 2, RGB(border_color.R, border_color.G, border_color.B));
	SelectObject(GetDC(hWnd), pen);
	SelectObject(GetDC(hWnd), brush);

	POINT pt,real_pt;
	GetCursorPos(&real_pt);
	ScreenToClient(hWnd, &real_pt);
	pt.x = real_pt.x;
	pt.y = real_pt.y;
	int x = this->x;
	int y = this->y;
	RECT rc;

	width = pt.x - x;
	height = pt.y - y;
	
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
	if (figure_class == "rect")
	{
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
	}
	else if (figure_class == "ellips")
	{
	

		double *cords_x = new double[96];
		double *cords_y = new double[96];

		calculate_ellips(cords_x, cords_y);

		MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
		for (int i = 1; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
			LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
		LineTo(hDC, round(cords_x[0]), round(cords_y[0]));

		EndPath(hDC);
		FillPath(hDC);

		MoveToEx(hDC, round(cords_x[0]), round(cords_y[0]), nullptr);
		for (int i = 1; i < _msize(cords_x) / sizeof(cords_x[0]); i++)
			LineTo(hDC, round(cords_x[i]), round(cords_y[i]));
		LineTo(hDC, round(cords_x[0]), round(cords_y[0]));

		delete cords_x;
		delete cords_y;

	}
	else if (figure_class == "triangle")
	{
		for (int i = triangle_index; i < 3; i++)
		{
			triangle_x[i] = real_pt.x;
			triangle_y[i] = real_pt.y;
		}

		MoveToEx(hDC, round(triangle_x[0]), round(triangle_y[0]), nullptr);
		for (int i = 1; i < 3; i++)
			LineTo(hDC, round(triangle_x[i]), round(triangle_y[i]));
		LineTo(hDC, round(triangle_x[0]), round(triangle_y[0]));

		EndPath(hDC);
		FillPath(hDC);

		MoveToEx(hDC, round(triangle_x[0]), round(triangle_y[0]), nullptr);
		for (int i = 1; i < 3; i++)
			LineTo(hDC, round(triangle_x[i]), round(triangle_y[i]));
		LineTo(hDC, round(triangle_x[0]), round(triangle_y[0]));

		int max_x=triangle_x[0],max_y = triangle_y[0],min_x = triangle_x[0], min_y= triangle_y[0];
		for (int i = 0; i < 3; i++)
		{
			if (max_x < triangle_x[i])
				max_x = triangle_x[i];
			if (min_x > triangle_x[i])
				min_x = triangle_x[i];
			if (max_y < triangle_y[i])
				max_y = triangle_y[i];
			if (min_y > triangle_y[i])
				min_y = triangle_y[i];

		}
		SetRect(&prev_rc, min_x - 2, min_y - 2, max_x + 2, max_y + 2);
	}

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

void Figure_fabric::set_figure_class(std::string figure_class)
{
	this->figure_class = figure_class;
}

void Figure_fabric::calculate_ellips(double* cords_x, double* cords_y)
{
	int size = _msize(cords_x) / sizeof(cords_x[0]);
	double delta = double(abs(width) / 6) / (size / 8);
	double delta_x = x + width/2;
	double delta_y = y + height/2;
	double delta_sum = 0;
	width = abs(width);
	height = abs(height);

	for (int i = 1; i < size / 8; i++)
	{
		delta_sum += delta;
		cords_x[i] = (-width) / 2 + delta_sum;

		cords_x[size - i] = (-width) / 2 + delta_sum;

		cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_x[i] += delta_x;

		cords_x[size - i] += delta_x;
	}
	delta = double((width / 3) * 2) / (size / 4);
	for (int i = size / 8; i < size / 8 + size / 4; i++)
	{
		delta_sum += delta;

		cords_x[i] = (-width) / 2 + delta_sum;

		cords_x[size - i] = (-width) / 2 + delta_sum;

		cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_x[i] += delta_x;

		cords_x[size - i] += delta_x;
	}

	delta = double(width / 6) / (size / 8);
	for (int i = size / 8 + size / 4; i < size / 2; i++)
	{
		delta_sum += delta;

		cords_x[i] = (-width) / 2 + delta_sum;

		cords_x[size - i] = (-width) / 2 + delta_sum;

		cords_y[i] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_y[size - i] = delta_y + sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[i], 2)));

		cords_x[i] += delta_x;

		cords_x[size - i] += delta_x;

	}


	cords_x[0] = -width / 2;

	cords_y[0] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[0], 2)));

	cords_x[0] += delta_x;


	cords_x[size / 2] = width / 2;

	cords_y[size / 2] = delta_y - sqrt((pow(double(height) / 2, 2) / pow(double(width) / 2, 2)) * (pow(double(width) / 2, 2) - pow(cords_x[size / 2], 2)));


	cords_x[size / 2] += delta_x;
}

