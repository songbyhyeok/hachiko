#pragma once

#include "GameNode.h"

class Player;
class MissileManager;
class UI;
class PlayerManager : public GameNode
{
private:
	Player * player;
	MissileManager * isMissileMgr;
	UI * isUI;

	int select;

	bool isSelect;
	bool isPlayer;

public:
	enum tagPlayer
	{
		HYEOK, DONGKYUNE, JUNHYEOK, PLAYER_NUM
	};

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SelectMode();

	void SetSelect(int _select);
	int GetSelect();

	void SetIsSelect(bool _isSelect);
	bool GetIsSelect();

	void SetIsPlayer(bool _isPlayer) { isPlayer = _isPlayer; }
	bool GetIsPlayer() { return isPlayer; }

	Player* GetPlayerInf();
	MissileManager * GetMissileInf() { return isMissileMgr; }

	PlayerManager();
	~PlayerManager();
};

