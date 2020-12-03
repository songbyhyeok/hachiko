#include "Collision.h"
#include "Player.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "MissileFactory.h"
#include "Missile.h"
#include "TilemapToolScene.h"

HRESULT Collision::Init()
{
	exit = false;

	playerCheck = false;
	enemyCheck = false;

	return S_OK;
}

void Collision::Update()
{
}

void Collision::PlayerUpdate()
{
	// 맵 타일의 특정 Terrain 과 플레이어가 충돌할 경우
	if (!playerCheck && tempPlayerRect)
	{
		int tempIdX = player->GetTileIdX(); int tempIdY = player->GetTileIdY();

		if (mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == BRICK ||
			mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == WALL ||
			mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == MAGMA)

			if (mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].rcTile.bottom >= tempPlayerRect->top)
				playerCheck = true;

		if (mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].sTerrain == BRICK ||
			mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].sTerrain == WALL ||
			mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].sTerrain == MAGMA)

			if (mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].rcTile.top <= tempPlayerRect->bottom)
				playerCheck = true;

		if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == BRICK ||
			mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == WALL ||
			mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == MAGMA)

			if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].rcTile.right >= tempPlayerRect->left)
				playerCheck = true;

		if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == BRICK ||
			mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == WALL ||
			mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == MAGMA)

			if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].rcTile.left <= tempPlayerRect->right)
				playerCheck = true;
	}

	// 플레이어 총알에 적이 맞을 경우
	vector<Missile*> tempMissilePVec = player->GetMissileMf()->GetMissile();
	for (int i = 0; i < tempMissilePVec.size(); i++)
	{
		for (int j = 0; j < enemyFa->GetEnemy().size(); j++)
		{
			if (tempMissilePVec[i]->GetisFire())
			{
				if (!enemyFa->GetEnemy()[j]->GetIsHit() &&
					tempMissilePVec[i]->GetPos().x > enemyFa->GetEnemy()[j]->GetRect()->left &&
					tempMissilePVec[i]->GetPos().y > enemyFa->GetEnemy()[j]->GetRect()->top &&
					tempMissilePVec[i]->GetPos().x < enemyFa->GetEnemy()[j]->GetRect()->right &&
					tempMissilePVec[i]->GetPos().y < enemyFa->GetEnemy()[j]->GetRect()->bottom)
				{
					enemyFa->GetEnemy()[j]->SetIsHit(true);
					enemyFa->GetEnemy()[j]->SetHp(-10);
					player->SetKill(1);

					enemyFa->GetEnemy()[j]->SetIsHit(false);
					tempMissilePVec[i]->SetisFire(false);
				}
			}
		}

		// 플레이어 총알에 terrain 충돌
		for (int k = 0; k < MAIN_TILE_Y * MAIN_TILE_X; k++)
		{
			if (mapTool->GetTileInf()[k].sTerrain == BRICK ||
				mapTool->GetTileInf()[k].sTerrain == WALL ||
				mapTool->GetTileInf()[k].sTerrain == MAGMA)

				if (tempMissilePVec[i]->GetisFire())
			{
				if (tempMissilePVec[i]->GetPos().x > mapTool->GetTileInf()[k].rcTile.left &&
					tempMissilePVec[i]->GetPos().y > mapTool->GetTileInf()[k].rcTile.top &&
					tempMissilePVec[i]->GetPos().x < mapTool->GetTileInf()[k].rcTile.right &&
					tempMissilePVec[i]->GetPos().y < mapTool->GetTileInf()[k].rcTile.bottom)
				{
					tempMissilePVec[i]->SetisFire(false);
				}
			}
		}
	}
}

void Collision::EnemyUpdate()
{
	for (int i = 0; i < enemyFa->GetEnemy().size(); i++)
	{
		// 맵 타일의 특정 Terrain 과 적이 충돌할 경우	
		if (!enemyCheck && tempEnemyRect)
		{
			int tempIdX = enemyFa->GetEnemy()[i]->GetTileIdX(); int tempIdY = enemyFa->GetEnemy()[i]->GetTileIdY();

			if (mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == WALL ||
				mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == BRICK ||
				mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == MAGMA)

				if(mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].rcTile.bottom >= tempEnemyRect->top)
			{
				enemyCheck = true;

			}

			if (mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].sTerrain == WALL ||
				mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == BRICK ||
				mapTool->GetTileInf()[(tempIdY - 1) * MAIN_TILE_X + tempIdX].sTerrain == MAGMA)

				if (mapTool->GetTileInf()[(tempIdY + 1) * MAIN_TILE_X + tempIdX].rcTile.top <= tempEnemyRect->bottom)
			{
				enemyCheck = true;

			}

			if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == WALL ||
				mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == BRICK ||
				mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].sTerrain == MAGMA)

				if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX - 1].rcTile.right >= tempEnemyRect->left)
			{
				enemyCheck = true;
				
			}

			if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == WALL ||
				mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == BRICK ||
				mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].sTerrain == MAGMA)

				if (mapTool->GetTileInf()[(tempIdY)* MAIN_TILE_X + tempIdX + 1].rcTile.left <= tempEnemyRect->right)
			{
				enemyCheck = true;

			}
		}

		// 적 미사일 플레이어 충돌
		vector<Missile*> tempMissileEVec = enemyFa->GetEnemy()[i]->GetMissileMf()->GetMissile();
		for (int j = 0; j < tempMissileEVec.size(); j++)
		{
			if (tempMissileEVec[j]->GetisFire())
			{
				if (!tempMissileEVec[j]->GetisHit() &&
					tempMissileEVec[j]->GetPos().x > player->GetRect()->left &&
					tempMissileEVec[j]->GetPos().y > player->GetRect()->top &&
					tempMissileEVec[j]->GetPos().x < player->GetRect()->right &&
					tempMissileEVec[j]->GetPos().y < player->GetRect()->bottom)
				{
					tempMissileEVec[j]->SetisHit(true);

					player->SetHp(-10);

					tempMissileEVec[j]->SetisHit(false);
					tempMissileEVec[j]->SetisFire(false);
				}
			}

			// 적 미사일 terrain 충돌
			for (int k = 0; k < MAIN_TILE_Y * MAIN_TILE_X; k++)
			{
				if (mapTool->GetTileInf()[k].sTerrain == WALL || 
					mapTool->GetTileInf()[k].sTerrain == BRICK ||
					mapTool->GetTileInf()[k].sTerrain == MAGMA)

					if (tempMissileEVec[j]->GetisFire())
				{
					if (tempMissileEVec[j]->GetPos().x > mapTool->GetTileInf()[k].rcTile.left - TILE_SIZE / 2 &&
						tempMissileEVec[j]->GetPos().y > mapTool->GetTileInf()[k].rcTile.top - TILE_SIZE / 2 &&
						tempMissileEVec[j]->GetPos().x < mapTool->GetTileInf()[k].rcTile.right &&
						tempMissileEVec[j]->GetPos().y < mapTool->GetTileInf()[k].rcTile.bottom)
					{
						tempMissileEVec[j]->SetisFire(false);
					}
				}
			}
		}

		// 적 범위에 플레이어가 들어올 경우 
		vector<RECT*>tempLocateVec = enemyFa->GetEnemy()[i]->GetLocateVec();
		for (int j = 0; j < tempLocateVec.size(); j++)
		{
			if (CheckRectCollision(*tempLocateVec[j], *player->GetRect()))
			{
				enemyFa->GetEnemy()[i]->SetMoving(false);
				enemyFa->GetEnemy()[i]->SetDetect(true);
				enemyFa->GetEnemy()[i]->SetDoAttack(false);
				enemyFa->GetEnemy()[i]->BringPlayerRectPos(player->GetRect());

				saveRect = *tempLocateVec[j];

				break;
			}

			else if (!CheckRectCollision(saveRect, *player->GetRect()))
			{
				enemyFa->GetEnemy()[i]->SetMoving(true);
				enemyFa->GetEnemy()[i]->SetDetect(false);
				enemyFa->GetEnemy()[i]->SetDoAttack(false);
			}
		}

		// 적 범위에 플레이어가 들어오고 공격범위에도 들어올 경우
		vector<RECT*>tempAttackVecs = enemyFa->GetEnemy()[i]->GetAttackVec();
		if (!enemyFa->GetEnemy()[i]->GetMoving() &&
			enemyFa->GetEnemy()[i]->GetDetect() &&
			!enemyFa->GetEnemy()[i]->GetDoAttack())
		{
			for (int j = 0; j < tempAttackVecs.size(); j++)
			{
				if (CheckRectCollision(*tempAttackVecs[j], *player->GetRect()))
				{
					enemyFa->GetEnemy()[i]->SetMoving(false);
					enemyFa->GetEnemy()[i]->SetDetect(false);
					enemyFa->GetEnemy()[i]->SetDoAttack(true);
					enemyFa->GetEnemy()[i]->BringPlayerRectPos(player->GetRect());
				}
			}
		}
	}
}

void Collision::SetPlayer(Player * _player)
{
	player = _player;
}

void Collision::SetEnemy1Factory(Enemy1Factory * _enemyFa)
{
	enemyFa = dynamic_cast<EnemyFactory*>(_enemyFa); // 업 캐스팅
}

void Collision::SetEnemy2Factory(Enemy2Factory * _enemyFa)
{
	enemyFa = _enemyFa;
}

void Collision::SetEnemy3Factory(Enemy3Factory * _enemyFa)
{
	enemyFa = _enemyFa;
}

void Collision::SetEnemy4Factory(Enemy4Factory * _enemyFa)
{
	enemyFa = _enemyFa;
}

void Collision::SetBossFactory(BossFactory * _enemyFa)
{
	enemyFa = _enemyFa;
}

void Collision::SetMapTool(TilemapToolScene * _mapTool)
{
	mapTool = _mapTool;
}

void Collision::SetTempPlayerPos(FPOINT * _tempPlayerPos)
{
	tempPlayerPos = _tempPlayerPos;
}

void Collision::SetTempPlayerRc(RECT * _tempPlayerRc)
{
	tempPlayerRect = _tempPlayerRc;
}

void Collision::SetTempEnemyPos(FPOINT * _tempEnemyPos)
{
	tempEnemyPos = _tempEnemyPos;
}

void Collision::SetTempEnemyRc(RECT * _tempEnemyRc)
{
	tempEnemyRect = _tempEnemyRc;
}

void Collision::SetPlayerCheck(bool _playerCheck)
{
	playerCheck = _playerCheck;
}

bool Collision::GetPlayerCheck()
{
	return playerCheck;
}

void Collision::SetEnemyCheck(bool _enemyCheck)
{
	enemyCheck = _enemyCheck;
}

bool Collision::GetEnemyCheck()
{
	return enemyCheck;
}

Collision::Collision()
{}

Collision::~Collision()
{}
