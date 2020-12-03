#pragma once

#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	Image* main;

	RECT playRect;
	RECT mapToolRect;
	RECT optionRect;
	RECT exitRect;

	RECT curRect;

	char szText[128];
	
	int state;

	int curFrameX;
public:
	virtual HRESULT Init();	
	virtual void Release();	
	virtual void Update();		
	virtual void Render(HDC hdc);

	void LbuttonSetting(RECT rect);

	void Play();
	void Maptool();
	void Option();
	void Exit();

	TitleScene();
	~TitleScene();
};

