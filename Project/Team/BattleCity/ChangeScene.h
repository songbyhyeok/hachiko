#pragma once
#include "pch.h"


class GameNode;
class TilemapToolScene;
class BattleScene;
class ChangeScene
{
private:
	TilemapToolScene* tilemaptoolscene;
	BattleScene* battlescene;
public:
	void BattleButton(const char* sceneName, const char* lodingName);
	void QuitButton(const char* sceneName, const char* lodingName);
	void Save(const char * sceneName, const char * lodingName);
	void Load(const char * sceneName, const char * lodingName);
	void BattleLoad(const char * sceneName, const char * lodingName);

	void Change(const char * sceneName, const char * lodingName);


	void SetTilemapToolScene(TilemapToolScene* tile) {	tilemaptoolscene = tile	;}
	void SetBattleScene(BattleScene* battle) { battlescene = battle; }
	

};