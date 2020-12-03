#include "pch.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "Astar.h"
#include "Missile.h"
#include "BattleScene.h"
#include "Animation.h"

HRESULT Enemy::Init()
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

HRESULT Enemy::Init(float posX, float posY)
{
	

	return S_OK;
}

void Enemy::Release()
{
	missileMgr->Release();
	SAFE_DELETE(missileMgr);

	if (astar)
	{
		SAFE_DELETE(astar);
	}

}

void Enemy::Update()
{
	

}

void Enemy::Render(HDC hdc)
{
	char sZtext[256];
	if (isStart)
	{
		startimg->AnimationRender(hdc, pos.x, pos.y, ani);
	}
	else
	{
		
		if (missileMgr)
		{
			missileMgr->Render(hdc);
		}

		if (HP > 0)
		{
			if (image)
			{
				image->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY);
			}
		}

		else
		{
			if (effectimage)
			{
				effectimage->FrameRender(hdc, pos.x, pos.y, effectFrameX, effectFrameY, 2);
			}
		}
	}
	
	/*SetTextColor(hdc, RGB(255,255,255));
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			wsprintf(sZtext, "%d", map[i][j]);
			TextOut(hdc, 100 + j*30, 100 + i*30, sZtext, strlen(sZtext));
		}
	}*/

	//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
}

void Enemy::AstarInit(int startx, int starty, int endx, int endy)
{
	int startIndexX, startIndexY;
	int endIndexX, endIndexY;

	if (astar)
	{
		delete astar;
	}
		
	startIndexX = (startx - 30) / 60;
	startIndexY = (starty - 30) / 60;
	endIndexX = (endx - 30) / 60;
	endIndexY = (endy - 30) / 60;

	index1 = (pos.x - 30) / 60;
	index2 = (pos.y - 30) / 60;

	Astar::Coordinate A(startIndexY, startIndexX);
	Astar::Coordinate B(endIndexY, endIndexX);

	astar = new Astar(A, B);

	map = astar->PrintNavi();
}



void Enemy::Collision()
{
	vector<Missile*>playermissile;
	int right = pos.x + size / 2;
	int left = pos.x - size / 2;
	int up = pos.y - size / 2;
	int down = pos.y + size / 2;

	vector<Missile*>::iterator it;
	vector<Missile*>::iterator ownit;
	playermissile = tank->GetMissile();

	if (HP > 0)
	{
		for (it = playermissile.begin(); it != playermissile.end(); it++)
		{
			if (!(*it)->GetIsCrash())
			{
				if (left >= ((*it)->GetPos().x + (*it)->GetSize() / 2) ||
					right <= ((*it)->GetPos().x - (*it)->GetSize() / 2) ||
					up >= ((*it)->GetPos().y + (*it)->GetSize() / 2) ||
					down <= ((*it)->GetPos().y - (*it)->GetSize() / 2))
				{
					continue;
				}

				else
				{
					(*it)->SetIsCrash(true);
					HP -= 1;
					if (HP <= 0)
					{
						battlescene->Setenemynum(battlescene->GetEnemyNum() - 1);
					}
					break;
				}
			}
		}
	
		
	
		
	
	
	}

	for (it = playermissile.begin(); it != playermissile.end(); it++)
	{
		for (ownit = ownmissile.begin(); ownit != ownmissile.end(); ownit++)
		{
			if ((*ownit)->GetIsFire() && (*it)->GetIsFire())
			{
				if (((*ownit)->GetPos().x - (*ownit)->GetSize() / 2) >= ((*it)->GetPos().x + (*it)->GetSize() / 2) ||
					((*ownit)->GetPos().x + (*ownit)->GetSize() / 2) <= ((*it)->GetPos().x - (*it)->GetSize() / 2) ||
					((*ownit)->GetPos().y - (*ownit)->GetSize() / 2) >= ((*it)->GetPos().y + (*it)->GetSize() / 2) ||
					((*ownit)->GetPos().y + (*ownit)->GetSize() / 2) <= ((*it)->GetPos().y - (*it)->GetSize() / 2))
				{
					continue;
				}

				else
				{
					(*ownit)->SetIsMissileCrash(true);
					(*it)->SetIsMissileCrash(true);

					break;
				}
			}

		}
	}

	for (ownit = ownmissile.begin(); ownit != ownmissile.end(); ownit++)
	{
		if (!(*ownit)->GetIsCrash())
		{


			if (tank->GetPos().x - tank->GetSize() / 2 >= ((*ownit)->GetPos().x + (*ownit)->GetSize() / 2) ||
				tank->GetPos().x + tank->GetSize() / 2 <= ((*ownit)->GetPos().x - (*ownit)->GetSize() / 2) ||
				tank->GetPos().y - tank->GetSize() / 2 >= ((*ownit)->GetPos().y + (*ownit)->GetSize() / 2) ||
				tank->GetPos().y + tank->GetSize() / 2 <= ((*ownit)->GetPos().y - (*ownit)->GetSize() / 2))
			{
				continue;
			}

			else
			{
				tank->SetIsHit(true);
				(*ownit)->SetIsCrash(true);
				ownit = ownmissile.begin();
				break;
			}
		}
	}

	for (ownit = ownmissile.begin(); ownit != ownmissile.end(); ownit++)
	{
		
		for (int i = 0; i < TILE_X*TILE_Y; i++)
		{
			if (battlescene->GetTileInfo()[i].terrain != EMPTY && battlescene->GetTileInfo()[i].terrain != GRASS && battlescene->GetTileInfo()[i].terrain != WATER
				&& battlescene->GetTileInfo()[i].terrain != ICE	&& battlescene->GetTileInfo()[i].terrain < 7)
			{
				if (battlescene->GetTileInfo()[i].rcTile.left >= (*ownit)->GetPos().x + (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.right <= (*ownit)->GetPos().x - (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.top >= (*ownit)->GetPos().y + (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.bottom <= (*ownit)->GetPos().y - (*ownit)->GetSize() / 2)
				{

				}

				else
				{
					if (battlescene->GetTileInfo()[i].terrain == BRICK)
					{
						battlescene->GetTileInfo()[i].terrain = EMPTY;
						battlescene->GetTileInfo()[i].frameX = 0;
						battlescene->GetTileInfo()[i].frameY = 0;

					}

					(*ownit)->SetIsCrash(true);
				}
			}

			if (battlescene->GetTileInfo()[i].terrain == EAGLE)
			{
				if (battlescene->GetTileInfo()[i].rcTile.left >= (*ownit)->GetPos().x + (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.right <= (*ownit)->GetPos().x - (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.top >= (*ownit)->GetPos().y + (*ownit)->GetSize() / 2 ||
					battlescene->GetTileInfo()[i].rcTile.bottom <= (*ownit)->GetPos().y - (*ownit)->GetSize() / 2)
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

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

HRESULT DefaultEnemy::Init(float posX, float posY)
{
	count = 0;
	pos.x = posX;
	pos.y = posY;
	startPos.x = posX;
	startPos.y = posY;
	endPos.x = 690;//690;
	endPos.y = 750;//750;

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == USERTANK && i % 2 == 0)
		{
			endPos.x = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			endPos.y = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}

	

	index1 = (pos.x - 30) / 60;
	index2 = (pos.y - 30) / 60;

	AstarInit(posX, posY, endPos.x, endPos.y);

	firetime = 0;

	image = ImageManager::GetSingleton()->AddImage("EnemyTank2", "Image/EnemyTank2.bmp", pos.x, pos.y, 480, 60, 8, 1, true, RGB(255, 0, 255));
	effectimage = ImageManager::GetSingleton()->AddImage("TankCrasheffect", "Image/bigEffect.bmp", pos.x, pos.y, 66, 35, 2, 1, true, RGB(255, 0, 255));
	startimg = ImageManager::GetSingleton()->AddImage("Enemystart", "Image/spawn.bmp", pos.x, pos.y, 160, 40, 4, 1, true, RGB(255, 0, 255));

	currFrameX = currFrameY = 0;
	effectFrameX = effectFrameY = 0;
	updateCount = 0;

	speed = 40.0f;
	angle = PI;
	size = 60;
	HP = 1;
	isDead = false;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	ownmissile = missileMgr->GetMissileVector();

	int arrAni[] = { 1,2,3,2,1,0 };
	ani = new ArrAnimation();
	ani->Init(startimg->GetWidth(), startimg->GetHeight(), startimg->GetFrameWidth(), startimg->GetFrameHeight());
	ani->SetUpdateTime(FPS / 5.0f);
	ani->SetPlayFrame(arrAni, 6, true, true);
	ani->Start();

	isStart = true;

	return S_OK;
}

void DefaultEnemy::Update()
{
	if (HP > 0 && !isStart)
	{
		//╩С

		if (index2 > 0)
		{
			if (map[index2 - 1][index1] == 7)
			{
				missileMgr->SetAngle(90);
				if (count == 0)
				{
					currFrameX = 0;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 1)
					{
						currFrameX = 0;
					}
					updateCount = 0;
				}

				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.y < (index2 - 1) * 60 + 30)
				{
					pos.y = (index2 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 - 1) * 60 + 30)
				{
					index2 = index2 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		if (index2 < 12)
		{

			if (map[index2 + 1][index1] == 7)
			{
				missileMgr->SetAngle(270);
				if (count == 0)
				{
					currFrameX = 4;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 5)
					{
						currFrameX = 4;
					}
					updateCount = 0;

				}
				pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.y > (index2 + 1) * 60 + 30)
				{
					pos.y = (index2 + 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 + 1) * 60 + 30)
				{
					index2 = index2 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		//го


		//аб
		if (index1 > 0)
		{

			if (map[index2][index1 - 1] == 7)
			{
				missileMgr->SetAngle(180);
				if (count == 0)
				{
					currFrameX = 2;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 3)
					{
						currFrameX = 2;
					}
					updateCount = 0;

				}

				pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.x < (index1 - 1) * 60 + 30)
				{
					pos.x = (index1 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.x == (index1 - 1) * 60 + 30)
				{
					index1 = index1 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}

		//©Л
		if (index1 < 12)
		{
			if (map[index2][index1 + 1] == 7)
			{
				missileMgr->SetAngle(0);
				if (count == 0)
				{
					currFrameX = 6;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 7)
					{
						currFrameX = 6;
					}
					updateCount = 0;

				}

				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.x > (index1 + 1) * 60 + 30)
				{
					pos.x = (index1 + 1) * 60 + 30;
				}
				map[index2][index1] = 0;

				if (pos.x == (index1 + 1) * 60 + 30)
				{
					index1 = index1 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}


		
	}

	if(!isStart)
		Collision();

	if (!isStart)
	{
		firetime += TimeManager::GetSingleton()->GetDeltaTime();

		if (missileMgr)
		{
			missileMgr->Update();
			if (firetime >= 1.5)
			{
				//TimeManager::GetSingleton()->SetIsTestStart(true);
				missileMgr->Fire();

				firetime = 0;
			}
		}
	}

	if (ani)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}
	if (isStart)
	{
		if (ani->GetFramePos().x == 0)
		{
			isStart = false;
		}
	}


	if (HP <= 0 && !isDead)
	{
		isDead = true;
		updateCount = 0;

	}

	if (isDead)
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
				isDead = false;

			}
		}
	}

	if (pos.x == endPos.x && pos.y == endPos.y)
	{
		int tempX, tempY;

		tempX = startPos.x;
		tempY = startPos.y;

		startPos.x = endPos.x;
		startPos.y = endPos.y;
		endPos.x = tempX;
		endPos.y = tempY;

		AstarInit(startPos.x, startPos.y, endPos.x, endPos.y);
	}

}

DefaultEnemy::DefaultEnemy()
{
}

DefaultEnemy::~DefaultEnemy()
{
}

HRESULT SpeedEnemy::Init(float posX, float posY)
{
	count = 0;
	pos.x = posX;
	pos.y = posY;
	startPos.x = posX;
	startPos.y = posY;
	endPos.x = 690;//690;
	endPos.y = 750;//750;

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == USERTANK && i % 2 == 0)
		{
			endPos.x = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			endPos.y = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}

	index1 = (pos.x - 30) / 60;
	index2 = (pos.y - 30) / 60;

	AstarInit(posX, posY, endPos.x, endPos.y);

	firetime = 0;

	image = ImageManager::GetSingleton()->AddImage("EnemyTank3", "Image/EnemyTank3.bmp", pos.x, pos.y, 480, 120, 8, 2, true, RGB(255, 0, 255));
	effectimage = ImageManager::GetSingleton()->AddImage("TankCrasheffect", "Image/bigEffect.bmp", pos.x, pos.y, 66, 35, 2, 1, true, RGB(255, 0, 255));
	startimg = ImageManager::GetSingleton()->AddImage("Enemystart", "Image/spawn.bmp", pos.x, pos.y, 160, 40, 4, 1, true, RGB(255, 0, 255));

	currFrameX = currFrameY = 0;
	effectFrameX = effectFrameY = 0;
	updateCount = 0;

	speed = 80.0f;
	angle = PI;
	size = 60;
	HP = 1;
	isDead = false;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	ownmissile = missileMgr->GetMissileVector();

	int arrAni[] = { 1,2,3,2,1,0 };
	ani = new ArrAnimation();
	ani->Init(startimg->GetWidth(), startimg->GetHeight(), startimg->GetFrameWidth(), startimg->GetFrameHeight());
	ani->SetUpdateTime(FPS / 5.0f);
	ani->SetPlayFrame(arrAni, 6, true, true);
	ani->Start();

	isStart = true;

	return S_OK;
}

void SpeedEnemy::Update()
{
	if (HP > 0 && !isStart)
	{
		//╩С

		if (index2 > 0)
		{
			if (map[index2 - 1][index1] == 7)
			{
				missileMgr->SetAngle(90);
				if (count == 0)
				{
					currFrameX = 0;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 1)
					{
						currFrameX = 0;
					}
					updateCount = 0;
				}

				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.y < (index2 - 1) * 60 + 30)
				{
					pos.y = (index2 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 - 1) * 60 + 30)
				{
					index2 = index2 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		if (index2 < 12)
		{

			if (map[index2 + 1][index1] == 7)
			{
				missileMgr->SetAngle(270);
				if (count == 0)
				{
					currFrameX = 4;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 5)
					{
						currFrameX = 4;
					}
					updateCount = 0;

				}
				pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.y > (index2 + 1) * 60 + 30)
				{
					pos.y = (index2 + 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 + 1) * 60 + 30)
				{
					index2 = index2 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		//го


		//аб
		if (index1 > 0)
		{

			if (map[index2][index1 - 1] == 7)
			{
				missileMgr->SetAngle(180);
				if (count == 0)
				{
					currFrameX = 2;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 3)
					{
						currFrameX = 2;
					}
					updateCount = 0;

				}

				pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.x < (index1 - 1) * 60 + 30)
				{
					pos.x = (index1 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.x == (index1 - 1) * 60 + 30)
				{
					index1 = index1 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}

		//©Л
		if (index1 < 12)
		{
			if (map[index2][index1 + 1] == 7)
			{
				missileMgr->SetAngle(0);
				if (count == 0)
				{
					currFrameX = 6;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 7)
					{
						currFrameX = 6;
					}
					updateCount = 0;

				}

				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.x > (index1 + 1) * 60 + 30)
				{
					pos.x = (index1 + 1) * 60 + 30;
				}
				map[index2][index1] = 0;

				if (pos.x == (index1 + 1) * 60 + 30)
				{
					index1 = index1 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}


		
	}

	if (!isStart)
		Collision();

	if (!isStart)
	{
		firetime += TimeManager::GetSingleton()->GetDeltaTime();

		if (missileMgr)
		{
			missileMgr->Update();
			if (firetime >= 0.8)
			{
				//TimeManager::GetSingleton()->SetIsTestStart(true);
				missileMgr->Fire();

				firetime = 0;
			}
		}
	}

	if (ani)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}
	if (isStart)
	{
		if (ani->GetFramePos().x == 0)
		{
			isStart = false;
		}
	}


	if (HP <= 0 && !isDead)
	{
		isDead = true;
		updateCount = 0;

	}

	if (isDead)
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
				isDead = false;

			}
		}
	}

	if (pos.x == endPos.x && pos.y == endPos.y)
	{
		int tempX, tempY;

		tempX = startPos.x;
		tempY = startPos.y;

		startPos.x = endPos.x;
		startPos.y = endPos.y;
		endPos.x = tempX;
		endPos.y = tempY;

		AstarInit(startPos.x, startPos.y, endPos.x, endPos.y);
	}
}

SpeedEnemy::SpeedEnemy()
{
}

SpeedEnemy::~SpeedEnemy()
{
}

HRESULT PowerEnemy::Init(float posX, float posY)
{
	count = 0;
	pos.x = posX;
	pos.y = posY;
	startPos.x = posX;
	startPos.y = posY;
	endPos.x = 690;//690;
	endPos.y = 750;//750;

	for (int i = 0; i < TILE_X*TILE_Y; i++)
	{
		if (battlescene->GetTileInfo()[i].objterrain == USERTANK && i % 2 == 0)
		{
			endPos.x = i % TILE_X / 2 * TILESIZE * 2 + TILESIZE;
			endPos.y = i / (TILE_X * 2) * TILESIZE * 2 + TILESIZE;
			break;
		}

	}

	index1 = (pos.x - 30) / 60;
	index2 = (pos.y - 30) / 60;

	AstarInit(posX, posY, endPos.x, endPos.y);

	firetime = 0;

	image = ImageManager::GetSingleton()->AddImage("EnemyTank4", "Image/EnemyTank4.bmp", pos.x, pos.y, 480, 240, 8, 4, true, RGB(255, 0, 255));
	effectimage = ImageManager::GetSingleton()->AddImage("TankCrasheffect", "Image/bigEffect.bmp", pos.x, pos.y, 66, 35, 2, 1, true, RGB(255, 0, 255));
	startimg = ImageManager::GetSingleton()->AddImage("Enemystart", "Image/spawn.bmp", pos.x, pos.y, 160, 40, 4, 1, true, RGB(255, 0, 255));

	currFrameX = currFrameY = 0;
	effectFrameX = effectFrameY = 0;
	updateCount = 0;

	speed = 40.0f;
	angle = PI;
	size = 60;
	HP = 3;
	isDead = false;

	fireDelay = rand() % 200 + 300;
	fireCount = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetOwner(this);

	ownmissile = missileMgr->GetMissileVector();

	int arrAni[] = { 1,2,3,2,1,0 };
	ani = new ArrAnimation();
	ani->Init(startimg->GetWidth(), startimg->GetHeight(), startimg->GetFrameWidth(), startimg->GetFrameHeight());
	ani->SetUpdateTime(FPS / 5.0f);
	ani->SetPlayFrame(arrAni, 6, true, true);
	ani->Start();

	isStart = true;

	return S_OK;
}

void PowerEnemy::Update()
{
	if (HP == 3)
	{
		currFrameY = 3;
	}
	else if (HP == 2)
	{
		currFrameY = 2;

	}
	else if (HP == 1)
	{
		currFrameY = 0;
	}
	if (HP > 0 && !isStart)
	{
		//╩С

		if (index2 > 0)
		{
			if (map[index2 - 1][index1] == 7)
			{
				missileMgr->SetAngle(90);
				if (count == 0)
				{
					currFrameX = 0;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 1)
					{
						currFrameX = 0;
					}
					updateCount = 0;
				}

				pos.y -= speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.y < (index2 - 1) * 60 + 30)
				{
					pos.y = (index2 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 - 1) * 60 + 30)
				{
					index2 = index2 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		if (index2 < 12)
		{

			if (map[index2 + 1][index1] == 7)
			{
				missileMgr->SetAngle(270);
				if (count == 0)
				{
					currFrameX = 4;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 5)
					{
						currFrameX = 4;
					}
					updateCount = 0;

				}
				pos.y += speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.y > (index2 + 1) * 60 + 30)
				{
					pos.y = (index2 + 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.y == (index2 + 1) * 60 + 30)
				{
					index2 = index2 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}
		//го


		//аб
		if (index1 > 0)
		{

			if (map[index2][index1 - 1] == 7)
			{
				missileMgr->SetAngle(180);
				if (count == 0)
				{
					currFrameX = 2;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 3)
					{
						currFrameX = 2;
					}
					updateCount = 0;

				}

				pos.x -= speed * TimeManager::GetSingleton()->GetDeltaTime();
				if (pos.x < (index1 - 1) * 60 + 30)
				{
					pos.x = (index1 - 1) * 60 + 30;
				}

				map[index2][index1] = 0;

				if (pos.x == (index1 - 1) * 60 + 30)
				{
					index1 = index1 - 1;
					count = 0;
					updateCount = 0;
				}
			}
		}

		//©Л
		if (index1 < 12)
		{
			if (map[index2][index1 + 1] == 7)
			{
				missileMgr->SetAngle(0);
				if (count == 0)
				{
					currFrameX = 6;
					count++;
				}
				updateCount++;
				if (updateCount % 5 == 0)
				{
					currFrameX++;
					if (currFrameX > 7)
					{
						currFrameX = 6;
					}
					updateCount = 0;

				}

				pos.x += speed * TimeManager::GetSingleton()->GetDeltaTime();

				if (pos.x > (index1 + 1) * 60 + 30)
				{
					pos.x = (index1 + 1) * 60 + 30;
				}
				map[index2][index1] = 0;

				if (pos.x == (index1 + 1) * 60 + 30)
				{
					index1 = index1 + 1;
					count = 0;
					updateCount = 0;
				}
			}
		}


		
	}

	if (!isStart)
		Collision();

	if (!isStart)
	{
		firetime += TimeManager::GetSingleton()->GetDeltaTime();

		if (missileMgr)
		{
			missileMgr->Update();
			if (firetime >= 0.8)
			{
				//TimeManager::GetSingleton()->SetIsTestStart(true);
				missileMgr->Fire();

				firetime = 0;
			}
		}
	}

	if (ani)
	{
		ani->UpdateKeyFrame(TimeManager::GetSingleton()->GetDeltaTime());
	}
	if (isStart)
	{
		if (ani->GetFramePos().x == 0)
		{
			isStart = false;
		}
	}


	if (HP <= 0 && !isDead)
	{
		isDead = true;
		updateCount = 0;

	}

	if (isDead)
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
				isDead = false;

			}
		}
	}

	if (pos.x == endPos.x && pos.y == endPos.y)
	{
		int tempX, tempY;

		tempX = startPos.x;
		tempY = startPos.y;

		startPos.x = endPos.x;
		startPos.y = endPos.y;
		endPos.x = tempX;
		endPos.y = tempY;

		AstarInit(startPos.x, startPos.y, endPos.x, endPos.y);
	}
}

PowerEnemy::PowerEnemy()
{
}

PowerEnemy::~PowerEnemy()
{
}
