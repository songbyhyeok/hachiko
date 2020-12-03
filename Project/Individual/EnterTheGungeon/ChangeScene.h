#pragma once

#include "SingletonBase.h"

enum STAGE
{
	STAGE1, STAGE2, STAGE3, STAGE4
};


class TilemapToolScene;
class BattleScene;
class ChangeScene : public SingletonBase<ChangeScene>
{
private:
	TilemapToolScene* mapTool;
	BattleScene* battleScene;

public:
	void Save();
	void Load();
	void stage1();
	void stage2();
	void tunnel();
	void boss();
	void ChangeButton(const char* sceneName, const char* lodingName);
	void Quit(const char * sceneName, const char * lodingName);
	void QuitButton(const char* sceneName, const char* lodingName);
	void SetMapTool(TilemapToolScene* _mapTool);
	void SetBattleScene(BattleScene* battle);
};

