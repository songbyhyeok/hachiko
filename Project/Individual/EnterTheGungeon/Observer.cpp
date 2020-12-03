#include "Observer.h"

void Observer::SetTileInfo(PTILE_INF _ptileInfo)
{
	pTileInfo = _ptileInfo;
}

PTILE_INF Observer::GetTileInfo()
{
	return pTileInfo;
}

Observer::Observer()
{
}

Observer::~Observer()
{
}
