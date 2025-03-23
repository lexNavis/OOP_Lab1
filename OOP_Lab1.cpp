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
        cout << "�������� ��������: \n"
            << "1 - ������� ������� ����\n"
            << "2 - ������� ���� - ��������\n"
            << "3 - ������� ��������� \n"
            << "4 - ������� ���� � ��������� ������������ (��������) \n"
            << "5 - �������� ����� \n";
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
                cout << "�������� �������� ��� ����� - ���������: \n"
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
                case 4: { BFish.superPower(); break; }
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
            DiscoFish CFish(x, y);
            while (!EXIT_TASK) {
                cout << "�������� �������� ��� �����-�����: \n"
                    << "1 - �������� �� ������\n"
                    << "2 - ������\n"
                    << "3 - ����������\n"
                    << "4 - ����� - �����\n"
                    << "������ ����� - ��������� �� �������\n";
                cin >> choice;
                switch (choice) {
                case 1: { CFish.Show();    break; }
                case 2: { CFish.Hide();    break; }
                case 3: { CFish.drag(PPM); break; }
                case 4: { CFish.superPower(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "���������...\n";
                    break;
                }
                }
            }
            break;
        }
        case 4: {
            cout << "������� ���������� (x,y): \n";
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
                cout << "�������� �������� ��� ������� �����: \n"
                    << "1 - �������� �� ������\n"
                    << "2 - ������\n"
                    << "3 - ����������\n"
                    << "4 - ����� - �����\n"
                    << "������ ����� - ��������� �� �������\n";
                cin >> choice;
                switch (choice) {
                case 1: { CFish.Show();    break; }
                case 2: { CFish.Hide();    break; }
                case 3: { CFish.drag(PPM); break; }
                case 4: { CFish.discoForm(); break; }
                default: {
                    EXIT_TASK = true;
                    cout << "���������...\n";
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

    ReleaseDC(hWnd, hdc); // ���������� �������� ����������
    return 0;
}
   