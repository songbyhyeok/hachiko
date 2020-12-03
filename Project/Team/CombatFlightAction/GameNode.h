#pragma once
#include "pch.h"

class GameNode
{
protected:
	typedef struct tagFPOINT
	{
		float x;
		float y;
	} FPOINT, *PFPOINT;

	typedef struct tagHITBOX
	{
		float left;
		float top;
		float right;
		float bottom;

	}HITBOX, *PHITBOX;

	typedef struct tagBASEFRAME
	{
		int elapsedFrame;
		int curFrameX;
		int curFrameY;
		int maxFrameX;
		int maxFrameY;
	}KEYFRAME, *PKEYFRAME;

	typedef struct tagBASEFRAME2
	{
		int elapsedFrame;
		int curFrameX;
		int curFrameY;
		int maxFrameX;
		int maxFrameY;
	}KEYFRAME2, *PKEYFRAME2;

protected:
	FPOINT pos;
	HITBOX hitBox;
	KEYFRAME key;
	KEYFRAME key2;
	int width;
	int height;

	HPEN		hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetPos(FPOINT pt);
	FPOINT GetPos();

	void SetFrame(int elaFrame, int curX, int curY, int maxX, int maxY);
	void SetMoveFrameX(int num, int remainder);
	void SetMoveFrameY(int num, int remainder);
	void SetMaxFrameDetermine(int num, int remainder);

	void SetFrame2(int elaFrame, int curX, int curY, int maxX, int maxY);
	void SetMoveFrameX2(int num, int remainder);
	void SetMoveFrameY2(int num, int remainder);
	void SetMaxFrameDetermine2(int num, int remainder);
	
	KEYFRAME GetFrame();

	void SetHitBox(FPOINT fpos, int _width, int _height);
	void HitBoxRender(HDC hdc, HITBOX hitBox);
	virtual HITBOX GetHitBox();

	GameNode();
	~GameNode();
};

