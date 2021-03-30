#include "main_window.h"

MainWindow::MainWindow(HINSTANCE hInstance, WNDPROC WndProc)
{
    hInst = hInstance;
    TCHAR szClassName[] = L"Main window"; // строка с именем класса

    WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
    wc.cbSize = sizeof(wc); // размер структуры (в байтах)
    wc.style = CS_HREDRAW | CS_VREDRAW| CS_DBLCLKS; // стиль класса окошка
    wc.lpfnWndProc = WndProc; // указатель на пользовательскую функцию
    wc.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
    wc.lpszClassName = szClassName; // указатель на имя класса
    wc.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
    wc.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // декриптор пиктограммы
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // дескриптор маленькой пиктограммы (в трэе)
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // дескриптор кисти для закраски фона окна
    wc.hInstance = hInstance; // указатель на строку, содержащую имя меню, применяемого для класса

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
    }

    hMainWnd = CreateWindow(
        szClassName, // имя класса
        L"Полноценная оконная процедура", // имя окошка (то что сверху)
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // режимы отображения окошка
        CW_USEDEFAULT, // позиция окошка по оси х
        NULL, // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
        CW_USEDEFAULT, // ширина окошка
        NULL, // высота окошка (раз дефолт в ширине, то писать не нужно)
        (HWND)NULL, // дескриптор родительского окна
        NULL, // дескриптор меню
        HINSTANCE(hInstance), // дескриптор экземпляра приложения
        NULL); // ничего не передаём из WndProc

    if (!hMainWnd) {
        MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
    }

}

MainWindow::~MainWindow()
{
}

HWND MainWindow:: get_window()
{
    return hMainWnd;
}