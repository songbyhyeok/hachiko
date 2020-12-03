#include "BattleScene.h"
#include "Image.h"
#include "EnemyManager.h"
#include "TilemapToolScene.h"
#include "Tank.h"
#include "Observer.h"
#include "Button.h"
#include "ChangeScene.h"

HRESULT BattleScene::Init()
{
	bool enemy1 = false;
	bool enemy2 = false;
	bool enemy3 = false;

	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_BATTLE_MAP_X, WINSIZE_BATTLE_MAP_Y);
	
	bg = ImageManager::GetSingleton()->AddImage("battlesceneBG", "Image/battlesceneBG.bmp", 940, 900);
	blackbg = ImageManager::GetSingleton()->AddImage("battleblackBG", "Image/blackBG.bmp", 780, 780);
	ImageManager::GetSingleton()->AddImage("로드버튼2", "Image/load2.bmp", 0.0f, 0.0f, 100, 80, 1, 2, true, RGB(255, 0, 255));

	DWORD	readByte;
	HANDLE	HFile;

	HFile = CreateFile("Save/test2.map", GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(HFile, &tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);

	CloseHandle(HFile);

	Observer::GetSingleton()->SetTileInfo(tileInfo);

	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/material.bmp", 0, 0,
		210, 30, SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));

	objSampleTileImage = ImageManager::GetSingleton()->AddImage("오브젝트타일", "Image/object.bmp", 0, 0,
		360, 60, OBJECT_TILE_X, OBJECT_TILE_Y, true, RGB(255, 0, 255));

	
	// 적

	
	tank = new Tank();
	tank->SetBattleScene(this);
	tank->Init(720, 720);
	
	enemynum = 0;
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (tileInfo[i].objterrain == ENEMYTANK1)
		{
			enemy1 = true;
		}

		else if (tileInfo[i].objterrain == ENEMYTANK2)
		{
			enemy2 = true;
		}

		else if (tileInfo[i].objterrain == ENEMYTANK3)
		{
			enemy3 = true;
		}
	}
	if (enemy1)
	{
		enemyMgr = new DefalutEnemyManager();
		enemyMgr->SetTankInf(tank);
		enemyMgr->SetBattleScene(this);
		enemyMgr->Init();
		enemynum += DEFAULTTANKNUM;
	}
	
	if (enemy2)
	{
		enemyMgr2 = new SpeedEnemyManager();
		enemyMgr2->SetTankInf(tank);
		enemyMgr2->SetBattleScene(this);
		enemyMgr2->Init();
		enemynum += SPEEDTANKNUM;
	}
	
	if (enemy3)
	{
		enemyMgr3 = new PowerEnemyManager();
		enemyMgr3->SetTankInf(tank);
		enemyMgr3->SetBattleScene(this);
		enemyMgr3->Init();
		enemynum += POWERTANKNUM;
	}
	
	POINT downframepoint = { 0,1 };
	POINT upframepoint = { 0,0 };

	changescene = new ChangeScene();
	changescene->SetBattleScene(this);

	loadbutton = new Button();
	loadbutton->Init("로드버튼2", WINSIZE_BATTLE_MAP_X - 50, WINSIZE_BATTLE_MAP_Y - 50, downframepoint, upframepoint);

	ARGUMENT_INFO* args;
	args = new ARGUMENT_INFO();
	args->sceneName = "";
	args->loadingName = "";

	loadbutton->SetButtonFunc(changescene, &ChangeScene::BattleLoad, args);
	enemyNum = ImageManager::GetSingleton()->AddImage("enemynum", "Image/enemyNum1.bmp", 30, 30, true, RGB(255, 0, 255));
	

	EnemyTime = 0;

	SAFE_DELETE(args);
	return S_OK;
}

void BattleScene::Release()
{
	if (enemyMgr)
	{
		enemyMgr->Release();
		SAFE_DELETE(enemyMgr);
	}
	
	if (enemyMgr2)
	{
		enemyMgr2->Release();
		SAFE_DELETE(enemyMgr2);
	}
	
	if (enemyMgr3)
	{
		enemyMgr3->Release();
		SAFE_DELETE(enemyMgr3);
	}
	
	if (tank)
	{
		tank->Release();
		SAFE_DELETE(tank);
	}
	
	if (loadbutton)
	{
		loadbutton->Release();
		SAFE_DELETE(loadbutton);
	}

	SAFE_ARR_DELETE(enemyNum);

}

void BattleScene::Update()
{
	if (loadbutton)
	{
		loadbutton->Update();
	}

	SoundManager::GetSingleton()->Update();
	EnemyTime += TimeManager::GetSingleton()->GetDeltaTime();
		
	if (tank)
	{
		tank->Update();
	}
		
	if (enemyMgr)
	{
		enemyMgr->Update();
	}

	if (enemyMgr2)
	{
		enemyMgr2->Update();
	}

	if (enemyMgr3)
	{
		enemyMgr3->Update();
	}

	if (EnemyTime > 7)
	{		
		EnemyTime = 0;
		if(enemyMgr)
			enemyMgr->AddEnemy(0, 0);
		if (enemyMgr2)
			enemyMgr2->AddEnemy(0, 0);
		if (enemyMgr3)
			enemyMgr3->AddEnemy(0, 0);
	}

	
	updateCount++;

	if (updateCount % 10 == 9)
	{
		updateCount = 0;
		for (int i = 0; i < TILE_X* TILE_Y; i++)
		{
			if (tileInfo[i].frameX == 4)
			{
				tileInfo[i].frameX = 5;
			}

			else if (tileInfo[i].frameX == 5)
			{
				tileInfo[i].frameX = 4;
			}
		}
	}

	if (enemynum <= 0)
	{
		SceneManager::GetSingleton()->ChangeScene("Ending");
	}

	if (tank->GetLife() == 0 || gameOver)
	{
		SceneManager::GetSingleton()->ChangeScene("GameOver", "loadingscene");
	}
}

void BattleScene::Render(HDC hdc)
{
	bg->Render(hdc, 0, 0);
	blackbg->Render(hdc, 0, 0);
	for (int i = 0; i < TILE_X* TILE_Y; i++)
	{
		if (tileInfo[i].terrain == WATER || tileInfo[i].terrain == ICE)
		{
			sampleTileImage->FrameRender(hdc, (tileInfo[i].rcTile.left + TILESIZE / 2), (tileInfo[i].rcTile.top + TILESIZE / 2),
				tileInfo[i].frameX, tileInfo[i].frameY);
		}
		
	}

	if (tank)
	{
		tank->Render(hdc);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);

		//enemyMgr->SetLife(0);

		
	}

	if (enemyMgr2)
	{
		enemyMgr2->Render(hdc);
	}

	if (enemyMgr3)
	{
		enemyMgr3->Render(hdc);
	}
	
	
	

	for (int i = 0; i < TILE_X* TILE_Y; i++)
	{
		if (tileInfo[i].terrain != WATER && tileInfo[i].terrain != ICE)
		{
			sampleTileImage->FrameRender(hdc, (tileInfo[i].rcTile.left + TILESIZE / 2), (tileInfo[i].rcTile.top + TILESIZE / 2),
				tileInfo[i].frameX, tileInfo[i].frameY);
		}
				
		if (tileInfo[i].objterrain < 7)
		{
			objSampleTileImage->FrameRender(hdc, (tileInfo[i].rcTile.left + TILESIZE / 2), (tileInfo[i].rcTile.top + TILESIZE / 2),
				tileInfo[i].objframeX, tileInfo[i].objframeY);
		}
		
				
	}

	//score = 100;

		
	if (enemyNum)
		for (int i = 0; i < enemynum; i++)
		{
			enemyNum->Render(hdc, i%2 * 30 + 810, i /2 * 30 + 50);
		}

	if(loadbutton)
		loadbutton->Render(hdc);
}

void BattleScene::GameInit()
{
	tank->Init(720, 720);
	bool enemy1 = false;
	bool enemy2 = false;
	bool enemy3 = false;
	enemynum = 0;

	
	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (tileInfo[i].objterrain == ENEMYTANK1)
		{
			enemy1 = true;
		}

		else if (tileInfo[i].objterrain == ENEMYTANK2)
		{
			enemy2 = true;
		}

		else if (tileInfo[i].objterrain == ENEMYTANK3)
		{
			enemy3 = true;
		}
	}

	if (enemyMgr)
	{
		enemyMgr->Release();
		SAFE_DELETE(enemyMgr);
	}

	if (enemyMgr2)
	{
		enemyMgr2->Release();
		SAFE_DELETE(enemyMgr2);
	}

	if (enemyMgr3)
	{
		enemyMgr3->Release();
		SAFE_DELETE(enemyMgr3);
	}
	if (enemy1)
	{
	

		enemyMgr = new DefalutEnemyManager();
		enemyMgr->SetTankInf(tank);
		enemyMgr->SetBattleScene(this);
		enemyMgr->Init();
		enemynum += DEFAULTTANKNUM;
	}

	if (enemy2)
	{
		
		enemyMgr2 = new SpeedEnemyManager();
		enemyMgr2->SetTankInf(tank);
		enemyMgr2->SetBattleScene(this);
		enemyMgr2->Init();
		enemynum += SPEEDTANKNUM;
	}

	if (enemy3)
	{
		

		enemyMgr3 = new PowerEnemyManager();
		enemyMgr3->SetTankInf(tank);
		enemyMgr3->SetBattleScene(this);
		enemyMgr3->Init();
		enemynum += POWERTANKNUM;
	}
	tank->SetLife(3);
	EnemyTime = 0;
}



BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}
