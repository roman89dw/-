#pragma once
#ifndef BALL_H
#define BALL_H

struct Ball {
    int x;     // ���������� X ����
    int y;     // ���������� Y ����
    int dx;    // ����������� �������� �� X (-1: �����, 1: ������)
    int dy;    // ����������� �������� �� Y (-1: �����, 0: �����, 1: ����)
};

#endif // BALL_H