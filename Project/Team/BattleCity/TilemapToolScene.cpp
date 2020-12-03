#include "TilemapToolScene.h"
#include "Image.h"
#include "macroFunction.h"
#include "Button.h"
#include "ChangeScene.h"
bool isObject = false;

HRESULT TilemapToolScene::Init()
{
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y);
	sampleTileImage = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/material.bmp", 0, 0,
		210, 30, SAMPLE_TILE_X, SAMPLE_TILE_Y,true, RGB(255, 0, 255));

	objSampleTileImage = ImageManager::GetSingleton()->AddImage("오브젝트타일", "Image/object.bmp", 0, 0,
		360, 60, OBJECT_TILE_X, OBJECT_TILE_Y, true, RGB(255, 0, 255));

	blackBG = ImageManager::GetSingleton()->AddImage("battleblackBG", "Image/blackBG.bmp", 780, 780);
	isDownSampleArea = false;

	rcSave = GetRectToCenter(100, WINSIZE_TILE_MAP_Y - 100, 184, 40);

	rcLoad = GetRectToCenter(300, WINSIZE_TILE_MAP_Y - 100, 184, 40);

	rcChange = GetRectToCenter(500, WINSIZE_TILE_MAP_Y - 100, 184, 40);

	ImageManager::GetSingleton()->AddImage("세이브버튼", "Image/save.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("로드버튼", "Image/load.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("체인지버튼", "Image/change.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("나가기버튼", "Image/exit.bmp", 0.0f, 0.0f, 184, 80, 1, 2, true, RGB(255, 0, 255));

	POINT downframepoint = { 0,1 };
	POINT upframepoint = { 0,0 };

	args = new ARGUMENT_INFO();
	args->sceneName = "";
	args->loadingName = "";

	args1 = new ARGUMENT_INFO();
	args1->sceneName = "Titlescene";
	args1->loadingName = "loadingScene";

	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;
	selectTileInfos[0].frameX = 0;
	selectTileInfos[0].frameY = 0;
	selectTileInfos[1].frameX = 0;
	selectTileInfos[1].frameY = 0;

	minX = 0, minY = 0, maxX = 0, maxY = 0;
	dragSizeX = 0;
	dragSizeY = 0;
	// 오른쪽에 샘플 타일의 Rect를 설정한다.
	for (int i = 0; i < SAMPLE_TILE_Y; i++)
	{
		for (int j = 0; j < SAMPLE_TILE_X; j++)
		{
			sampleTileInfo[i*SAMPLE_TILE_X + j].frameX = j;
			sampleTileInfo[i*SAMPLE_TILE_X + j].frameY = i;


			// 오른쪽에 샘플 타일의 Rect를 설정한다.
			SetRect(&sampleTileInfo[i*SAMPLE_TILE_X + j].rcTile, WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth() + j * TILESIZE, i*TILESIZE,
				WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth() + j * TILESIZE + TILESIZE, i*TILESIZE + TILESIZE);

			// 왼쪽에 메인 타일 Rect를 설정한다.
			for (int i = 0; i < TILE_Y; i++)
			{
				for (int j = 0; j < TILE_X; j++)
				{
					SetRect(&tileInfo[i*TILE_X + j].rcTile, j*TILESIZE, i*TILESIZE,
						j*TILESIZE + TILESIZE, i*TILESIZE + TILESIZE);
				}
			}

			// 왼쪽에 그려질 내용을 초기화한다. (기본적으로 잔디로 설정)
			for (int i = 0; i < TILE_X * TILE_Y; i++)
			{
				tileInfo[i].frameX = 0;
				tileInfo[i].frameY = 0;
				tileInfo[i].objframeX = 0;
				tileInfo[i].objframeY = 0;
				tileInfo[i].terrain = EMPTY;
			}
		}
	}

	for (int i = 0; i < OBJECT_TILE_Y; i++)
	{
		for (int j = 0; j < OBJECT_TILE_X; j++)
		{
			objectTileInfo[i*OBJECT_TILE_X + j].frameX = j;
			objectTileInfo[i*OBJECT_TILE_X + j].frameY = i;


			// 오른쪽에 샘플 타일의 Rect를 설정한다.
			SetRect(&objectTileInfo[i*OBJECT_TILE_X + j].rcTile, WINSIZE_TILE_MAP_X - objSampleTileImage->GetWidth() + j * TILESIZE, i*TILESIZE,
				WINSIZE_TILE_MAP_X - objSampleTileImage->GetWidth() + j * TILESIZE + TILESIZE, i*TILESIZE + TILESIZE);
		}
	}

	changescene = new ChangeScene();
	changescene->SetTilemapToolScene(this);

	savebutton = new Button();

	loadbutton = new Button();

	morebutton = new Button();

	exitbutton = new Button();

	//isObject = false;

	savebutton->Init("세이브버튼", 900, WINSIZE_TILE_MAP_Y - 100, downframepoint, upframepoint);
	loadbutton->Init("로드버튼", 1100, WINSIZE_TILE_MAP_Y - 100, downframepoint, upframepoint);
	morebutton->Init("체인지버튼", 1300, WINSIZE_TILE_MAP_Y - 100, downframepoint, upframepoint);
	exitbutton->Init("나가기버튼", 900, WINSIZE_TILE_MAP_Y - 200, downframepoint, upframepoint);

	savebutton->SetButtonFunc(changescene, &ChangeScene::Save, args);
	morebutton->SetButtonFunc(changescene, &ChangeScene::Change, args);
	loadbutton->SetButtonFunc(changescene, &ChangeScene::Load, args);
	exitbutton->SetButtonFunc(changescene, &ChangeScene::BattleButton, args1);

	return S_OK;
}

void TilemapToolScene::Release()
{
	if (savebutton)
	{
		savebutton->Release();
		SAFE_DELETE(savebutton);
	}

	if (loadbutton)
	{
		loadbutton->Release();
		SAFE_DELETE(loadbutton);
	}

	if (morebutton)
	{
		morebutton->Release();
		SAFE_DELETE(morebutton);
	}

	if (exitbutton)
	{
		exitbutton->Release();
		SAFE_DELETE(exitbutton);
	}

	if (args)
	{
		SAFE_DELETE(args);
	}

	if (args1)
	{
		SAFE_DELETE(args1);
	}

	if (changescene)
	{
		SAFE_DELETE(changescene);
	}

}

void TilemapToolScene::Update()
{
	// 마우스 왼쪽 버튼을 눌렀을 때
		// 1) 샘플타일에서 선택
		// 2) 메인타일에서 선택

	// 마우스 왼쪽 버튼을 뗐을 때
		// 1) 샘플타일에서 선택
		// 2) 메인타일에서 선택

	// 마우스가 이동될 때 (드래그)

	if (savebutton)
	{
		savebutton->Update();
	}

	if (loadbutton)
	{
		loadbutton->Update();
	}

	if (morebutton)
	{
		morebutton->Update();
	}

	if (exitbutton)
	{
		exitbutton->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{

		/*if (PtInRect(&rcSave, g_ptMouse))
		{
			Save();
			savebutton->SetState(BUTTON_STATE::DOWN);
		}*/

		/*if (PtInRect(&rcLoad, g_ptMouse))
		{
			Load();
			loadbutton->SetState(BUTTON_STATE::DOWN);
		}*/

		/*if (PtInRect(&rcChange, g_ptMouse))
		{
			Change();
			morebutton->SetState(BUTTON_STATE::DOWN);
		}*/

		if (isObject)
		{
			for (int i = 0; i < OBJECT_TILE_X * OBJECT_TILE_Y; i++)
			{
				if (PtInRect(&objectTileInfo[i].rcTile, g_ptMouse))
				{
					selectTileInfo.frameX = objectTileInfo[i].frameX;
					selectTileInfo.frameY = objectTileInfo[i].frameY;

					selectTileInfos[0].frameX = objectTileInfo[i].frameX;
					selectTileInfos[0].frameY = objectTileInfo[i].frameY;
					isDownSampleArea = true;

					break;
				}
			}
		}

		else
		{
			for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
			{
				if (PtInRect(&sampleTileInfo[i].rcTile, g_ptMouse))
				{
					selectTileInfo.frameX = sampleTileInfo[i].frameX;
					selectTileInfo.frameY = sampleTileInfo[i].frameY;

					selectTileInfos[0].frameX = sampleTileInfo[i].frameX;
					selectTileInfos[0].frameY = sampleTileInfo[i].frameY;
					isDownSampleArea = true;

					break;
				}
			}

		}
	}

	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		/*savebutton->SetState(BUTTON_STATE::UP);
		loadbutton->SetState(BUTTON_STATE::UP);
		morebutton->SetState(BUTTON_STATE::UP);*/
		int x = 0, y = 0;
		int tempj = 0, tempk = 0;

		if (isObject)
		{
			if (isDownSampleArea)
			{
				for (int i = 0; i < OBJECT_TILE_X * OBJECT_TILE_Y; i++)
				{
					if (PtInRect(&objectTileInfo[i].rcTile, g_ptMouse))
					{
						selectTileInfos[1].frameX = objectTileInfo[i].frameX;
						selectTileInfos[1].frameY = objectTileInfo[i].frameY;

						// 드래그 영역의 값을 정렬

						minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
						maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

						dragSizeX = maxX - minX;
						dragSizeY = maxY - minY;

						isDownSampleArea = false;
						break;
					}
				}
			}

			for (int i = 0; i < TILE_Y * TILE_X; i++)
			{
				if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
				{
					tempj = (i / TILE_X) + dragSizeY;
					tempk = (i % TILE_X) + dragSizeX;

					if (tempj >= TILE_Y)
						tempj = TILE_Y - 1;
					if (tempk >= TILE_X)
						tempk = TILE_X - 1;

					for (int j = (i / TILE_X); j <= tempj; j++)
					{
						for (int k = (i%TILE_X); k <= tempk; k++)
						{
							tileInfo[j*TILE_X + k].objframeX = minX + x;
							tileInfo[j*TILE_X + k].objframeY = minY + y;
							
							
							x++;
						}
						x = 0;
						y++;
					}

				}

			}
		}
		else
		{
			if (isDownSampleArea)
			{
				for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
				{
					if (PtInRect(&sampleTileInfo[i].rcTile, g_ptMouse))
					{
						selectTileInfos[1].frameX = sampleTileInfo[i].frameX;
						selectTileInfos[1].frameY = sampleTileInfo[i].frameY;

						// 드래그 영역의 값을 정렬

						minX = min(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						maxX = max(selectTileInfos[0].frameX, selectTileInfos[1].frameX);
						minY = min(selectTileInfos[0].frameY, selectTileInfos[1].frameY);
						maxY = max(selectTileInfos[0].frameY, selectTileInfos[1].frameY);

						dragSizeX = maxX - minX;
						dragSizeY = maxY - minY;

						isDownSampleArea = false;
						break;
					}
				}
			}

			for (int i = 0; i < TILE_Y * TILE_X; i++)
			{
				if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
				{
					tempj = (i / TILE_X) + dragSizeY;
					tempk = (i % TILE_X) + dragSizeX;

					if (tempj >= TILE_Y)
						tempj = TILE_Y - 1;
					if (tempk >= TILE_X)
						tempk = TILE_X - 1;

					for (int j = (i / TILE_X); j <= tempj; j++)
					{
						for (int k = (i%TILE_X); k <= tempk; k++)
						{
							tileInfo[j*TILE_X + k].frameX = minX + x;
							tileInfo[j*TILE_X + k].frameY = minY + y;

							x++;
						}
						x = 0;
						y++;
					}

				}

			}
		}
	}

	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		if (isObject)
		{
			for (int i = 0; i < TILE_Y * TILE_X; i++)
			{

				if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
				{
					tileInfo[i].objframeX = selectTileInfo.frameX;
					tileInfo[i].objframeY = selectTileInfo.frameY;
					break;
				}

			}
		}

		else
		{
			for (int i = 0; i < TILE_Y * TILE_X; i++)
			{

				if (PtInRect(&tileInfo[i].rcTile, g_ptMouse))
				{
					tileInfo[i].frameX = selectTileInfo.frameX;
					tileInfo[i].frameY = selectTileInfo.frameY;
					break;
				}

			}
		}


	}

	for (int i = 0; i < TILE_X* TILE_Y; i++)
	{
		if (tileInfo[i].frameX == 0)
		{
			tileInfo[i].terrain = EMPTY;
		}

		else if (tileInfo[i].frameX == 1)
		{
			tileInfo[i].terrain = BRICK;
		}

		else if (tileInfo[i].frameX == 2)
		{
			tileInfo[i].terrain = CONCRETE;
		}

		else if (tileInfo[i].frameX == 3)
		{
			tileInfo[i].terrain = GRASS;
		}

		else if (tileInfo[i].frameX == 4 || tileInfo[i].frameX == 5)
		{
			tileInfo[i].terrain = WATER;
		}

		else if (tileInfo[i].frameX == 6)
		{
			tileInfo[i].terrain = ICE;
		}

		if (tileInfo[i].objframeX  >= 2 && tileInfo[i].objframeX <=3)
		{
			tileInfo[i].terrain = EAGLE;
		}

		else if (tileInfo[i].objframeX >= 0 && tileInfo[i].objframeX <= 1)
		{
			tileInfo[i].objterrain = EMPTY;
		}

		else if (tileInfo[i].objframeX >= 4 && tileInfo[i].objframeX <= 5)
		{
			tileInfo[i].objterrain = USERTANK;
		}

		else if (tileInfo[i].objframeX >= 6 && tileInfo[i].objframeX <= 7)
		{
			tileInfo[i].objterrain = ENEMYTANK1;
		}

		else if (tileInfo[i].objframeX >= 8 && tileInfo[i].objframeX <= 9)
		{
			tileInfo[i].objterrain = ENEMYTANK2;
		}
		else if (tileInfo[i].objframeX >= 10 && tileInfo[i].objframeX <= 11)
		{
			tileInfo[i].objterrain = ENEMYTANK3;
		}
	}



}

void TilemapToolScene::Render(HDC hdc)
{
	PatBlt(hdc, 0, 0, WINSIZE_TILE_MAP_X, WINSIZE_TILE_MAP_Y, WHITENESS);
	blackBG->Render(hdc, 0, 0);
	// 오른쪽 타일맵 샘플
	if (isObject)
	{
		objSampleTileImage->Render(hdc, WINSIZE_TILE_MAP_X - objSampleTileImage->GetWidth() / 2, objSampleTileImage->GetHeight() / 2);

		for (int y = 0; y <= dragSizeY; y++)
		{
			for (int x = 0; x <= dragSizeX; x++)
			{
				objSampleTileImage->FrameRender(hdc, WINSIZE_TILE_MAP_X - objSampleTileImage->GetWidth() + (x * TILESIZE), objSampleTileImage->GetHeight() + 50 + (y*TILESIZE),
					minX + x, minY + y);
			}
		}
	}
	else
	{
		sampleTileImage->Render(hdc, WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth()/2 , sampleTileImage->GetHeight() / 2);

		for (int y = 0; y <= dragSizeY; y++)
		{
			for (int x = 0; x <= dragSizeX; x++)
			{
				sampleTileImage->FrameRender(hdc, WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth() + (x * TILESIZE), sampleTileImage->GetHeight() + 50 + (y*TILESIZE),
					minX + x, minY + y);
			}
		}

		/*sampleTileImage->FrameRender(hdc, WINSIZE_TILE_MAP_X - sampleTileImage->GetWidth(), sampleTileImage->GetHeight() + 50,
			selectTileInfo.frameX, selectTileInfo.frameY);*/
	}

	// 왼쪽 메인 타일
	for (int i = 0; i < TILE_X* TILE_Y; i++)
	{
		sampleTileImage->FrameRender(hdc, (tileInfo[i].rcTile.left + TILESIZE / 2), (tileInfo[i].rcTile.top + TILESIZE / 2),
			tileInfo[i].frameX, tileInfo[i].frameY);

		objSampleTileImage->FrameRender(hdc, (tileInfo[i].rcTile.left + TILESIZE / 2), (tileInfo[i].rcTile.top + TILESIZE / 2),
			tileInfo[i].objframeX, tileInfo[i].objframeY);
	}


	if (savebutton)	savebutton->Render(hdc);
	if (loadbutton)	loadbutton->Render(hdc);
	if (morebutton)	morebutton->Render(hdc);
	if (exitbutton)	exitbutton->Render(hdc);
}

void TilemapToolScene::Save()
{
	//OPENFILENAME OFN;
	//char str[300];
	//char lpstrFile[MAX_PATH] = "";
	//
	//memset(&OFN, 0, sizeof(OPENFILENAME));
	//OFN.lStructSize = sizeof(OPENFILENAME);
	//OFN.hwndOwner = g_hWnd;
	//OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	//OFN.lpstrFile = lpstrFile;
	//OFN.nMaxFile = 256;
	//OFN.lpstrInitialDir = "c:\\";
	//if (GetOpenFileName(&OFN) != 0) {
	//	/*wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
	//	MessageBox(g_hWnd, str, "파일 열기 성공", MB_OK);*/
	//}

	//DWORD writtenByte;

	//HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	//WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);
	//CloseHandle(hFile);

}

void TilemapToolScene::Load()
{

	//OPENFILENAME OFN;
	//char str[300];
	//char lpstrFile[MAX_PATH] = "";


	//memset(&OFN, 0, sizeof(OPENFILENAME));
	//OFN.lStructSize = sizeof(OPENFILENAME);
	//OFN.hwndOwner = g_hWnd;
	//OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	//OFN.lpstrFile = lpstrFile;
	//OFN.nMaxFile = 256;
	//OFN.lpstrInitialDir = "c:\\";
	//if (GetOpenFileName(&OFN) != 0) {
	//	//wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
	//	//MessageBox(g_hWnd, str, "파일 열기 성공", MB_OK);
	//}
	//
	//DWORD	readByte;
	//HANDLE	hFile;

	//hFile = CreateFile(OFN.lpstrFile, GENERIC_READ,
	//	0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
	//CloseHandle(hFile);


}

void TilemapToolScene::Change()
{
	/*dragSizeX = 0;
	dragSizeY = 0;
	selectTileInfo.frameX = 0;
	selectTileInfo.frameY = 0;
	selectTileInfos[0].frameX = 0;
	selectTileInfos[0].frameY = 0;
	selectTileInfos[1].frameX = 0;
	selectTileInfos[1].frameY = 0;
	isObject = !isObject;*/
}

bool TilemapToolScene::GetisObject()
{
	return isObject;
}

void TilemapToolScene::SetisObject(bool isobject)
{
	isObject = isobject;
}

TilemapToolScene::TilemapToolScene()
{
}

TilemapToolScene::~TilemapToolScene()
{
}
