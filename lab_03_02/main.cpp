#include "framework.h"
#include "object.h"
#include "point.h"
#include "functions.h"
#include "posinlifetime.h"

RECT rc;
Object player;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		// ќтрисовка окна
	case WM_SIZE:
	{
		GetClientRect(hWnd, &rc);
	}
	case WM_KEYDOWN:
	{

	}
	case WM_PAINT:
	{
		// ѕолучение координат клиентской части окна
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rcClient;

		GetClientRect(hWnd, &rcClient);

		//  онец отрисовки, особождение контекста
		EndPaint(hWnd, &ps);
	}
	break;

	// ¬ыход из приложени€
	case WM_DESTROY:
		PostQuitMessage(0);

		// ќстальные сообщени€ окна обрабатываютс€ стандартным образом
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	}
	return 0;
}

int main()
{
	Point firstPos(100, 100);
	Point secondPos;

	PosInLifeTime* posArray = new PosInLifeTime[MAX_SHADOW_LEN];

	for (int i = 0; i < MAX_SHADOW_LEN; i++)
	{
		posArray[i] = PosInLifeTime(Point(0, 0), Point(0, 0), MAX_SHADOW_LEN);
	}

	WNDCLASSA wndclass;

	memset(&wndclass, 0, sizeof(WNDCLASSA));
	wndclass.lpszClassName = "Game";
	wndclass.lpfnWndProc = WndProc;

	RegisterClassA(&wndclass);

	HWND hwnd;

	hwnd = CreateWindowA
	(
		"Game",
		"Game",
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		640,
		480,
		NULL,
		NULL,
		NULL,
		NULL
	);

	HDC hdc = GetDC(hwnd);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;

	player.Init(Point(100, 100), Point(40, 40), RGB(0, 255, 0));

	int iCount = 0;

	firstPos = player.pos;
	posArray[MAX_SHADOW_LEN - 1] = PosInLifeTime(firstPos, player.size, 0);

	while (1)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			player.Control();
			player.Move();

			switch (player.IfMove())
			{
			case 1:
			{

				secondPos = player.pos;

				if (iCount < MAX_SHADOW_LEN)
				{
					iCount++;

					for (int i = MAX_SHADOW_LEN - iCount; i < MAX_SHADOW_LEN; i++)
					{
						posArray[i].pos = posArray[i + 1].pos;
						posArray[i].size = player.size;
						posArray[i].lifeTime--;
					}

					posArray[MAX_SHADOW_LEN - 1] = PosInLifeTime(secondPos, player.size, 0);

				}
				else
				{
					for (int i = MAX_SHADOW_LEN - iCount; i < MAX_SHADOW_LEN; i++)
					{
						posArray[i].pos = posArray[i + 1].pos;
						posArray[i].size = player.size;
					}

					posArray[MAX_SHADOW_LEN - 1] = PosInLifeTime(secondPos, player.size, 0);
				}
				firstPos = secondPos;

				WinShow(hdc, rc, player, posArray, MAX_SHADOW_LEN);
			}
			break;
			case -1:
			{

				while (iCount > 0)
				{

					for (int i = MAX_SHADOW_LEN - iCount; i < MAX_SHADOW_LEN; i++)
					{
						posArray[i].size = player.size;
						posArray[i].lifeTime++;
					}

					iCount--;
					WinShow(hdc, rc, player, posArray, MAX_SHADOW_LEN);
					Sleep(1);
				}

				for (int i = 0; i < MAX_SHADOW_LEN; i++)
				{
					posArray[i] = PosInLifeTime(Point(0, 0), player.size, MAX_SHADOW_LEN);
				}

				posArray[MAX_SHADOW_LEN - 1] = PosInLifeTime(firstPos, player.size, 0);

			}
			break;
			default:
				break;
			}
			Sleep(4);
		}
	}

	delete[] posArray;
	return 0;
}
