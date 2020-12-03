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

void GameNode::SetFrame(PKEYFRAME _key, int elaFrame, int curX, int curY, int maxX, int maxY)
{
	_key->elapsedFrame = elaFrame;
	_key->curFrameX = curX;
	_key->curFrameY = curY;
	_key->maxFrameX = maxX;
	_key->maxFrameY = maxY;
}

void GameNode::SetMoveFrameX(PKEYFRAME _key, int num, int remainder)
{
	_key->elapsedFrame++;
	if (_key->elapsedFrame % num == remainder)
	{
		_key->curFrameX++;
		_key->elapsedFrame = 0;

		if (_key->curFrameX == _key->maxFrameX)
			_key->curFrameX = 0;
	}
}

void GameNode::SetMoveFrameY(PKEYFRAME _key, int num, int remainder)
{
	_key->elapsedFrame++;
	if (_key->elapsedFrame % num == remainder)
	{
		_key->curFrameY++;
		_key->elapsedFrame = 0;

		if (_key->curFrameY == _key->maxFrameY)
			_key->curFrameY = 0;
	}
}

void GameNode::SetPos(FPOINT fp)
{
	pos = fp;
}

FPOINT GameNode::GetPos()
{
	return pos;
}

GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}
