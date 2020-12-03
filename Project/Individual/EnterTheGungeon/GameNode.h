#pragma once

#include "pch.h"
#include "Image.h"

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagFRECT
{
	float left;
	float top;
	float right;
	float bottom;
} FRECT, *PFRECT;

typedef struct tagBASEFRAME
{
	int elapsedFrame;
	int curFrameX;
	int curFrameY;
	int maxFrameX;
	int maxFrameY;
}KEYFRAME, *PKEYFRAME;

class GameNode
{
protected:
	FPOINT pos;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetFrame(PKEYFRAME _key, int elaFrame, int curX, int curY, int maxX, int maxY);
	void SetMoveFrameX(PKEYFRAME _key, int num, int remainder);
	void SetMoveFrameY(PKEYFRAME _key, int num, int remainder);

	void SetPos(FPOINT fp);
	FPOINT GetPos();

	GameNode();
	~GameNode();
};

