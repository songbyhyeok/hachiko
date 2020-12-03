#include "Missile.h"
#include "macroFunction.h"
#include "Enemy.h"
#include "Image.h"

HRESULT Missile::Init(Image * lowImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;		
	angleY = PI / 4.0f;	adjustAngle = 0.0f;
	angleX = PI / 4.0f;

	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	img = lowImg;

	istest = false;

	return S_OK;
}

void Missile::Release(){}

void Missile::Update(int num, int remainder)
{
	

	if (isFire)
	{
		
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();

		
		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);

		if (9999 <= pos.x && 9999 <= pos.y)
		{
			isFire = false;
		}
	}

	SetMaxFrameDetermine(num, remainder);
}

void Missile::Render(HDC hdc)
{
	if (isFire && !istest)
	{
		if (img && !isCrash)
		{
			img->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

void Missile::SetTarget(GameNode* enemy) { target = enemy; }
void Missile::SetSpeed(float _speed) { speed = _speed; }
void Missile::SetAngleX(float _angleX) { angleX = _angleX; }
void Missile::SetAngleY(float _angleY) { angleY = _angleY; }
void Missile::SetIsFire(bool _isFire) { isFire = _isFire; }

bool Missile::GetIsFire() { return isFire; }
float Missile::GetSize() { return size; }

Missile::Missile()
{}

Missile::~Missile()
{}

HRESULT NormalMissile::Init(Image * norImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;
	angleX = PI / 4.0f;	adjustAngle = 0.0f;

	//SetFrame(0, 0, 0, 1, 7);
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	/*img = ImageManager::GetSingleton()->AddImage("BasicWeapon", "Image/BasicWeapon.bmp",
		pos.x, pos.y, width, height, 1, 7, true, RGB(255, 0, 255));*/


	normalImg = norImg;

	return S_OK;
}

void NormalMissile::Release()
{
}

void NormalMissile::Update(int num, int remainder)
{
	if (isFire)
	{
	
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
	}

	SetMaxFrameDetermine(num, remainder);
}

void NormalMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (normalImg && !isCrash)
		{
			normalImg->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

NormalMissile::NormalMissile(){}

NormalMissile::~NormalMissile(){}

HRESULT HighMissile::Init(Image * _highImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;
	//angle = PI / 4.0f;	adjustAngle = 0.0f;

	//SetFrame(0, 0, 0, 1, 7);
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	/*img = ImageManager::GetSingleton()->AddImage("BasicWeapon", "Image/BasicWeapon.bmp",
		pos.x, pos.y, width, height, 1, 7, true, RGB(255, 0, 255));*/

	highImg = _highImg;

	return S_OK;
}

void HighMissile::Release(){}

void HighMissile::Update()
{
	SetHitBox(pos, width, height / 3);
	SetMoveFrameY(4,5);
}

void HighMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (highImg && !isCrash)
		{
			highImg->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

	}
}

HighMissile::HighMissile(){}

HighMissile::~HighMissile(){}

//#######


HRESULT EnemyMissile::Init(Image * _enemyImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;
	angleX = PI / 4.0f;	adjustAngle = 0.0f;

	//SetFrame(0, 0, 0, 1, 7);
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	/*img = ImageManager::GetSingleton()->AddImage("BasicWeapon", "Image/BasicWeapon.bmp",
		pos.x, pos.y, width, height, 1, 7, true, RGB(255, 0, 255));*/

	enemyImg = _enemyImg;

	return S_OK;
}

void EnemyMissile::Release()
{
}

void EnemyMissile::Update(int num, int remainder)
{
	if (isFire)
	{
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();

		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
	}

	SetMaxFrameDetermine(num, remainder);
}

void EnemyMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (enemyImg && !isCrash)
		{
			enemyImg->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
}

//#######




HRESULT Enemy1Missile::Init(Image * _enemy1Img, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;
	angleX = PI / 4.0f;	adjustAngle = 0.0f;

	//SetFrame(0, 0, 0, 1, 7);
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	/*img = ImageManager::GetSingleton()->AddImage("BasicWeapon", "Image/BasicWeapon.bmp",
		pos.x, pos.y, width, height, 1, 7, true, RGB(255, 0, 255));*/

	enemy1Img = _enemy1Img;

	return S_OK;
}

void Enemy1Missile::Release()
{
}

void Enemy1Missile::Update(int num, int remainder)
{
	if (isFire)
	{
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();
		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
	}
	SetMaxFrameDetermine(num, remainder);
}

void Enemy1Missile::Render(HDC hdc)
{
	if (isFire)
	{
		if (enemy1Img && !isCrash)
		{
			enemy1Img->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

Enemy1Missile::Enemy1Missile()
{
}

Enemy1Missile::~Enemy1Missile()
{
}

//#######


HRESULT UFOMissile::Init(Image * _ufoImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	width = _width;			height = _height;

	speed = 50.0f;
	angleX = PI / 4.0f;	adjustAngle = 0.0f;

	//SetFrame(0, 0, 0, 1, 7);
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	/*img = ImageManager::GetSingleton()->AddImage("BasicWeapon", "Image/BasicWeapon.bmp",
		pos.x, pos.y, width, height, 1, 7, true, RGB(255, 0, 255));*/

	ufoImg = _ufoImg;

	return S_OK;
}

void UFOMissile::Release()
{
}

void UFOMissile::Update(int num, int remainder)
{ 
	if (isFire)
	{
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();
		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
	}
	SetMaxFrameDetermine(num, remainder);
}

void UFOMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (ufoImg && !isCrash)
		{
			ufoImg->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

UFOMissile::UFOMissile()
{
}

UFOMissile::~UFOMissile()
{
}
//#######



HRESULT EyeMissile::Init(Image * _eyeImg, int _width, int _height, int maxKeyX, int maxKeyY)
{
	
	/*img = ImageManager::GetSingleton()->AddImage("CharacterMissile", "Image/MISSILE/missile2.bmp",
		pos.x, pos.y, width, height, 1, 1, true, RGB(255, 0, 255));*/

	width = _width;			height = _height;
	speed = 50.0f;
	angleX = PI / 4.0f;	adjustAngle = 0.0f;

	
	SetFrame(0, 0, 0, maxKeyX, maxKeyY);

	isFire = false;
	isCrash = false;
	target = nullptr;

	eyeImg = _eyeImg;
	   

	return S_OK;
}

void EyeMissile::Release()
{
}

void EyeMissile::Update(int num, int remainder)
{
	if (isFire)
	{
		pos.x += speed * cosf(angleX) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angleY) * TimeManager::GetSingleton()->GetDeltaTime();
		SetHitBox(pos, width / key.maxFrameX, height / key.maxFrameY);
	}
	SetMaxFrameDetermine(num, remainder);
}

void EyeMissile::Render(HDC hdc)
{
	if (isFire)
	{
		if (eyeImg && !isCrash)
		{
			eyeImg->FrameRender(hdc, pos.x, pos.y, key.curFrameX, key.curFrameY);
			//HitBoxRender(hdc, hitBox);
		}

		//RenderEllipseToCenter(hdc, leftX, leftY, pos.x, pos.y);
		//RenderEllipseToCenter(hdc, rightX, rightY, pos.x, pos.y);
	}
}

EyeMissile::EyeMissile()
{
}

EyeMissile::~EyeMissile()
{
}
