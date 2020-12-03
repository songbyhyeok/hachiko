#pragma once
#include "pch.h"
#include "GameNode.h"

class Missile;
class NormalMissile;
class HighMissile;
class Enemy1Missile;
class EnemyMissile;
class UFOMissile;
class EyeMissile;
class Enemy;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vecMissiles;
	vector<Missile*>::iterator itMissiles;
	vector<NormalMissile*> vecNormalMissiles;
	vector<NormalMissile*>::iterator itNormalMissiles;
	vector<HighMissile*> vecHighMissiles;
	vector<HighMissile*>::iterator itHighMissiles;

	//
	vector<EnemyMissile*> vecEnemyMissiles;
	vector<EnemyMissile*>::iterator itEnemyMissiles;
	vector<Enemy1Missile*> vecEnemy1Missiles;
	vector<Enemy1Missile*>::iterator itEnemy1Missiles;
	vector<UFOMissile*> vecUFOMissiles;
	vector<UFOMissile*>::iterator itUFOMissiles;
	vector<EyeMissile*> vecEyeMissiles;
	vector<EyeMissile*>::iterator itEyeMissiles;


	GameNode* owner;
	Enemy * isEnemy;

	bool isTarget;
	float angle;
	float rotateAngle;

	int fireCount;
	int fireDelay;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(int num = 0, int remainder = 0);
	virtual void Render(HDC hdc);

	void SetFireDelay(int maxDelay, int minDelay);
	bool FireMode(float _angleX,float _angleY, float _speed, float x = 0, float y = 0);
	bool playerFireMode(float _angle, float _speed);

	void SetAngle(float _angle) { angle = _angle; }
	float GetAngle() { return angle; }

	void SetRorAngle(float _rotateAngle) { rotateAngle = _rotateAngle; }
	float GetRorAngle() { return rotateAngle; }

	void SetTarget(Enemy * enemy) { enemy = isEnemy; }
	void SetTargetMode(bool targetMode) { isTarget = targetMode; }
	bool GetTargetMode() { return isTarget; }
	
	void SetOwner(GameNode* gameNode) { owner = gameNode; }

	void SetMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);
	void SetNorMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);
	void SetHighMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);

	void SetEnemyMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);
	void SetEnemy1MissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);
	void SetUFOMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);
	void SetEyeMissileInf(Image * image, int _width, int _height, int maxKeyX, int maxKeyY);

	void SetBullet(int _bullet){ vecMissiles.reserve(_bullet);}
	void SetNorBullet(int _bullet){ vecNormalMissiles.reserve(_bullet);}
	void SetHighBullet(int _bullet){ vecHighMissiles.reserve(_bullet);}
	
	////
	void SetEnemyBullet(int _bullet) { vecEnemyMissiles.reserve(_bullet); }
	void SetEnemy1Bullet(int _bullet) { vecEnemy1Missiles.reserve(_bullet); }
	void SetUFOBullet(int _bullet) { vecUFOMissiles.reserve(_bullet); }
	void SetEyeBullet(int _bullet) { vecHighMissiles.reserve(_bullet); }


	vector<Missile*> GetMissile() { return vecMissiles; }
	vector<Missile*>::iterator GetMissileIte() { return itMissiles; }

	vector<NormalMissile*> GetNormalMissile() { return vecNormalMissiles; }
	vector<NormalMissile*>::iterator GetNormalMissileIte() { return itNormalMissiles; }

	vector<HighMissile*> GetHighMissile() { return vecHighMissiles; }
	vector<HighMissile*>::iterator GetHighMissileIte() { return itHighMissiles; }

	////
	vector<EnemyMissile*> GetEnemyMissile() { return vecEnemyMissiles; }
	vector<EnemyMissile*>::iterator GetEnemyMissileIte() { return itEnemyMissiles; }

	vector<Enemy1Missile*> GetEnemy1Missile() { return vecEnemy1Missiles; }
	vector<Enemy1Missile*>::iterator GetEnemy1MissileIte() { return itEnemy1Missiles; }

	vector<UFOMissile*> GetUFOMissile() { return vecUFOMissiles; }
	vector<UFOMissile*>::iterator GetUFOMissileIte() { return itUFOMissiles; }

	vector<EyeMissile*> GetEyeMissile() { return vecEyeMissiles; }
	vector<EyeMissile*>::iterator GetEyeMissileIte() { return itEyeMissiles; }






	MissileManager();
	~MissileManager();
};

