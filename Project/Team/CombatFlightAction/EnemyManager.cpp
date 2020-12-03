#include "EnemyManager.h"
#include "Enemy.h"

#define ENEMY_NUM 100

HRESULT EnemyManager::Init()
{
	adjustW = 0;	adjustH = 0;

	isBombMan = false;
	isComet = false;
	isCuteEye = false;
	isShyEye = false;
	isJellyFish = false;
	isUFO = false;
	isUFOEnemy = false;
	isBoss1 = false;
	isSwitch = false;

	return S_OK;
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Release();
		SAFE_DELETE((*itEnemys));
	}
	vecEnemys.clear();
}

void EnemyManager::Update()
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		//if (!(*itEnemys)->GetIsCrashP() || !(*itEnemys)->GetIsCrashM())
		(*itEnemys)->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin(); itEnemys != vecEnemys.end(); itEnemys++)
	{
		//if (!(*itEnemys)->GetIsCrashP() || !(*itEnemys)->GetIsCrashM())
		(*itEnemys)->Render(hdc);
	}
}

void EnemyManager::AddBombMan(int num)
{
	if (!isBombMan)
	{
		for (int i = 0; i < num; i++)
		{
			BombMan * bombMan = new BombMan();
			bombMan->Init(WINSIZE_X / 2 - 200 + (i % num) * 100, 0);

			vecEnemys.push_back(bombMan);
		}

		isBombMan = true;
	}
}

void EnemyManager::AddComet(int num)
{
	if (!isComet)
	{
		srand((unsigned)time(NULL));

		for (int i = 0; i < num; i++)
		{
			bool isBool = false;

			int location = rand() % 3;

			int tempW = rand() % 600;
			int tempH = rand() % 200;

			if (location == 0)
			{
				adjustW = 0;

				while (!isBool)
				{
					if ((tempH - 50) < adjustH && adjustH < (tempH))
					{
						for (int j = 0; j < 10; j++)
							tempH = rand() % 200;
					}

					else
						isBool = true;
				}

				adjustH = tempH;
			}

			else if (location == 1)
			{
				adjustH = 0;

				while (!isBool)
				{
					if (tempW - 50 < adjustW && adjustW < tempW)
					{
						for (int j = 0; j < 10; j++)
							tempW = rand() % 600;
					}

					else
						isBool = true;
				}

				adjustW = tempW;
			}

			else
			{
				adjustW = 600;

				while (!isBool)
				{
					if ((tempH - 50) < adjustH && adjustH < (tempH))
						adjustH = rand() % 200;

					else
						isBool = true;
				}

				adjustH = tempH;
			}

			Comet* comet = new Comet();
			comet->Init(adjustW, adjustH);

			vecEnemys.push_back(comet);
		}

		isComet = true;
	}
}

void EnemyManager::AddJellyFish(int num)
{
	if (!isJellyFish)
	{
		for (int i = 0; i < num; i++)
		{
			JellyFish* jellyFish = new JellyFish();
			jellyFish->Init(100 * (i % num), 100);

			vecEnemys.push_back(jellyFish);
		}

		isJellyFish = true;
	}
}

void EnemyManager::AddUFO(int num)
{
	if (!isUFO)
	{
		for (int i = 0; i < num; i++)
		{
			UFO* ufo = new UFO();
			ufo->Init(WINSIZE_X + 100 + (i % 5) * 100, -100 + (i / 5) * 80);

			vecEnemys.push_back(ufo);
		}

		isUFO = true;
	}
}

void EnemyManager::AddUFOEnemy(int num)
{
	if (!isUFOEnemy)
	{
		for (int i = 0; i < num; i++)
		{
			UFOEnemy* ufoEnemy = new UFOEnemy();
			ufoEnemy->Init(-100 + (i % 5) * 100, -100 + (i / 5) * 80);

			vecEnemys.push_back(ufoEnemy);
		}

		isUFOEnemy = true;
	}
}

void EnemyManager::AddCuteEye(int num)
{
	if (!isCuteEye)
	{
		for (int i = 0; i < num; i++)
		{
			CuteEye* cuteEye = new CuteEye();
			cuteEye->Init(WINSIZE_X + 20 + (i % 5) * 100, 120 + (i / 5) * 80);

			vecEnemys.push_back(cuteEye);
		}

		isCuteEye = true;
	}
}

void EnemyManager::AddShyEye(int num)
{
	if (!isShyEye)
	{
		for (int i = 0; i < num; i++)
		{
			ShyEye * shyEye = new ShyEye();
			shyEye->Init(-100 + (i % 5) * 100, -100 + (i / 5) * 80);

			vecEnemys.push_back(shyEye);
		}

		isShyEye = true;
	}
}

void EnemyManager::AddBoss1()
{
	if (!isBoss1)
	{
		GiantBalloon * isGinatBallon = new GiantBalloon();
		isGinatBallon->Init(WINSIZE_X / 2, 100);

		vecEnemys.push_back(isGinatBallon);

		isBoss1 = true;
	}
}

void EnemyManager::SetIsBool(bool _isSwitch)
{
	isSwitch = _isSwitch;

	if (!isSwitch)
	{
		isBombMan = false;
		isComet = false;
		isCuteEye = false;
		isShyEye = false;
		isJellyFish = false;
		isUFO = false;
		isUFOEnemy = false;
		isBoss1 = false;
	}

	else
	{
		isBombMan = true;
		isComet = true;
		isCuteEye = true;
		isShyEye = true;
		isJellyFish = true;
		isUFO = true;
		isUFOEnemy = true;
		isBoss1 = true;
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
