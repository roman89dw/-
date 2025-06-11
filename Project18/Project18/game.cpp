#include "game.h"
#include "player.h" // ��� ������ � ��������
#include "ball.h"   // ��� ������ � �����
#include "utils.h"  // ��� ������, ����� ��� ������� ������ � ��������
#include <iostream>
#include <conio.h> 
#include <chrono> 
#include <thread> 

using namespace std; // ���������� ������������ ���� std ��� ��������

// ��������� ��� �������� �������� ����
const int FIELD_WIDTH = 80;  // ������ �������� ����
const int FIELD_HEIGHT = 20; // ������ �������� ����

// ���������� �������� ����
Player player1; // ������ ������� ������
Player player2; // ������ ������� ������
Ball ball;     // ������ ����

// ������� ��� ���������
void drawField();
void drawPlayers();
void drawBall();
void drawScore();

// ������� ��� ���������� ��������� ����
void updateGame();
void handleInput();

// ������������� ����
void initializeGame() {
    // ������������� �������
    player1.x = 2; // ��������� ������� ������� ������ �� X
    player1.y = FIELD_HEIGHT / 2 - 2; // ��������� ������� ������� ������ �� Y
    player1.score = 0; // ��������� ���� ������� ������

    player2.x = FIELD_WIDTH - 3; // ��������� ������� ������� ������ �� X
    player2.y = FIELD_HEIGHT / 2 - 2; // ��������� ������� ������� ������ �� Y
    player2.score = 0; // ��������� ���� ������� ������

    // ������������� ����
    ball.x = FIELD_WIDTH / 2; // ��������� ������� ���� �� X
    ball.y = FIELD_HEIGHT / 2; // ��������� ������� ���� �� Y
    ball.dx = 1; // ��������� ����������� ���� �� X
    ball.dy = 0; // ��������� ����������� ���� �� Y (�����)
}

/**
 * @brief ������������ ������� ����, ������� �������.
 */
void drawField() {
    clearScreen(); // ������� ����� ����� ����������

    // ������� �������
    for (int i = 0; i < FIELD_WIDTH + 2; ++i) {
        cout << "#";
    }
    cout << endl;

    // ������� ������� � ������ ������������
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        cout << "#"; // ����� �������
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            cout << " "; // ������ ������������
        }
        cout << "#" << endl; // ������ �������
    }

    // ������ �������
    for (int i = 0; i < FIELD_WIDTH + 2; ++i) {
        cout << "#";
    }
    cout << endl;
}

/**
 * @brief ������������ ������� ������� �� ������� ����.
 */
void drawPlayers() {
    // ��������� ������� ������
    gotoXY(player1.x, player1.y + 1); // ���������� ������ � ������� ������ (� ������ ������� �������)
    cout << "|"; // ������� ����� �������
    gotoXY(player1.x, player1.y + 2);
    cout << "|"; // ������� ����� �������
    gotoXY(player1.x, player1.y + 3);
    cout << "|"; // ������ ����� �������

    // ��������� ������� ������
    gotoXY(player2.x, player2.y + 1);
    cout << "|";
    gotoXY(player2.x, player2.y + 2);
    cout << "|";
    gotoXY(player2.x, player2.y + 3);
    cout << "|";
}

/**
 * @brief ������������ ��� �� ������� ����.
 */
void drawBall() {
    gotoXY(ball.x + 1, ball.y + 1); // ���������� ������ � ������� ���� (� ������ ����� � ������� ������)
    cout << "O"; // ������������ ���
}

/**
 * @brief ������������ ������� ���� �������.
 */
void drawScore() {
    // ������� ���� �� ��������� �������� ���� (��������, ���� ��� ����)
    gotoXY(FIELD_WIDTH / 2 - 5, 0); // ������� ��� ������ ����� ������� ������
    cout << "���� ������ 1: " << player1.score;

    gotoXY(FIELD_WIDTH / 2 + 5, 0); // ������� ��� ������ ����� ������� ������
    cout << "���� ������ 2: " << player2.score;
}

/**
 * @brief ������������ ���� �� ������������ ��� ���������� ���������.
 */
void handleInput() {
    // ���������, ���� �� ������ �������
    if (_kbhit()) { // ������� _kbhit() ���������, ���� �� ������� ������� � ������
        char key = _getch(); // ������� _getch() ��������� ������ ��� �������� Enter

        // ���������� ������� 1 (W/S)
        if (key == 'w' || key == 'W') {
            if (player1.y > 0) { // ���������, ����� ������� �� ����� �� ������� �������
                player1.y--; // ������� ������� �����
            }
        }
        else if (key == 's' || key == 'S') {
            if (player1.y + 2 < FIELD_HEIGHT - 1) { // ���������, ����� ������� �� ����� �� ������ �������
                player1.y++; // ������� ������� ����
            }
        }

        // ���������� ������� 2 (I/K)
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
 * @brief ��������� ��������� ����: �������� ����, �������� ������������, ���������� �����.
 */
void updateGame() {
    // �������� ����
    ball.x += ball.dx; // ��������� ������� ���� �� X
    ball.y += ball.dy; // ��������� ������� ���� �� Y

    // �������� ������������ ���� � �������/������ �����
    if (ball.y <= 0 || ball.y >= FIELD_HEIGHT - 1) {
        ball.dy *= -1; // ������ ����������� ���� �� Y
    }

    // �������� ������������ ���� � ���������
    // ������������ � �������� ������ 1
    if (ball.x == player1.x + 1 && (ball.y >= player1.y && ball.y <= player1.y + 2)) {
        ball.dx *= -1; // ������ ����������� ���� �� X
        // ��������� ����������� Y � ����������� �� ����� ��������� �� �������
        if (ball.y == player1.y) {
            ball.dy = -1; // ����������� �����
        }
        else if (ball.y == player1.y + 1) {
            ball.dy = 0; // �����
        }
        else {
            ball.dy = 1; // ����������� ����
        }
    }
    // ������������ � �������� ������ 2
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

    // �������� �� ��������� � ������
    // ��� ���� �� ������� ������ 1 (��� ������ 2)
    if (ball.x < 0) {
        player2.score++; // ����������� ���� ������ 2
        ball.x = FIELD_WIDTH / 2; // ���������� ��� � �����
        ball.y = FIELD_HEIGHT / 2;
        ball.dx = 1; // ��� ����� � ������� ������, ������� ���������
        ball.dy = 0;
    }
    // ��� ���� �� ������� ������ 2 (��� ������ 1)
    if (ball.x > FIELD_WIDTH) {
        player1.score++; // ����������� ���� ������ 1
        ball.x = FIELD_WIDTH / 2;
        ball.y = FIELD_HEIGHT / 2;
        ball.dx = -1; // ��� ����� � ������� ������, ������� ���������
        ball.dy = 0;
    }
}

/**
 * @brief �������� �������, ����������� ����.
 * �������� ������� ������� ����.
 */
void startGame() {
    initializeGame(); // �������������� ����

    bool gameOver = false; // ���� ���������� ����
    while (!gameOver) {
        drawField();    // ������������ ����
        drawPlayers();  // ������������ �������
        drawBall();     // ������������ ���
        drawScore();    // ������������ ����

        handleInput();  // ������������ ���� ������������
        updateGame();   // ��������� ��������� ����

        // �������� ������� ������
        if (player1.score >= 7) {
            gotoXY(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 + 1);
            cout << "����� 1 �������!";
            gameOver = true;
        }
        else if (player2.score >= 7) {
            gotoXY(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 + 1);
            cout << "����� 2 �������!";
            gameOver = true;
        }

        this_thread::sleep_for(chrono::milliseconds(100)); // �������� ��� �������� �������� ����
    }
    gotoXY(0, FIELD_HEIGHT + 4); // ���������� ������ ����� ��������� ����
}