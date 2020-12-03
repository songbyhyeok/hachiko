#include "GameNode.h"

HRESULT GameNode::Init()
{
	
	return S_OK;
}

void GameNode::Release()
{
}

void GameNode::Update()
{
}

void GameNode::Render(HDC hdc)
{
}

void GameNode::SetPos(FPOINT pt) { pos = pt; }

GameNode::FPOINT GameNode::GetPos()
{
	return pos;
}

void GameNode::SetFrame(int elaFrame, int curX, int curY, int maxX, int maxY)
{
	key.elapsedFrame = elaFrame;
	key.curFrameX = curX;
	key.curFrameY = curY;
	key.maxFrameX = maxX;
	key.maxFrameY = maxY;
}

void GameNode::SetMoveFrameX(int num, int remainder)
{
	key.elapsedFrame++;
	if (key.elapsedFrame % num == remainder)
	{
		key.curFrameX++;
		key.elapsedFrame = 0;

		if (key.curFrameX == key.maxFrameX)
			key.curFrameX = 0;
	}
}

void GameNode::SetMoveFrameY(int num, int remainder)
{
	key.elapsedFrame++;
	if (key.elapsedFrame % num == remainder)
	{
		key.curFrameY++;
		key.elapsedFrame = 0;

		if (key.curFrameY == key.maxFrameY)
			key.curFrameY = 0;
	}
}

void GameNode::SetMaxFrameDetermine(int num, int remainder)
{
	if (key.maxFrameX > key.maxFrameY)
		SetMoveFrameX(num, remainder);

	else
		SetMoveFrameY(num, remainder);
}

void GameNode::SetFrame2(int elaFrame, int curX, int curY, int maxX, int maxY)
{
	key2.elapsedFrame = elaFrame;
	key2.curFrameX = curX;
	key2.curFrameY = curY;
	key2.maxFrameX = maxX;
	key2.maxFrameY = maxY;
}

void GameNode::SetMoveFrameX2(int num, int remainder)
{
	key2.elapsedFrame++;
	if (key2.elapsedFrame % num == remainder)
	{
		key2.curFrameX++;
		key2.elapsedFrame = 0;

		if (key2.curFrameX == key2.maxFrameX)
			key2.curFrameX = 0;
	}
}

void GameNode::SetMoveFrameY2(int num, int remainder)
{
	key2.elapsedFrame++;
	if (key2.elapsedFrame % num == remainder)
	{
		key2.curFrameY++;
		key2.elapsedFrame = 0;

		if (key2.curFrameY == key2.maxFrameY)
			key2.curFrameY = 0;
	}
}

void GameNode::SetMaxFrameDetermine2(int num, int remainder)
{
	if (key2.maxFrameX > key2.maxFrameY)
		SetMoveFrameX2(num, remainder);

	else
		SetMoveFrameY2(num, remainder);
}

GameNode::KEYFRAME GameNode::GetFrame()
{
	return key;
}

GameNode::HITBOX GameNode::GetHitBox()
{
	return hitBox;
}

void GameNode::SetHitBox(FPOINT fpos, int _width, int _height)
{
	hitBox = { fpos.x - (_width / 2), fpos.y - (_height / 2), fpos.x + (_width / 2), fpos.y + (_height / 2) };
}

void GameNode::HitBoxRender(HDC hdc, HITBOX hitBox)
{
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}
