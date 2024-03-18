#include "object.h"

class Square : public Object {
public:
    // ������������
    Square() : Object() {}
    Square(Point pos, Point size, COLORREF color) : Object(pos, size, color) {}

    // ��������������� ������ ��� ��������� ��������
    void Draw(HDC hdc) override {
        // ��������� ��������
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, brush);

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, brush);
        Rectangle(hdc, (int)pos.x, (int)pos.y, (int)(pos.x + size.x), (int)(pos.y + size.y));
    }
};

class Circle : public Object {
public:
    // ������������
    Circle() : Object() {}
    Circle(Point pos, Point size, COLORREF color) : Object(pos, size, color) {}

    // ��������������� ������ ��� ��������� �����
    void Draw(HDC hdc) override {
        // ��������� �����
    }
};
