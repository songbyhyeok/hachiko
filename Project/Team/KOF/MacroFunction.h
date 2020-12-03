#pragma once

#include <Windows.h>

//충돌체크 함수
inline bool CheckRectCollision(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right ||
		rc1.right < rc2.left ||
		rc1.top > rc2.bottom ||
		rc1.bottom < rc2.top)
		return false;

	return true;
}

inline void FrameCalculation(int elapsedFrame, int ratio, int curKeyFrameX, int MaxFrame)
{
	elapsedFrame++;
	if (elapsedFrame % ratio == ratio - 1)
	{
		curKeyFrameX++;

		if (curKeyFrameX >= MaxFrame)
			curKeyFrameX = 0;

		elapsedFrame = 0;
	}
}

inline void RenderRect(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

inline void RenderRect(HDC hdc, RECT rect, RECT rect2)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);
}


inline void RenderRectangleToCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void RenderEllipseToCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void RenderLine(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}


