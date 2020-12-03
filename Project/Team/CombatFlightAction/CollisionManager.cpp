#include "CollisionManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Item.h"

void CollisionManager::Update()
{
	Collision();
}

void CollisionManager::Collision()
{
	for (auto& it : enemyMgr->GetEnemy())
	{
		it->SetIsTarget(playerMgr->GetPlayerInf());

		if (playerMgr->GetIsSelect())
		{
			if (TimeManager::GetSingleton()->GetWorldTime() > 2.0f)
			{
				if (CheckCollision(it->GetHitBox(), playerMgr->GetPlayerInf()->GetHitBox()))
				{
					it->SetIsCrashP(true);
					playerMgr->GetPlayerInf()->SetLift(-1);
					playerMgr->GetPlayerInf()->SetIsSuffer(true);
				}

				for (auto & itt : it->GetMissileInf()->GetMissile())
					if (CheckCollision(itt->GetHitBox(), playerMgr->GetPlayerInf()->GetHitBox()))
					{
						itt->SetIsTest(true);
						it->SetIsCrashP(true);
						playerMgr->GetPlayerInf()->SetIsSuffer(true);
						playerMgr->GetPlayerInf()->SetLift(-1);
					}
			}
		}
	}
	
	//플레이어 미사일이 적과 충돌할 때
	if (playerMgr->GetIsSelect())
	{
		//for (auto & it : playerMgr->GetMissileInf()->GetMissile())
		for (auto & it : playerMgr->GetPlayerInf()->GetMissile()->GetMissile())
		{
			for (auto& its : enemyMgr->GetEnemy())
			{
				if (TimeManager::GetSingleton()->GetWorldTime() > 1.000f)
				{
					if (CheckCollision(it->GetHitBox(), its->GetHitBox()))
					{
						its->SetIsCrashM(true);

						its->SetIsCurBool(true);

						//item->SetIsDecide(true);
						//item->SetPos(its->GetPos());
					}
				}
			}
		}
	}

}

bool CollisionManager::CheckCollision(HITBOX iTarget, HITBOX pTarget)
{
	if (iTarget.left > pTarget.right ||
		iTarget.right < pTarget.left ||
		iTarget.top > pTarget.bottom ||
		iTarget.bottom < pTarget.top)
	{
		return false;
	}
	
	return true;
}

void CollisionManager::SetMgr(PlayerManager * _playerMgr, EnemyManager* _enemyMgr)
{
	playerMgr = _playerMgr;
	enemyMgr = _enemyMgr;
	//item = _item;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
