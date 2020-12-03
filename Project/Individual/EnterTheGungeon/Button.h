#pragma once

#include "GameNode.h"
#include "TilemapToolScene.h"

enum BUTTON_STATE
{
	NONE,
	UP,
	DOWN
};

class Image;
class ChangeScene;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* img;
	RECT rc;
	POINT btnUpPoint;
	POINT btnDownPoint;
	ChangeScene* changeScene;
	void(ChangeScene::*slbuttonFunc)();
	void(ChangeScene::*buttonFunc)(const char*, const char*);
	PSL_INF psl;

public:
	HRESULT Init(const char * imageName, const char * location, float posX, float posY, POINT downPoint, POINT upPoint);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetButtonFunc(ChangeScene* cS, void(ChangeScene::* bF)());
	void SetButtonFunc(ChangeScene* cS, void(ChangeScene::* bF)(const char *, const char *), PSL_INF _psl);

	Button();
	~Button();
};

