#include "game.h"
#include "player.h" // Для работы с игроками
#include "ball.h"   // Для работы с мячом
#include "utils.h"  // Для утилит, таких как очистка экрана и задержка
#include <iostream>
#include <conio.h> 
#include <chrono> 
#include <thread> 

using namespace std; // Используем пространство имен std для удобства

// Константы для размеров игрового поля
const int FIELD_WIDTH = 80;  // Ширина игрового поля
const int FIELD_HEIGHT = 20; // Высота игрового поля

// Объявление объектов игры
Player player1; // Объект первого игрока
Player player2; // Объект второго игрока
Ball ball;     // Объект мяча

// Функции для отрисовки
void drawField();
void drawPlayers();
void drawBall();
void drawScore();

// Функции для обновления состояния игры
void updateGame();
void handleInput();

// Инициализация игры
void initializeGame() {
    // Инициализация игроков
    player1.x = 2; // Начальная позиция первого игрока по X
    player1.y = FIELD_HEIGHT / 2 - 2; // Начальная позиция первого игрока по Y
    player1.score = 0; // Начальный счет первого игрока

    player2.x = FIELD_WIDTH - 3; // Начальная позиция второго игрока по X
    player2.y = FIELD_HEIGHT / 2 - 2; // Начальная позиция второго игрока по Y
    player2.score = 0; // Начальный счет второго игрока

    // Инициализация мяча
    ball.x = FIELD_WIDTH / 2; // Начальная позиция мяча по X
    ball.y = FIELD_HEIGHT / 2; // Начальная позиция мяча по Y
    ball.dx = 1; // Начальное направление мяча по X
    ball.dy = 0; // Начальное направление мяча по Y (прямо)
}

/**
 * @brief Отрисовывает игровое поле, включая границы.
 */
void drawField() {
    clearScreen(); // Очищаем экран перед отрисовкой

    // Верхняя граница
    for (int i = 0; i < FIELD_WIDTH + 2; ++i) {
        cout << "#";
    }
    cout << endl;

    // Боковые границы и пустое пространство
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        cout << "#"; // Левая граница
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            cout << " "; // Пустое пространство
        }
        cout << "#" << endl; // Правая граница
    }

    // Нижняя граница
    for (int i = 0; i < FIELD_WIDTH + 2; ++i) {
        cout << "#";
    }
    cout << endl;
}

/**
 * @brief Отрисовывает ракетки игроков на игровом поле.
 */
void drawPlayers() {
    // Отрисовка первого игрока
    gotoXY(player1.x, player1.y + 1); // Перемещаем курсор к позиции игрока (с учетом верхней границы)
    cout << "|"; // Верхняя часть ракетки
    gotoXY(player1.x, player1.y + 2);
    cout << "|"; // Средняя часть ракетки
    gotoXY(player1.x, player1.y + 3);
    cout << "|"; // Нижняя часть ракетки

    // Отрисовка второго игрока
    gotoXY(player2.x, player2.y + 1);
    cout << "|";
    gotoXY(player2.x, player2.y + 2);
    cout << "|";
    gotoXY(player2.x, player2.y + 3);
    cout << "|";
}

/**
 * @brief Отрисовывает мяч на игровом поле.
 */
void drawBall() {
    gotoXY(ball.x + 1, ball.y + 1); // Перемещаем курсор к позиции мяча (с учетом левой и верхней границ)
    cout << "O"; // Отрисовываем мяч
}

/**
 * @brief Отрисовывает текущий счет игроков.
 */
void drawScore() {
    // Выводим счет за пределами игрового поля (например, выше или ниже)
    gotoXY(FIELD_WIDTH / 2 - 5, 0); // Позиция для вывода счета первого игрока
    cout << "Счет Игрока 1: " << player1.score;

    gotoXY(FIELD_WIDTH / 2 + 5, 0); // Позиция для вывода счета второго игрока
    cout << "Счет Игрока 2: " << player2.score;
}

/**
 * @brief Обрабатывает ввод от пользователя для управления ракетками.
 */
void handleInput() {
    // Проверяем, была ли нажата клавиша
    if (_kbhit()) { // Функция _kbhit() проверяет, есть ли нажатая клавиша в буфере
        char key = _getch(); // Функция _getch() считывает символ без ожидания Enter

        // Управление игроком 1 (W/S)
        if (key == 'w' || key == 'W') {
            if (player1.y > 0) { // Проверяем, чтобы ракетка не вышла за верхнюю границу
                player1.y--; // Двигаем ракетку вверх
            }
        }
        else if (key == 's' || key == 'S') {
            if (player1.y + 2 < FIELD_HEIGHT - 1) { // Проверяем, чтобы ракетка не вышла за нижнюю границу
                player1.y++; // Двигаем ракетку вниз
            }
        }

        // Управление игроком 2 (I/K)
        if (key == 'i' || key == 'I') {
            if (player2.y > 0) {
                player2.y--;
            }
        }
        else if (key == 'k' || key == 'K') {
            if (player2.y + 2 < FIELD_HEIGHT - 1) {
                player2.y++;
            }
        }
    }
}

/**
 * @brief Обновляет состояние игры: движение мяча, проверка столкновений, начисление очков.
 */
void updateGame() {
    // Движение мяча
    ball.x += ball.dx; // Обновляем позицию мяча по X
    ball.y += ball.dy; // Обновляем позицию мяча по Y

    // Проверка столкновения мяча с верхним/нижним краем
    if (ball.y <= 0 || ball.y >= FIELD_HEIGHT - 1) {
        ball.dy *= -1; // Меняем направление мяча по Y
    }

    // Проверка столкновения мяча с ракетками
    // Столкновение с ракеткой игрока 1
    if (ball.x == player1.x + 1 && (ball.y >= player1.y && ball.y <= player1.y + 2)) {
        ball.dx *= -1; // Меняем направление мяча по X
        // Изменение направления Y в зависимости от точки попадания по ракетке
        if (ball.y == player1.y) {
            ball.dy = -1; // Диагонально вверх
        }
        else if (ball.y == player1.y + 1) {
            ball.dy = 0; // Прямо
        }
        else {
            ball.dy = 1; // Диагонально вниз
        }
    }
    // Столкновение с ракеткой игрока 2
    if (ball.x == player2.x - 1 && (ball.y >= player2.y && ball.y <= player2.y + 2)) {
        ball.dx *= -1;
        if (ball.y == player2.y) {
            ball.dy = -1;
        }
        else if (ball.y == player2.y + 1) {
            ball.dy = 0;
        }
        else {
            ball.dy = 1;
        }
    }

    // Проверка на попадание в ворота
    // Мяч ушел за ракетку игрока 1 (гол игроку 2)
    if (ball.x < 0) {
        player2.score++; // Увеличиваем счет игрока 2
        ball.x = FIELD_WIDTH / 2; // Возвращаем мяч в центр
        ball.y = FIELD_HEIGHT / 2;
        ball.dx = 1; // Мяч летит в сторону игрока, который пропустил
        ball.dy = 0;
    }
    // Мяч ушел за ракетку игрока 2 (гол игроку 1)
    if (ball.x > FIELD_WIDTH) {
        player1.score++; // Увеличиваем счет игрока 1
        ball.x = FIELD_WIDTH / 2;
        ball.y = FIELD_HEIGHT / 2;
        ball.dx = -1; // Мяч летит в сторону игрока, который пропустил
        ball.dy = 0;
    }
}

/**
 * @brief Основная функция, запускающая игру.
 * Содержит главный игровой цикл.
 */
void startGame() {
    initializeGame(); // Инициализируем игру

    bool gameOver = false; // Флаг завершения игры
    while (!gameOver) {
        drawField();    // Отрисовываем поле
        drawPlayers();  // Отрисовываем игроков
        drawBall();     // Отрисовываем мяч
        drawScore();    // Отрисовываем счет

        handleInput();  // Обрабатываем ввод пользователя
        updateGame();   // Обновляем состояние игры

        // Проверка условия победы
        if (player1.score >= 7) {
            gotoXY(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 + 1);
            cout << "Игрок 1 победил!";
            gameOver = true;
        }
        else if (player2.score >= 7) {
            gotoXY(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 + 1);
            cout << "Игрок 2 победил!";
            gameOver = true;
        }

        this_thread::sleep_for(chrono::milliseconds(100)); // Задержка для контроля скорости игры
    }
    gotoXY(0, FIELD_HEIGHT + 4); // Перемещаем курсор после окончания игры
}