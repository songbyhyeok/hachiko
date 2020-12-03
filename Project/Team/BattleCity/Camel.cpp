#include "Camel.h"
#include "Animation.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Camel::Init()
{
	Enemy::Init();

	image = ImageManager::GetSingleton()->AddImage("Camel", "Image/camel.bmp", pos.x, pos.y, 300, 267, 4, 3, true, RGB(255, 0, 255));
	
	// 0 ~ 마지막 프레임까지 순차적으로 진행
	ani = new DefaultAnimation();
	ani->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	ani->SetUpdateTime(FPS/2.0f);
	ani->SetPlayFrame(true,true);

	// 시작 프레임과 끝 프레임을 임의로 지정
	ani2 = new FrameAnimation();
	ani2->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	ani2->SetUpdateTime(FPS/10.0f);
	ani2->SetPlayFrame(8, 3, true, true);

	// 배열 형태로 순차적인 진행이 아니게 설정
	int arrAni[] = { 0,0,0,0,0,3,3,3,3,3,5,5,5,5,9,9,9,9 };

	ani3 = new ArrAnimation();
	ani3->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	ani3->SetUpdateTime(FPS/2.0f);
	ani3->SetPlayFrame(arrAni, 18, true, true);

	playAni = ani2;
	return S_OK;
}

void Camel::Release()
{
	SAFE_DELETE(ani);
	SAFE_DELETE(ani2);
	SAFE_DELETE(ani3);

	Enemy::Release();
}

void Camel::Update()
{
	if (missileMgr)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			TimeManager::GetSingleton()->SetIsTestStart(true);
			missileMgr->Fire();
		}

		missileMgr->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))
	{
		if (playAni)
		{
			playAni->Start();
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		if (playAni)
		{
			playAni->Stop();
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
	{
		if (playAni)
		{
			playAni->Pause();
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	{
		if (playAni)
		{
			playAni->Resume();
		}
	}


	if (playAni)
	{
		playAni->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}
}

void Camel::Render(HDC hdc)
{
	if (missileMgr)
	{
		missileMgr->Render(hdc);
	}

	if (image)
	{
		image->AnimationRender(hdc, WINSIZE_X/2, 300, playAni);
	}
}

Camel::Camel()
{
}

Camel::~Camel()
{
}
