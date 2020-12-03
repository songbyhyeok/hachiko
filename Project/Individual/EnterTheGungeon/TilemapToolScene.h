#pragma once

#include "GameNode.h"

#define TILE_MAP_X WINSIZE_X + 600
#define TILE_MAP_Y WINSIZE_Y
#define SAMPLE_TILE_X 10 
#define SAMPLE_TILE_Y 3
#define TILE_SIZE 60
#define MAIN_TILE_X 20
#define MAIN_TILE_Y 15

enum TERRAIN
{
	EMPTY,
	WALL,
	BRICK,
	TILE,
	MAGMA
};

typedef struct tagSelectTile
{
	int frameX;
	int frameY;
	TERRAIN sTerrain;
}SELECT_TILE_INF, *PSELECT_TILE_INF;

typedef struct tagSampleTile
{
	RECT rcTile;
	int frameX;
	int frameY;
	TERRAIN sTerrain;
}SAMPLE_TILE_INF, *PSAMPLE_TILE_INF;

typedef struct tagTile
{
	TERRAIN sTerrain;
	TERRAIN objTerrain;
	RECT rcTile;
	int sFrameX;
	int sFrameY;
	int objFrameX;
	int objFrameY;
}TILE_INF, *PTILE_INF;

typedef struct tagSL
{
	const char* sceneName;
	const char* loadingName;
} SL_INF, *PSL_INF;

class Button;
class ChangeScene;
class TilemapToolScene : public GameNode
{
private:
	Image* black;
	Image* sample;
	
	PSL_INF psl;

	PSAMPLE_TILE_INF sTileInf;
	PTILE_INF tileInf;
	SELECT_TILE_INF selectTile;
	PSELECT_TILE_INF selectTiles;

	Button* save;
	Button* load;
	Button* more;
	Button* exit;

	int dragSizeX, dragSizeY;
	int minX, minY, maxX, maxY;
	bool isDownSampleArea;
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTileInf(PTILE_INF pTilefinf);
	void SetTileInfTerrain(TERRAIN terrain);
	void SetTileInfRect(RECT rect);
	PTILE_INF GetTileInf();

	TilemapToolScene();
	~TilemapToolScene();
};

