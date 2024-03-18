#pragma once
#include "point.h"
#include <Windows.h>

class Object {
public:
    Point pos;
    Point size;
    COLORREF brush;
    Point speed;

    Object() : pos(Point()), size(Point()), brush(RGB(0, 0, 0)), speed(Point()) {}
    Object(Point _pos, Point _size, COLORREF _brush) : pos(_pos), size(_size), brush(_brush), speed(Point(0, 0)) {}

    void Init(Point _pos, Point _size, COLORREF _brush) {
        pos = _pos;
        size = _size;
        brush = _brush;
        speed = Point(0, 0);
    }

    void Show(HDC hdc) {
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, brush);

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, brush);
        Rectangle(hdc, (int)pos.x, (int)pos.y, (int)(pos.x + size.x), (int)(pos.y + size.y));
    }

    void Control() {
        int objSpeed = 3;
        speed.x = 0;
        speed.y = 0;

        if (GetKeyState(VK_UP) < 0) speed.y = -objSpeed;
        if (GetKeyState(VK_DOWN) < 0) speed.y = objSpeed;
        if (GetKeyState(VK_LEFT) < 0) speed.x = -objSpeed;
        if (GetKeyState(VK_RIGHT) < 0) speed.x = objSpeed;
        if (speed.x != 0 && speed.y != 0) speed = Point(speed.x * 0.7, speed.y * 0.7);
    }

    void Move() {
        pos.x += speed.x;
        pos.y += speed.y;
    }

    int IfMove() const {
        if (GetKeyState(VK_UP) < 0 || GetKeyState(VK_DOWN) < 0 || GetKeyState(VK_LEFT) < 0 || GetKeyState(VK_RIGHT) < 0) {
            return 1;
        }

        if (GetAsyncKeyState(VK_UP) > 0 || GetAsyncKeyState(VK_DOWN) > 0 || GetAsyncKeyState(VK_LEFT) > 0 || GetAsyncKeyState(VK_RIGHT) > 0) {
            return -1;
        }

        return 0;
    }

};