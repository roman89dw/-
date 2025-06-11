#pragma once
#ifndef BALL_H
#define BALL_H

struct Ball {
    int x;     // Координата X мяча
    int y;     // Координата Y мяча
    int dx;    // Направление движения по X (-1: влево, 1: вправо)
    int dy;    // Направление движения по Y (-1: вверх, 0: прямо, 1: вниз)
};

#endif // BALL_H