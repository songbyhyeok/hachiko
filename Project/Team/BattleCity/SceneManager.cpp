#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

DWORD CALLBACK LoadingThread(LPVOID pvParam)
{
	// 쓰레드 종료 시점 (방법)
	/*
		1. 호출된 함수가 반환될 때(우리가 사용할 방법)
		2. 호출된 함수 내부에서 ExitThread()를 호출했을 때
		3. 동일한 프로세스나 다른 프로세스에서 TerminatedThread()를 호출했을 때
		4. 현재 쓰레드가 포함된 프로세스가 종료될 때
	*/

	SceneManager::readyScene->Init();
	SceneManager::currentScene = SceneManager::readyScene;

	SceneManager::loadingScene->Release();
	SceneManager::loadingScene = nullptr;
	SceneManager::readyScene = nullptr;

	
	
	return 0;
}


HRESULT SceneManager::Init()
{
	
	return S_OK;
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}

GameNode * SceneManager::AddScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

GameNode * SceneManager::AddLoadingScene(string key, GameNode * scene)
{
	if (scene == nullptr)
		return nullptr;

	mapLoadingSceneDatas.insert(pair<string, GameNode*>(key, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*> ::iterator it;
	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK;

	if (SUCCEEDED(it->second->Init()))
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		currentScene = it->second;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT SceneManager::ChangeScene(string sceneName, string loadingSceneName)
{
	map<string, GameNode*> ::iterator it;
	it = mapSceneDatas.find(sceneName);

	if (it == mapSceneDatas.end())
	{
		return E_FAIL;
	}

	if (it->second == currentScene) return S_OK;

	// change 중간에 들어갈 로딩씬
	map<string, GameNode*> ::iterator itLoading;
	itLoading = mapLoadingSceneDatas.find(loadingSceneName);

	if (itLoading == mapLoadingSceneDatas.end())
	{
		return ChangeScene(sceneName);
	}

	if (SUCCEEDED(itLoading->second->Init()))
	{
		if (currentScene)
		{
			currentScene->Release();
		}

		readyScene = it->second;
		loadingScene = itLoading->second;
		currentScene = loadingScene;

		// 멀티쓰레드로 체인지할 메인씬을 초기화한다.
		HANDLE hThread;
		DWORD loadThreadID;
		//hThread = CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThreadID);
		//CloseHandle(hThread);
		CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &loadThreadID));
		return S_OK;
	}
	return E_FAIL;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
