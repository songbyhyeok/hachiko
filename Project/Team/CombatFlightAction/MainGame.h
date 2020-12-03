#pragma once
#include "GameNode.h"

class Image;
class GameManager;

class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	Image* backBuffer;

	GameManager * gameMgr;

	float volume;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);
	//void CheckCollision(SpaceShip * m1, EnemyManager * m2);

	MainGame();
	~MainGame();
};

