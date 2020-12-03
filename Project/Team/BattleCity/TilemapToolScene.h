#pragma once
#include "GameNode.h"
// 640 * 288 (20 9)




typedef struct tagSampleTile
{
	RECT rcTile;
	int frameX;
	int frameY;

}SAMPLE_TILE_INFO;

typedef struct tagObjectTile
{
	RECT rcTile;
	int frameX;
	int frameY;

}OBJECT_TILE_INFO;

typedef struct tagTile
{
	TERRAIN terrain;
	TERRAIN objterrain;
	RECT rcTile;
	int frameX;
	int frameY;
	int objframeX;
	int objframeY;

}TILE_INFO;

typedef struct tagSelectTile
{
	int frameX;
	int frameY;

}SELECT_TILE_INFO;

class Button;
class ChangeScene;
class TilemapToolScene : public GameNode
{
private:
	Image* sampleTileImage;
	Image* objSampleTileImage;
	Image* blackBG;
	// 샘플타일의 정보 (시작프레임포인트, rect 정보)
	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	OBJECT_TILE_INFO objectTileInfo[OBJECT_TILE_X*OBJECT_TILE_Y];
	// 메인타일의 정보 (rect 정보, 샘플타일의 시작프레임포인트, 속성)
	TILE_INFO tileInfo[TILE_X * TILE_Y];
	// 선택된 타일의 정보 (시작프레임포인트
	SELECT_TILE_INFO selectTileInfo;
	SELECT_TILE_INFO selectTileInfos[2];
	ARGUMENT_INFO* args;
	ARGUMENT_INFO* args1;
	ChangeScene* changescene;

	int minX, minY, maxX, maxY;
	int dragSizeX;
	int dragSizeY;
	bool isDownSampleArea;

	// 세이브 , 로드
	RECT rcSave;
	RECT rcLoad;
	RECT rcChange;

	Button* savebutton;
	Button* loadbutton;
	Button* morebutton;
	Button* exitbutton;

public:

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Save();
	void Load();
	void Change();

	bool GetisObject();
	void SetisObject(bool isobject);
	TILE_INFO* GetTile_Info() { return tileInfo; }
	TilemapToolScene();
	~TilemapToolScene();
};

