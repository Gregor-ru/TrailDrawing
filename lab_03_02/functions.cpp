#include "framework.h"
#include "posinlifetime.h"
#include "object.h"
#include "functions.h"
#include <Windows.h>

void ArrayShow(HDC hdc, PosInLifeTime* posArray, int arrayLen) {
    Object shadow(Point(0, 0), Point(0, 0), RGB(0, 0, 0));

    for (int i = 0; i < arrayLen; i++) {
        int color = ITER_SIZE * posArray[i].lifeTime;

        if (posArray[i].lifeTime > 100) {
            color = ITER_SIZE * (posArray[i].lifeTime - 100);
        }

        shadow.Init(posArray[i].pos, posArray[i].size, RGB(color, 255, color));

        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, shadow.brush);

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, shadow.brush);
        Rectangle(hdc, (int)shadow.pos.x, (int)shadow.pos.y, (int)(shadow.pos.x + shadow.size.x), (int)(shadow.pos.y + shadow.size.y));
    }
}

void WinShow(HDC hdc, RECT rc, Object obj, PosInLifeTime* posArray, int arrayLen) {
    HDC sqDc = CreateCompatibleDC(hdc);
    HBITMAP sqBm = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

    SelectObject(sqDc, sqBm);

    SelectObject(sqDc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(sqDc, RGB(255, 255, 255));
    Rectangle(sqDc, 0, 0, 640, 840);

    ArrayShow(sqDc, posArray, arrayLen);
    obj.Show(sqDc);

    BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, sqDc, 0, 0, SRCCOPY);
    DeleteDC(sqDc);
    DeleteObject(sqBm);
}