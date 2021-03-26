#include <iostream>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, // дескриптор экземпляра приложения
    HINSTANCE hPrevInstance, // в Win32 не используется
    LPSTR lpCmdLine, // нужен для запуска окна в режиме командной строки
    int nCmdShow) // режим отображения окна
{
    // Функция вывода окна с кнопкой "ОК" на экран (о параметрах позже)
    MessageBox(NULL, L"Привет, мир!!!", L"Оконная процедура", MB_OK);
    return NULL; // возвращаем значение функции
}