#pragma once

#include <Windows.h>
#include "object.h"
#include "posinlifetime.h"

void ArrayShow(HDC hdc, PosInLifeTime* posArray, int arrayLen);
void WinShow(HDC hdc, RECT rc, Object obj, PosInLifeTime* posArray, int arrayLen);
