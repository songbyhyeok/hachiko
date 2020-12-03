#include "TilemapToolScene.h"
#include "Button.h"
#include "ChangeScene.h"
#include "Image.h"

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, TILE_MAP_X, TILE_MAP_Y);

	black = ImageManager::GetSingleton()->AddImage("블랙타일", "Image/maptool/black.bmp", WINSIZE_X, WINSIZE_Y);

	sample = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/maptool/temp.bmp", 0, 0,
		600, 180, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));

	//우측 샘플타일
	sTileInf = new SAMPLE_TILE_INF[SAMPLE_TILE_X * SAMPLE_TILE_Y];

	//좌측 메인타일
	tileInf = new TILE_INF[MAIN_TILE_X * MAIN_TILE_Y];

	selectTiles = new SELECT_TILE_INF[2];

	POINT downPoint = { 0,0 };
	POINT upPoint = { 0,1 };

	psl = new SL_INF();
	psl->sceneName = "타이틀";
	psl->loadingName = "로딩";

	ChangeScene::GetSingleton()->SetMapTool(this);

	save = new Button();
	load = new Button();
	more = new Button();
	exit = new Button();

	save->Init("세이브", "Image/maptool/save.bmp", WINSIZE_X + (115 / 2), WINSIZE_Y - 140, downPoint, upPoint);
	load->Init("로드", "Image/maptool/load.bmp", 6 + WINSIZE_X + 115 + (115 / 2), WINSIZE_Y - 140, downPoint, upPoint);
	more->Init("전환", "Image/maptool/change.bmp", 12 + WINSIZE_X + 115 * 2 + (115 / 2), WINSIZE_Y - 140, downPoint, upPoint);
	exit->Init("종료", "Image/maptool/exit.bmp", 20 + WINSIZE_X + 115 * 3 + (115 / 2), WINSIZE_Y - 140, downPoint, upPoint);

	save->SetButtonFunc(ChangeScene::GetSingleton(), &ChangeScene::Save);
	load->SetButtonFunc(ChangeScene::GetSingleton(), &ChangeScene::Load);
	more->SetButtonFunc(ChangeScene::GetSingleton(), &ChangeScene::Quit, psl);
	exit->SetButtonFunc(ChangeScene::GetSingleton(), &ChangeScene::Quit, psl);
	
	// 우측 샘플타일 정보
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			sTileInf[i * SAMPLE_TILE_X + j].frameX = j;
			sTileInf[i * SAMPLE_TILE_X + j].frameY = i;

			SetRect(&sTileInf[i * SAMPLE_TILE_X + j].rcTile, 
				TILE_MAP_X - sample->GetWidth() + j * TILE_SIZE, 
				i * TILE_SIZE,
				TILE_MAP_X - sample->GetWidth() + j * TILE_SIZE + TILE_SIZE,
				i * TILE_SIZE + TILE_SIZE);
		}
	}

	//우측 샘플타일 초기화
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			if (i == 0)
				sTileInf[i * SAMPLE_TILE_X + j].sTerrain = BRICK;

			if (i == 1 && 0 < j && j < 5)
				sTileInf[i * SAMPLE_TILE_X + j].sTerrain = WALL;

			else
				sTileInf[i * SAMPLE_TILE_X + j].sTerrain = TILE;
		}
	}

	// 좌측에 메인타일 정보
	for (int i = 0; i < MAIN_TILE_Y; i++)
	{
		for (int j = 0; j < MAIN_TILE_X; j++)
		{
			SetRect(&tileInf[i * MAIN_TILE_X + j].rcTile,
				j * TILE_SIZE, 
				i * TILE_SIZE,
				j * TILE_SIZE + TILE_SIZE, 
				i * TILE_SIZE + TILE_SIZE);
		}
	}

	for (int i = 0; i < MAIN_TILE_X * MAIN_TILE_Y; i++)
	{
		tileInf[i].sFrameX = 0;
		tileInf[i].sFrameY = 0;
		tileInf[i].sTerrain = EMPTY;
		tileInf[i].objFrameX = 0;
		tileInf[i].objFrameY = 0;
		tileInf[i].objTerrain = EMPTY;
	}

	selectTile.frameX = selectTile.frameY = 0;
	selectTiles[0].frameY = selectTiles[0].frameX = 0;
	selectTiles[1].frameY = selectTiles[1].frameX = 0;

	dragSizeX = dragSizeY = 0;
	minX = minY = maxX = maxY = 0;

	isDownSampleArea = false;

	return S_OK;
}

void TilemapToolScene::Release()
{
	if (exit)
	{
		exit->Release();
		SAFE_DELETE(exit);
	}

	if (more)
	{
		more->Release();
		SAFE_DELETE(more);
	}

	if (load)
	{
		load->Release();
		SAFE_DELETE(load);
	}

	if (save)
	{
		save->Release();
		SAFE_DELETE(save);
	}

	if (psl)
	{
		SAFE_DELETE(psl);
	}

	if (selectTiles)
	{
		SAFE_ARR_DELETE(selectTiles);
	}

	if (tileInf)
	{
		SAFE_ARR_DELETE(tileInf);
	}

	if (sTileInf)
	{
		SAFE_ARR_DELETE(sTileInf);
	}	
}

void TilemapToolScene::Update()
{
	if (save)
		save->Update();

	if (load)
		load->Update();

	if (more)
		more->Update();

	if (exit)
		exit->Update();

	if (!exit)
		return;

	//타일을 설치할 때 연속적이 가능하게
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
		{
			if (PtInRect(&sTileInf[i].rcTile, g_ptMouse))
			{
				selectTile.frameX = sTileInf[i].frameX;
				selectTile.frameY = sTileInf[i].frameY;

				selectTiles[0].frameX = sTileInf[i].frameX;
				selectTiles[0].frameY = sTileInf[i].frameY;

				isDownSampleArea = true;
				break;
			}
		}
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		int x = 0, y = 0;
		int tempX = 0, tempY = 0;

		if (isDownSampleArea)
		{
			for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
			{
				if (PtInRect(&sTileInf[i].rcTile, g_ptMouse))
				{
					selectTiles[1].frameX = sTileInf[i].frameX;
					selectTiles[1].frameY = sTileInf[i].frameY;

					minX = min(selectTiles[0].frameX, selectTiles[1].frameX);
					maxX = max(selectTiles[0].frameX, selectTiles[1].frameX);
					minY = min(selectTiles[0].frameY, selectTiles[1].frameY);
					maxY = max(selectTiles[0].frameY, selectTiles[1].frameY);

					dragSizeX = maxX - minX;
					dragSizeY = maxY - minY;

					isDownSampleArea = false;
					break;
				}
			}
		}

		//메인타일에 드래그정보
		for (int i = 0; i < MAIN_TILE_X * MAIN_TILE_Y; i++)
		{
			if (PtInRect(&tileInf[i].rcTile, g_ptMouse))
			{
				tempX = (i % MAIN_TILE_X) + dragSizeX;
				tempY = (i / MAIN_TILE_X) + dragSizeY;

				if (tempY >= MAIN_TILE_Y)
					tempY = MAIN_TILE_Y - 1;

				if (tempX >= MAIN_TILE_X)
					tempX = MAIN_TILE_X - 1;

				for (int j = (i / MAIN_TILE_X); j <= tempY; j++)
				{
					for (int k = (i % MAIN_TILE_X); k <= tempX; k++)
					{
						tileInf[j * MAIN_TILE_X + k].sFrameX = minX + x;
						tileInf[j * MAIN_TILE_X + k].sFrameY = minY + y;

						x++;
					}

					x = 0;

					y++;
				}
			}
		}
	}

	// 메인 타일와 마우스가 충돌하면 
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < MAIN_TILE_X * MAIN_TILE_Y; i++)
		{
			if (PtInRect(&tileInf[i].rcTile, g_ptMouse))
			{
				tileInf[i].sFrameX = selectTile.frameX;
				tileInf[i].sFrameY = selectTile.frameY;

				break;
			}
		}
	}

	// 메인타일 터레인설정
	for (int i = 0; i < MAIN_TILE_X * MAIN_TILE_Y; i++)
	{
		if (tileInf[i].sFrameY == 0)
			tileInf[i].sTerrain = BRICK;

		else if (tileInf[i].sFrameX == 0 &&
			tileInf[i].sFrameY == 2)
			tileInf[i].sTerrain = WALL;

		else if (tileInf[i].sFrameX == 8 &&
			tileInf[i].sFrameY == 2)
		{
			tileInf[i].sTerrain = MAGMA;
		}

		else if (tileInf[i].sFrameX == 1 &&
				tileInf[i].sFrameY == 1)
			{
				tileInf[i].sTerrain = WALL;
			}

		else if (tileInf[i].sFrameX == 2 &&
			tileInf[i].sFrameY == 1)
		{
			tileInf[i].sTerrain = WALL;
		}

		else if (tileInf[i].sFrameX == 3 &&
			tileInf[i].sFrameY == 1)
		{
			tileInf[i].sTerrain = WALL;
		}

		else if (tileInf[i].sFrameX == 4 &&
			tileInf[i].sFrameY == 1)
		{
			tileInf[i].sTerrain = WALL;
		}

		else 
			tileInf[i].sTerrain = TILE;
	}
}

void TilemapToolScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, TILE_MAP_X, TILE_MAP_Y, WHITENESS);
	black->Render(hdc, 0, 0);

	if (save) save->Render(hdc);
	if (load) load->Render(hdc);
	if (more) more->Render(hdc);
	if (exit) exit->Render(hdc);

	sample->Render(hdc, TILE_MAP_X - sample->GetWidth() / 2, sample->GetHeight() / 2);
	for (int i = 0; i <= dragSizeY; i++)
	{
		for (int j = 0; j <= dragSizeX; j++)
		{
			sample->FrameRender(hdc, TILE_MAP_X - sample->GetWidth() + TILE_SIZE / 2+ (j * TILE_SIZE),
				sample->GetHeight() + (i * TILE_SIZE + TILE_SIZE / 2),
				minX + j, minY + i);
		}
	}

	// 왼쪽 메인타일
	for (int i = 0; i < MAIN_TILE_X * MAIN_TILE_Y; i++)
	{
		sample->FrameRender(hdc, 
			tileInf[i].rcTile.left + TILE_SIZE / 2,
			tileInf[i].rcTile.top + TILE_SIZE / 2,
			tileInf[i].sFrameX, tileInf[i].sFrameY);
	}
}

void TilemapToolScene::SetTileInf(PTILE_INF pTilefinf)
{
	tileInf = pTilefinf;
}

void TilemapToolScene::SetTileInfTerrain(TERRAIN terrain)
{
	tileInf->sTerrain = terrain;
}

void TilemapToolScene::SetTileInfRect(RECT rect)
{
	tileInf->rcTile = rect;
}

PTILE_INF TilemapToolScene::GetTileInf()
{
	return &(*tileInf);
}

TilemapToolScene::TilemapToolScene()
{
}

TilemapToolScene::~TilemapToolScene()
{
}
