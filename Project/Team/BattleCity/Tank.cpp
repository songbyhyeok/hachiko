#include "pch.h"
#include "macroFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Astar.h"
#include "BattleScene.h"
#include "Missile.h"
#include "Animation.h"

HRESULT Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = 120;

	ImageManager::GetSingleton()->AddImage("UFO", "Image/ufo.bmp", pos.x, pos.y, 530, 32, 10, 1, true, RGB(255, 0, 255));
	image = ImageManager::GetSingleton()->FindImage("UFO");

	currFrameX = currFrameY = 0;
	updateCount = 0;


	speed = 1.0f;
	angle = PI;
	size = 40;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	

	return S_OK;
}

HRESULT Tank::Init(float posX, float posY)
{	
	
	startPos.x = posX;
	startPos.y = posY;

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == USERTANK && i % 2 == 0)
		{
			startPos.x = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			startPos.y = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}
	this->GameInit(startPos.x, startPos.y);
	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	image = ImageManager::GetSingleton()->AddImage("EnemyTank1", "Image/EnemyTank1.bmp", pos.x, pos.y, 480, 120, 8, 2, true, RGB(255, 0, 255));
	effectimage = ImageManager::GetSingleton()->AddImage("TankCrasheffect", "Image/bigEffect.bmp", pos.x, pos.y, 66, 35, 2, 1, true, RGB(255, 0, 255));

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);
	ownmissile = missileMgr->GetMissileVector();


	ani = new ArrAnimation();
	ani->Init(image->GetWidth(), image->GetHeight(), image->GetFrameWidth(), image->GetFrameHeight());
	ani->SetUpdateTime(FPS / 2.0f);
	ani->SetPlayFrame(arrAni, 2, true, true);
	ani->Start();
	return S_OK;
}

void Tank::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);

	
	SAFE_DELETE(ani);


}

void Tank::Update()
{
	if (!isHit)
	{
		if (ani)
		{
			ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP) && !down && !left && !right)
		{
			arrAni[0] = TANKUP+8;
			arrAni[1] = TANKUP+9;
			ani->SetPlayFrame(arrAni, 2, true, true);
			pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.y < image->GetFrameHeight()/2)
			{
				pos.y = image->GetFrameHeight() / 2;
			}
			missileMgr->SetAngle(90);
			up = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN) && !up && !left && !right)
		{
			arrAni[0] = TANKDOWN+8;
			arrAni[1] = TANKDOWN+9;
			ani->SetPlayFrame(arrAni, 2, true, true);
			pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.y >WINSIZE_BATTLE_MAP_Y - image->GetFrameHeight() / 2)
			{
				pos.y = WINSIZE_BATTLE_MAP_Y - image->GetFrameHeight() / 2;
			}
			missileMgr->SetAngle(270);
			down = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT) && !down && !up && !right)
		{
			arrAni[0] = TANKLEFT+8;
			arrAni[1] = TANKLEFT+9;
			ani->SetPlayFrame(arrAni, 2, true, true);
			pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.x < size / 2)
			{
				pos.x = size / 2;
			}
			missileMgr->SetAngle(180);
			left = true;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT) && !down && !left && !up)
		{
			arrAni[0] = TANKRIGHT+8;
			arrAni[1] = TANKRIGHT+9;
			ani->SetPlayFrame(arrAni, 2, true, true);
			pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();
			if (pos.x > WINSIZE_BATTLE_MAP_Y - size / 2)
			{
				pos.x = WINSIZE_BATTLE_MAP_Y - size / 2;
			}
			missileMgr->SetAngle(0);
			right = true;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_UP))
		{
			up = false;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_DOWN))
		{
			down = false;
		}

		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_RIGHT))
		{
			right = false;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
		{
			left = false;
		}


		if (missileMgr)
		{
			missileMgr->Update();
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			if (missileMgr)
			{
				missileMgr->Fire();

			}
		}

		this->CheckCollision();
	}

	else
	{
		updateCount++;
		if (updateCount % 7 == 6)
		{
			updateCount = 0;
			effectFrameX++;
			if (effectFrameX > 1)
			{
				pos.x = -100;
				pos.y = -100;
				effectFrameX = 0;
				pos.x = -1000;
				pos.y = -1000;
				isHit = false;
				life -= 1;
				if (life > 0)
				{
					this->GameInit(startPos.x, startPos.y);
				}
			}
		}
	}

	
	
}

void Tank::Render(HDC hdc)
{
	
	if (isHit)
	{
		if (effectimage)
		{
			effectimage->FrameRender(hdc, pos.x, pos.y, effectFrameX, effectFrameY, 2);
		}
	}

	else
	{
		if (missileMgr)
		{
			missileMgr->Render(hdc);
		}

		if (life > 0)
		{
			if (image)
			{
				//image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
				image->AnimationRender(hdc, pos.x, pos.y, ani);
				
				
			}
		}
	}

	for (int i = 0; i < life; i++)
	{
		image->FrameRender(hdc, i * 30 + 800, 680, 0, 0, 0.5);
	}
	
			
}

void Tank::CheckCollision()
{
	vector<Missile*>::iterator it;

	for (int i = 0; i < TILE_Y*TILE_X; i++)
	{
		if (battlescene->GetTileInfo()[i].terrain != EMPTY && battlescene->GetTileInfo()[i].terrain != GRASS && battlescene->GetTileInfo()[i].terrain != ICE
			&& battlescene->GetTileInfo()[i].terrain < 7)
		{
			if (battlescene->GetTileInfo()[i].rcTile.left >= pos.x + size / 2 ||
				battlescene->GetTileInfo()[i].rcTile.right <= pos.x - size / 2 ||
				battlescene->GetTileInfo()[i].rcTile.top >= pos.y + size / 2 ||
				battlescene->GetTileInfo()[i].rcTile.bottom <= pos.y - size / 2)
			{
				continue;
			}

			else
			{

				if (battlescene->GetTileInfo()[i].rcTile.left < pos.x + size / 2
					&& right)
				{
					pos.x = battlescene->GetTileInfo()[i].rcTile.left - size / 2;
					
				}

				else if (battlescene->GetTileInfo()[i].rcTile.right > pos.x - size / 2 
					&& left)
				{
					pos.x = battlescene->GetTileInfo()[i].rcTile.right + size / 2;
				}
				else if (battlescene->GetTileInfo()[i].rcTile.top < pos.y + size / 2 
					&& down)
				{
					pos.y = battlescene->GetTileInfo()[i].rcTile.top - size / 2;
				}
				else if (battlescene->GetTileInfo()[i].rcTile.bottom > pos.y - size / 2 
					&& up)
				{
					pos.y = battlescene->GetTileInfo()[i].rcTile.bottom + size / 2;
				}


			}
		}
	}

	for (it = ownmissile.begin(); it != ownmissile.end(); it++)
	{
		
		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (battlescene->GetTileInfo()[i].terrain !=EMPTY && battlescene->GetTileInfo()[i].terrain != GRASS && battlescene->GetTileInfo()[i].terrain != WATER
				&& battlescene->GetTileInfo()[i].terrain != ICE	&& battlescene->GetTileInfo()[i].terrain < 7)
			{
				if (battlescene->GetTileInfo()[i].rcTile.left >= (*it)->GetPos().x + (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.right <= (*it)->GetPos().x - (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.top >= (*it)->GetPos().y + (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.bottom <= (*it)->GetPos().y - (*it)->GetSize() / 2)
				{
					continue;
				}

				else
				{
					if (battlescene->GetTileInfo()[i].terrain == BRICK)
					{
						battlescene->GetTileInfo()[i].terrain = EMPTY;
						battlescene->GetTileInfo()[i].frameX = 0;
						battlescene->GetTileInfo()[i].frameY = 0;
												
					}

					(*it)->SetIsCrash(true);
				}
			}

			if (battlescene->GetTileInfo()[i].terrain == EAGLE)
			{
				if (battlescene->GetTileInfo()[i].rcTile.left >= (*it)->GetPos().x + (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.right <= (*it)->GetPos().x - (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.top >= (*it)->GetPos().y + (*it)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.bottom <= (*it)->GetPos().y - (*it)->GetSize() / 2)
				{
					continue;
				}

				else
				{
					battlescene->SetGameOver(true);
				}
			}


		}
		
		
	}
	
}



HRESULT Tank::GameInit(float posX, float posY)
{
	count = 0;
	pos.x = posX;
	pos.y = posY;
	   
	currFrameX = currFrameY = 0;
	effectFrameX = effectFrameY = 0;
	updateCount = 0;

	speed = 150.0f;
	angle = PI;
	size = 55;

	up = false;
	right = false;
	left = false;
	down = false;

	HP = 1;

	arrAni[0] = TANKUP+8;

	arrAni[1] = TANKUP+9;
	return S_OK;
}

Tank::Tank()
{
}


Tank::~Tank()
{
}
