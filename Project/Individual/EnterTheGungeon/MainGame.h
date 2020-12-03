#pragma once

#include "GameNode.h"

class GameNode;
class MainGame : public GameNode
{
private:
	HDC hdc;
	bool isInit;

	GameNode* titleScene;
	GameNode* loadingScene;
	GameNode* battleScene;
	GameNode* mapTool;

	Image* cursor;
	Image* backBuffer;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

