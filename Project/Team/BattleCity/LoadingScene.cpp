#include "LoadingScene.h"
#include "Image.h"
#include "Animation.h"

HRESULT LoadingScene::Init()
{
	bg = ImageManager::GetSingleton()->AddImage("LoadingScene", "Image/loadingImg.bmp",0,0, 7200, 800, 12,1);
	
	ani = new DefaultAnimation();
	ani->Init(bg->GetWidth(), bg->GetHeight(), bg->GetFrameWidth(), bg->GetFrameHeight());
	ani->SetUpdateTime(FPS/5.0f);
	ani->SetPlayFrame(true, true);
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
	bg->AnimationRender(hdc, WINSIZE_X / 2, WINSIZE_Y/2, ani);
}

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}
