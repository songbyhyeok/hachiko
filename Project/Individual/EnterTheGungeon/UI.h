#pragma once

#include "GameNode.h"

class Player;
class UI : public GameNode
{
private:
	Image * heart;
	PKEYFRAME heartKey;

	Image * bullet;
	Image * power;
	Image * speed;
	Image * time;

	Player* player;

	HFONT hFont, oldFont;
	char szText[128];

	FRECT reloadBox;
	FRECT reloadGauge;

	int gaugeX, gaugeY;

	HBRUSH hBrush;

	int elapsedTime;
	int count;

	bool reload;
	bool isReady;

	int hit;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void ReloadUI();

	void SetReload(bool _reload);
	bool GetReload();

	void SetIsReady(bool _isReady);
	bool GetIsReady();

	void SetPlayer(Player* _player);

};

