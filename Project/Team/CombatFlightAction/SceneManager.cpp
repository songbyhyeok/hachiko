#include "SceneManager.h"
#include "Image.h"
#include "PlayerManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "UI.h"

HRESULT SceneManager::Init()
{
	SetFrame(0, 1, 1, 0, 0);

	/*ImageManager::GetSingleton()->AddImage("stage1", "Image/MAP/RUIN.bmp", WINSIZE_X, WINSIZE_Y);
	stage1 = ImageManager::GetSingleton()->FindImage("stage1");*/

	ImageManager::GetSingleton()->AddImage("stage2", "Image/MAP/end.bmp", WINSIZE_X, WINSIZE_Y);
	stage2 = ImageManager::GetSingleton()->FindImage("stage2");

	ImageManager::GetSingleton()->AddImage("stage3", "Image/MAP/TILE.bmp", WINSIZE_X, WINSIZE_Y);
	stage1 = ImageManager::GetSingleton()->FindImage("stage3");

	ImageManager::GetSingleton()->AddImage("INTRO", "Image/MAP/introMain.bmp", WINSIZE_X, WINSIZE_Y);
	bg = ImageManager::GetSingleton()->FindImage("INTRO");

	ImageManager::GetSingleton()->AddImage("BACK", "Image/MAP/SPACE.bmp", WINSIZE_X, WINSIZE_Y);
	back = ImageManager::GetSingleton()->FindImage("BACK");

	ImageManager::GetSingleton()->AddImage("END", "Image/MAP/Gameover.bmp", WINSIZE_X, WINSIZE_Y);
	isEnd = ImageManager::GetSingleton()->FindImage("END");
	
	gameScene = INTRO;

	return S_OK;
}

void SceneManager::Update()
{
	if (gameScene == INTRO)
	{
		IntroScene();
	}

	else if (isUI && gameScene == SELECT)
	{
		SelectScene();
	}
	
	else if (gameScene == SCENE1)
	{
		PlayScene();

		if (playerMgr->GetPlayerInf()->GetLife() <= 0)
		{
			gameScene = END;
		}
	}

	else if (gameScene == SCENE2)
	{
		PlayScene();

		/*if (playerMgr->GetPlayerInf()->GetLife() <= 0)
		{
			gameScene = END;
		}*/
	}

	else if (gameScene == SCENE3)
	{
		PlayScene();

		/*if (playerMgr->GetPlayerInf()->GetLife() <= 0)
		{
			gameScene = END;
		}*/
	}

	else if (gameScene == END)
	{
		EndScene();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (gameScene == INTRO)
	{
		bg->Render(hdc, 0, 0);
	}

	else if (gameScene == SELECT)
	{
		if (back)
		{
			back->Render(hdc, 0, 0);
		}

		isUI->Render(hdc);
		
	}

	else if (gameScene == SCENE1)
	{
		if (stage1)
		{
			stage1->MapRender(hdc, nY);
		}

		playerMgr->Render(hdc);
		enemyMgr->Render(hdc);
	}

	else if (gameScene == SCENE2)
	{
		if (stage2)
		{
			stage2->Render(hdc,0,0);
		}

	
	}

	/*else if (gameScene == SCENE3)
	{
		if (stage3)
		{
			stage3->MapRender(hdc, nY);
		}

		playerMgr->Render(hdc);
		enemyMgr->Render(hdc);
	}*/

	else if (gameScene == END)
	{
		isEnd->Render(hdc, 0 , 0);
	}
}

void SceneManager::IntroScene()
{
	if (KeyManager::GetSingleton()->IsOnceKeyUp('Z'))
	{
		gameScene = SELECT;
	}
}

void SceneManager::SelectScene()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
	{
		if (isUI->GetSelect() > -130)
		{
			isUI->SetSelect(-130);
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT))
	{
		if (isUI->GetSelect() < 130)
		{
			isUI->SetSelect(130);
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp('Z'))
	{
		if (isUI->GetSelect() == -130)
		{
			isUI->SetSelect(playerMgr->HYEOK);
			playerMgr->SetSelect(0);
		}

		if (isUI->GetSelect() == 0)
		{
			isUI->SetSelect(playerMgr->DONGKYUNE);
			playerMgr->SetSelect(1);
		}

		if (isUI->GetSelect() == 130)
		{
			isUI->SetSelect(playerMgr->JUNHYEOK);
			playerMgr->SetSelect(2);
		}

		gameScene = SCENE1;
		TimeManager::GetSingleton()->Init();
	}
}

void SceneManager::PlayScene()
{
	nY -= 1;
	
	if (nY + WINSIZE_Y <= 0)
		nY += WINSIZE_Y;
	
	if (bg)
	{
		SetMoveFrameY(3, 2);
	}

	playerMgr->SelectMode();

	if (gameScene == SCENE1)
		Scene1();

	else if (gameScene == SCENE2)
		Scene2();

	else if (gameScene == SCENE3)
		Scene3();
}

void SceneManager::Scene1()
{
	float elaTime = TimeManager::GetSingleton()->GetWorldTime();

	if (2.00 <= elaTime && elaTime < 3.00)
	{
		enemyMgr->AddJellyFish(3);
		enemyMgr->AddUFOEnemy(3);
		enemyMgr->AddUFO(3);
		enemyMgr->AddCuteEye(3);
		enemyMgr->AddShyEye(5);
		enemyMgr->AddBombMan(1);
		enemyMgr->AddCuteEye(1);
	}

	else if (3.50 < elaTime && elaTime < 5.00)
	{
		enemyMgr->AddBombMan(5);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
	}

	else if (5.50 < elaTime && elaTime < 7.00)
	{
		enemyMgr->AddComet(5);
		enemyMgr->AddUFO(5);
		enemyMgr->AddCuteEye(1);
	}

	else if (7.50 < elaTime && elaTime < 8.00)
	{
		enemyMgr->SetIsBool(false);
	}

	else if (9.50 < elaTime && elaTime < 11.00)
	{
		enemyMgr->AddBombMan(3);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
	}

	else if (10.50 < elaTime && elaTime < 12.00)
	{
		enemyMgr->AddComet(3);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
	}

	else if (12.50 < elaTime && elaTime < 14.00)
	{
		enemyMgr->AddCuteEye(2);
		enemyMgr->AddJellyFish(3);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
	}

	else if (14.50 < elaTime && elaTime < 16.00)
	{
		enemyMgr->AddUFO(5);
		enemyMgr->AddUFOEnemy(8);
	}

	else if (16.50 < elaTime && elaTime < 18.00)
	{
		enemyMgr->AddShyEye(5);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
		//enemyMgr->AddBoss1();
	}

	else if (18.50 < elaTime && elaTime < 19.50)
	{
		enemyMgr->AddShyEye(5);
		enemyMgr->AddJellyFish(5);
		enemyMgr->AddUFOEnemy(5);
		enemyMgr->AddShyEye(5);
		enemyMgr->AddBoss1();
	}
	enemyMgr->Update();
	playerMgr->Update();

	for (auto & it : enemyMgr->GetEnemy())
	{
		if (it->GetisDead())
			gameScene = SCENE2;
	}

}

void SceneManager::Scene2()
{




}

void SceneManager::Scene3()
{

}

void SceneManager::EndScene()
{
}

void SceneManager::SetMgr(PlayerManager * _playerMgr, EnemyManager* _enemyMgr, UI * _isUI)
{
	playerMgr = _playerMgr;
	enemyMgr = _enemyMgr;
	isUI = _isUI;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
