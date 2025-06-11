#include "utils.h"

// Для Windows
#ifdef _WIN32
#include <windows.h> // Для работы с консолью на Windows

void clearScreen() {
    system("cls"); // Вызов системной команды для очистки экрана
}

void gotoXY(int x, int y) {
    COORD coord; // Структура для координат
    coord.X = x; // Устанавливаем координату X
    coord.Y = y; // Устанавливаем координату Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Устанавливаем позицию курсора
}


#else
#include <iostream> // Для вывода

using namespace std; // Используем пространство имен std для удобства

/**
 * @brief Очищает экран консоли на Unix-подобных системах.
 */
void clearScreen() {
    // ANSI escape-последовательность для очистки экрана и перемещения курсора в 0,0
    cout << "\033[2J\033[H";
}

/**
 * @brief Перемещает курсор консоли в указанные координаты на Unix-подобных системах.
 * @param x Координата X.
 * @param y Координата Y.
 */
void gotoXY(int x, int y) {
    // ANSI escape-последовательность для перемещения курсора
    cout << "\033[" << y + 1 << ";" << x + 1 << "H";
}
#endif