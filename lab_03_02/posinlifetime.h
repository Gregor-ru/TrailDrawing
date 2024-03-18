#pragma once
#include "point.h"

class PosInLifeTime {
public:
    Point pos;
    Point size;
    int lifeTime;

    PosInLifeTime() : pos(Point()), size(Point()), lifeTime(0) {}
    PosInLifeTime(Point _pos, Point _size, int _lifeTime) : pos(_pos), size(_size), lifeTime(_lifeTime) {}
};