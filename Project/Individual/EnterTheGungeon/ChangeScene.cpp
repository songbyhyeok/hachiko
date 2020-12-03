#include "ChangeScene.h"
#include "TilemapToolScene.h"
#include "BattleScene.h"

void ChangeScene::Save()
{
	OPENFILENAME ofn;
	char lpstrFile[MAX_PATH] = "";

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	ofn.lpstrFile = lpstrFile;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = "c:\\";
	
	if (GetSaveFileName(&ofn) != 0)
	{
		DWORD writtenByte;

		HANDLE hFile;
		hFile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, mapTool->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);
	}
}

void ChangeScene::Load()
{
	OPENFILENAME ofn;
	char lpstrFile[MAX_PATH] = "";

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	ofn.lpstrFile = lpstrFile;
	ofn.nMaxFile = 256;
	ofn.lpstrInitialDir = "c:\\";

	if (GetOpenFileName(&ofn) != 0)
	{
		DWORD readByte;
		HANDLE hFile;
		hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

		ReadFile(hFile, mapTool->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}

	//GENERIC_READ|GENERIC_WRITE
}

void ChangeScene::stage1()
{
	OPENFILENAME ofn;

	DWORD readByte;
	HANDLE hFile = CreateFile(".\\mapSave\\stage1", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	ReadFile(hFile, battleScene->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void ChangeScene::stage2()
{
	OPENFILENAME ofn;

	DWORD readByte;
	HANDLE hFile = CreateFile(".\\mapSave\\stage2", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	ReadFile(hFile, battleScene->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void ChangeScene::tunnel()
{
	OPENFILENAME ofn;

	DWORD readByte;
	HANDLE hFile = CreateFile(".\\mapSave\\tunnel", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	ReadFile(hFile, battleScene->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void ChangeScene::boss()
{
	OPENFILENAME ofn;

	DWORD readByte;
	HANDLE hFile = CreateFile(".\\mapSave\\boss", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	ReadFile(hFile, battleScene->GetTileInf(), sizeof(TILE_INF) * MAIN_TILE_X * MAIN_TILE_Y, &readByte, NULL);
	CloseHandle(hFile);
}

void ChangeScene::ChangeButton(const char * sceneName, const char * lodingName)
{
	SceneManager::GetSingleton()->ChangeScene(sceneName, lodingName);
}

void ChangeScene::Quit(const char * sceneName, const char * lodingName)
{
	SceneManager::GetSingleton()->ChangeScene(sceneName, lodingName);
}

void ChangeScene::QuitButton(const char * sceneName, const char * lodingName)
{
	if (MessageBox(g_hWnd, "게임을 계속 하겠습니까", "질문", MB_YESNO) == IDYES)
	{
	}
	else
		PostQuitMessage(0);
}

void ChangeScene::SetMapTool(TilemapToolScene * _mapTool)
{
	mapTool = _mapTool;
}

void ChangeScene::SetBattleScene(BattleScene * _battleScene)
{
	battleScene = _battleScene;
}
