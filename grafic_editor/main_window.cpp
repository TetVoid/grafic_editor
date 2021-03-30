#include "main_window.h"

MainWindow::MainWindow(HINSTANCE hInstance, WNDPROC WndProc)
{
    hInst = hInstance;
    TCHAR szClassName[] = L"Main window"; // ������ � ������ ������

    WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
    wc.cbSize = sizeof(wc); // ������ ��������� (� ������)
    wc.style = CS_HREDRAW | CS_VREDRAW| CS_DBLCLKS; // ����� ������ ������
    wc.lpfnWndProc = WndProc; // ��������� �� ���������������� �������
    wc.lpszMenuName = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
    wc.lpszClassName = szClassName; // ��������� �� ��� ������
    wc.cbWndExtra = NULL; // ����� ������������� ������ � ����� ���������
    wc.cbClsExtra = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // ��������� �����������
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // ���������� ��������� ����������� (� ����)
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���������� �������
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ��� �������� ���� ����
    wc.hInstance = hInstance; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
    }

    hMainWnd = CreateWindow(
        szClassName, // ��� ������
        L"����������� ������� ���������", // ��� ������ (�� ��� ������)
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
        CW_USEDEFAULT, // ������� ������ �� ��� �
        NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
        CW_USEDEFAULT, // ������ ������
        NULL, // ������ ������ (��� ������ � ������, �� ������ �� �����)
        (HWND)NULL, // ���������� ������������� ����
        NULL, // ���������� ����
        HINSTANCE(hInstance), // ���������� ���������� ����������
        NULL); // ������ �� ������� �� WndProc

    if (!hMainWnd) {
        MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
    }

}

MainWindow::~MainWindow()
{
}

HWND MainWindow:: get_window()
{
    return hMainWnd;
}