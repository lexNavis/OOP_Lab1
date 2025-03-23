#include <iostream>
#include <Windows.h>
#include "IDK.h"
using namespace std;

int PPM = 10; //Pixels Per Move
bool EXIT_TASK = false; //to break infinite loops

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
    HDC hdc = GetDC(hWnd);
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);
    Rectangle(hdc, 0, 0, 1920, 1080);
    int x = 0, y = 0;

    while(1)
    {
        EXIT_TASK = false;
        cout << "Выберите действие: \n"
            << "1 - Создать базовую рыбу\n"
            << "2 - Создать рыбу - патриота\n"
            << "3 - Создать дискорыбу \n"
            << "4 - Создать флаг и потестить столкновения (временно) \n"
            << "5 - Очистить экран \n";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "Введите координаты (x,y): \n";
            cin >> x >> y;
            Fish AFish(x, y);
            while (!EXIT_TASK) {
                cout << "Выберите действие над базовой рыбой: \n"
                    << "1 - Показать на экране\n"
                    << "2 - Скрыть\n"
                    << "3 - Перемещать\n"
                    << "Другая цифра - Вернуться на главную\n";
                cin >> choice;
                switch (choice) {
                case 1: { AFish.Show();    break; }
                case 2: { AFish.Hide();    break; }
                case 3: { AFish.drag(PPM); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "Возращаем...\n";
                    break;
                }
                }
            }
            break;
        }
        
        case 2: {
            cout << "Введите координаты (x,y): \n";
            cin >> x >> y;
            PatrioticFish BFish(x, y);
            while (!EXIT_TASK) {
                cout << "Выберите действие над рыбой - патриотом: \n"
                    << "1 - Показать на экране\n"
                    << "2 - Скрыть\n"
                    << "3 - Перемещать\n"
                    << "4 - Патриотичная форма\n"
                    << "5 - Вернуться в обычную форму\n"
                    << "Другая цифра - Вернуться на главную\n";
                cin >> choice;
                switch (choice) {
                case 1: { BFish.Show();    break; }
                case 2: { BFish.Hide();    break; }
                case 3: { BFish.drag(PPM); break; }
                case 4: { BFish.superPower(); break; }
                case 5: { BFish.baseForm(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "Возращаем...\n";
                    break;
                }
                }
            }
            break;
        }
        case 3: {
            cout << "Введите координаты (x,y): \n";
            cin >> x >> y;
            DiscoFish CFish(x, y);
            while (!EXIT_TASK) {
                cout << "Выберите действие над диско-рыбой: \n"
                    << "1 - Показать на экране\n"
                    << "2 - Скрыть\n"
                    << "3 - Перемещать\n"
                    << "4 - Диско - форма\n"
                    << "Другая цифра - Вернуться на главную\n";
                cin >> choice;
                switch (choice) {
                case 1: { CFish.Show();    break; }
                case 2: { CFish.Hide();    break; }
                case 3: { CFish.drag(PPM); break; }
                case 4: { CFish.superPower(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "Возращаем...\n";
                    break;
                }
                }
            }
            break;
        }
        case 4: {
            cout << "Введите координаты (x,y): \n";
            cin >> x >> y;
            Flag DFlag(x, y, 80, 40);
            /*PatrioticFish DFish(100, 100);
            DFlag.Show();
            DFish.drag(PPM, &DFlag);*/
            DiscoFish DFish(100, 100);
            DFlag.Show();
            DFish.drag(PPM, &DFlag);
            
            /*DiscoFish CFish(x, y);
            while (!EXIT_TASK) {
                cout << "Выберите действие над базовой рыбой: \n"
                    << "1 - Показать на экране\n"
                    << "2 - Скрыть\n"
                    << "3 - Перемещать\n"
                    << "4 - Диско - форма\n"
                    << "Другая цифра - Вернуться на главную\n";
                cin >> choice;
                switch (choice) {
                case 1: { CFish.Show();    break; }
                case 2: { CFish.Hide();    break; }
                case 3: { CFish.drag(PPM); break; }
                case 4: { CFish.discoForm(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "Возращаем...\n";
                    break;
                }
                }
            }*/
            break;
        }
        case 5: {
            Rectangle(hdc, 0, 0, 1920, 1080);
            break;
        }
            default:
                break;
        }
    }

    ReleaseDC(hWnd, hdc); // Освободите контекст устройства
    return 0;
}
   