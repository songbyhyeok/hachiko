#pragma once
#include "GameNode.h"

class TilemapToolScene;
class KofPlayer;
class Tank;
class Missile;
class Enemy;
class TitleScene;
class BattleScene;
class LoadingScene;
class ChangeScene;
class GameOverScene;
class EndingScene;
class MainGame : public GameNode
{
private:
	string scene[4] = { "Titlescene" ,"Battlescene", "GameOver", "Ending" };
	int scenenum;
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	Image* backBuffer;
	//Enemy* enemy;
	
	TilemapToolScene* tilemapToolScene;
	TitleScene* titlescene;
	BattleScene* battlescene;
	LoadingScene* loadingscene;

	GameOverScene* gameOverScene;
	EndingScene* endingScene;

	/*TitleScene* titlescene;
	BattleScene* battlescene;
	LoadingScene* loadingscene;*/
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);
	bool CheckCollision(Missile* m1, Missile* m2);

	MainGame();
	~MainGame();
};

