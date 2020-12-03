#pragma once

#include "GameNode.h"

class Image;
class SieKensou;
class SieKensou2;
class Ground;
class UI;
class Collision;

class MainGame : public GameNode
{
private:
	HANDLE hTimer;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	HDC hdc;
	PAINTSTRUCT ps;

	int mousePosX, mousePosY;
	int score;
	char szText[NAME_SIZE];
	char szScore[NAME_SIZE];
	bool isInit; //���ΰ��� ������ ���ÿ� ������Ʈ�� ������ ���
	int elapsedFrame;
	int curFrame;

	Image * backBuffer;
	Image * bg;

	SieKensou * sieKensou;
	SieKensou2 * sieKensou2;

	UI * isUI;
	Collision * collision;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

