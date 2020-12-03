#pragma once

#include "SingletonBase.h"
#include "TilemapToolScene.h"

class Observer : public SingletonBase<Observer>
{
private:
	PTILE_INF pTileInfo;

public:
	void SetTileInfo(PTILE_INF)


	Observer();
	~Observer();
};

