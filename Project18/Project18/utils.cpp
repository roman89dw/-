#include "utils.h"

// ��� Windows
#ifdef _WIN32
#include <windows.h> // ��� ������ � �������� �� Windows

void clearScreen() {
    system("cls"); // ����� ��������� ������� ��� ������� ������
}

void gotoXY(int x, int y) {
    COORD coord; // ��������� ��� ���������
    coord.X = x; // ������������� ���������� X
    coord.Y = y; // ������������� ���������� Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // ������������� ������� �������
}


#else
#include <iostream> // ��� ������

using namespace std; // ���������� ������������ ���� std ��� ��������

/**
 * @brief ������� ����� ������� �� Unix-�������� ��������.
 */
void clearScreen() {
    // ANSI escape-������������������ ��� ������� ������ � ����������� ������� � 0,0
    cout << "\033[2J\033[H";
}

/**
 * @brief ���������� ������ ������� � ��������� ���������� �� Unix-�������� ��������.
 * @param x ���������� X.
 * @param y ���������� Y.
 */
void gotoXY(int x, int y) {
    // ANSI escape-������������������ ��� ����������� �������
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}
#endif