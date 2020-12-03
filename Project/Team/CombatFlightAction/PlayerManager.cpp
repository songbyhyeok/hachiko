#include "PlayerManager.h"
#include "MissileManager.h"
#include "UI.h"
#include "Player.h"

HRESULT PlayerManager::Init()
{
	GameNode::Init();

	player = nullptr;

	select = -1;

	isMissileMgr = new MissileManager();
	isMissileMgr->Init();	
	isMissileMgr->SetTargetMode(true);
	isMissileMgr->SetTarget(nullptr);

	isSelect = false;
	isPlayer = false;

	return S_OK;
}

void PlayerManager::Release()
{
	if (isSelect)
	{
		player->Release();
		SAFE_DELETE(player);
	}

	isMissileMgr->Release();
	SAFE_DELETE(isMissileMgr);
}

void PlayerManager::Update()
{
	if (isSelect)
		player->Update();	
}

void PlayerManager::Render(HDC hdc)
{
	if (isSelect)
		player->Render(hdc);
}

void PlayerManager::SelectMode()
{
	if (!isPlayer)
	{
		if (select == -1)
		{
			player = nullptr;
			isSelect = false;
		}

		else if (select == HYEOK)
		{
			player = new Hyeok();
			isSelect = true;
		}

		else if (select == DONGKYUNE)
		{
			player = new Dongkyune();
			isSelect = true;
		}

		else if (select == JUNHYEOK)
		{
			player = new Junhyeok();
			isSelect = true;
		}

		if (isSelect)
		{
			player->Init();
			isMissileMgr->SetOwner(player);
			isPlayer = true;
		}
	}

}

void PlayerManager::SetSelect(int _select)
{
	select = _select;
}

int PlayerManager::GetSelect()
{
	return select;
}

void PlayerManager::SetIsSelect(bool _isSelect)
{
	isSelect = _isSelect;
}

bool PlayerManager::GetIsSelect()
{
	return isSelect;
}

Player * PlayerManager::GetPlayerInf()
{
	return player;
}

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

