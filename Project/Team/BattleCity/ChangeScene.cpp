#include "ChangeScene.h"
#include "TilemapToolScene.h"
#include "BattleScene.h"

void ChangeScene::BattleButton(const char * sceneName, const char * lodingName)
{
	{
		SceneManager::GetSingleton()->ChangeScene(sceneName, lodingName);
	}
}

void ChangeScene::QuitButton(const char * sceneName, const char * lodingName)
{
	if (MessageBox(g_hWnd, "게임을 계속 하겠습니까", "질문", MB_YESNO) == IDYES)
	{
		// 게임 계속 처리
	}
	else
	{
		PostQuitMessage(0);
	}
}

void ChangeScene::Save(const char * sceneName, const char * lodingName)
{
	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH] = "";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";
	if (GetSaveFileName(&OFN) != 0) {
		DWORD writtenByte;

		HANDLE hFile;
		hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, tilemaptoolscene->GetTile_Info(), sizeof(TILE_INFO) * TILE_X * TILE_Y, &writtenByte, NULL);
		CloseHandle(hFile);
	}
}

	

void ChangeScene::Load(const char * sceneName, const char * lodingName)
{
	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH] = "";


	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";
	if (GetOpenFileName(&OFN) != 0) {
		DWORD	readByte;
		HANDLE	hFile;
		hFile = CreateFile(OFN.lpstrFile, GENERIC_READ,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
		ReadFile(hFile, tilemaptoolscene->GetTile_Info(), sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}	
}


void ChangeScene::BattleLoad(const char * sceneName, const char * lodingName)
{
	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH] = "";
	
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = g_hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";
	if (GetOpenFileName(&OFN) != 0) {
		DWORD	readByte;
		HANDLE	hFile;

		hFile = CreateFile(OFN.lpstrFile, GENERIC_READ,
			0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(hFile, battlescene->GetTileInfo(), sizeof(TILE_INFO) * TILE_X * TILE_Y, &readByte, NULL);
		CloseHandle(hFile);
	}

	

	battlescene->GameInit();
}

void ChangeScene::Change(const char * sceneName, const char * lodingName)
{
	tilemaptoolscene->SetisObject(!tilemaptoolscene->GetisObject());
}
