#pragma once
#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    int x;       // Координата X левого верхнего угла ракетки
    int y;       // Координата Y левого верхнего угла ракетки
    int score;   // Текущий счет игрока
};

#endif // PLAYER_H