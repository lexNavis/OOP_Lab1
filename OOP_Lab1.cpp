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
    int x = 600, y = 600; // �������� ����������
    //Fish AFish(x, y);
    PatrioticFish BFish(400, 400);
    Rectangle(hdc, 0, 0, 1920, 1080);

    while(1)
    {
        EXIT_TASK = false;
        cout << "�������� ��������: \n"
            << "1 - ������� ������� ����\n"
            << "2 - ������� ���� - ��������\n"
            << "3 - ������� ���� (��������)\n";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "������� ���������� (x,y): \n";
            cin >> x >> y;
            Fish AFish(x, y);
            while (!EXIT_TASK) {
                cout << "�������� �������� ��� ������� �����: \n"
                    << "1 - �������� �� ������\n"
                    << "2 - ������\n"
                    << "3 - ����������\n"
                    << "������ ����� - ��������� �� �������\n";
                cin >> choice;
                switch (choice) {
                case 1: { AFish.Show();    break; }
                case 2: { AFish.Hide();    break; }
                case 3: { AFish.drag(PPM); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "���������...\n";
                    break;
                }
                }
            }
            break;
        }
        
        case 2: {
            cout << "������� ���������� (x,y): \n";
            cin >> x >> y;
            PatrioticFish BFish(x, y);
            while (!EXIT_TASK) {
                cout << "�������� �������� ��� ������� �����: \n"
                    << "1 - �������� �� ������\n"
                    << "2 - ������\n"
                    << "3 - ����������\n"
                    << "4 - ������������ �����\n"
                    << "5 - ��������� � ������� �����\n"
                    << "������ ����� - ��������� �� �������\n";
                cin >> choice;
                switch (choice) {
                case 1: { BFish.Show();    break; }
                case 2: { BFish.Hide();    break; }
                case 3: { BFish.drag(PPM); break; }
                case 4: { BFish.patrioticForm(); break; }
                case 5: { BFish.baseForm(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "���������...\n";
                    break;
                }
                }
            }
            break;
        }
        case 3: {
            cout << "������� ���������� (x,y): \n";
            cin >> x >> y;
            Disc CDisk(x, y, 40, 20, 4);
            CDisk.Show();
            break;
        }
            default:
                break;
        }
    }

    ReleaseDC(hWnd, hdc); // ���������� �������� ����������
    return 0;
}
   