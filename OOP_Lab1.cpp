#include <iostream>
#include <Windows.h>
#include "IDK.h"
using namespace std;


int main() {
    HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(hWnd);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    int x = 600, y = 600; // Измените координаты
    Fish AFish(x, y);
    Rectangle(hdc, 0, 0, 1920, 1080);
    while(1)
    {
        AFish.Show();
        AFish.drag(40);
    }

    ReleaseDC(hWnd, hdc); // Освободите контекст устройства
    return 0;
}
/*ACircle.Show();
 //AEllipse.Show();*/       
//ATriangle.Show();
//system("pause");
///*ACircle.Hide();
//AEllipse.Hide(); */
//ATriangle.Expand(30);
//system("pause");
//ATriangle.Reduce(30);
//system("pause");    