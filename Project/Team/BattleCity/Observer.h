#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Observer : public SingletonBase<Observer>
{

	BATTLE_TILE_INFO* tileinfo;
public:

	void SetTileInfo(BATTLE_TILE_INFO* _tileinfo) { tileinfo = _tileinfo; }
	BATTLE_TILE_INFO* GetTileInfo() { return tileinfo; }

	Observer();
	~Observer();
};

