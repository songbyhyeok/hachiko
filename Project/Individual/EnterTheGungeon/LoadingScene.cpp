#include "LoadingScene.h"
#include "Image.h"
#include "Animation.h"

HRESULT LoadingScene::Init()
{
	bg = ImageManager::GetSingleton()->AddImage("·Îµù", "Image/loading.bmp", 0, 0, 7200, 800, 12, 1);

	ani = new ArrAnimation();
	ani->Init(bg->GetWidth(), bg->GetHeight(), bg->GetFrameWidth(), bg->GetFrameHeight());
	ani->SetUpdateTime(FPS / 5.0f);
	int arr[12] = { 0,1,2,3,4,5,6,7,8,9,10,11};
	ani->SetPlayFrame(arr, 12);
	ani->Start();

	return S_OK;
}

void LoadingScene::Release()
{
	SAFE_DELETE(ani);
}

void LoadingScene::Update()
{
	ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
}

void LoadingScene::Render(HDC hdc)
{
	bg->AnimationRender(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, ani, true);
}

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}
