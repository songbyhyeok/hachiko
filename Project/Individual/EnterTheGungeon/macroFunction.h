#pragma once

#include "GameNode.h"

inline void SetWindowSize(int x, int y, int width, int height)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = width; rc.bottom = height;

	// 실제 윈도우 크기 받아온다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
}

inline RECT GetRectToCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2),
	x + (width / 2), y + (height / 2) };

	return rc;
}

inline void RenderRect(HDC hdc, int x, int y, int xEnd, int yEnd)
{
	Rectangle(hdc, x, y, xEnd, yEnd);
}

inline void RenderRectToCenter(HDC hdc, int centerX, int centerY,
	int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

inline void RenderLine(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline void RenderRect(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x, y);
}

inline void RenderEllipseToCenter(HDC hdc, int centerX, int centerY,
	int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

inline float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}

inline bool CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right ||
		rc1.right < rc2.left ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
	{
		return false;
	}

	return true;
}