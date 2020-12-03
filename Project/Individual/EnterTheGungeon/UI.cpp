#include "UI.h"
#include "Player.h"
#include "MissileFactory.h"
#include "Missile.h"

HRESULT UI::Init()
{
	heart = ImageManager::GetSingleton()->AddImage(3, "체력", "Image/UI/heart.bmp", 0, 0, 100, 43,
		2, 1, true, RGB(255, 0, 255));

	heartKey = new KEYFRAME[3];

	for (int i = 0; i < 3; i++)
		SetFrame(&heartKey[i], 0, 0, 0, 2, 1);

	power = ImageManager::GetSingleton()->AddImage("파워", "Image/UI/power.bmp", 30, 42, true, RGB(255, 0, 255));
	speed = ImageManager::GetSingleton()->AddImage("속도", "Image/UI/speed.bmp", 50, 45, true, RGB(255, 0, 255));
	time = ImageManager::GetSingleton()->AddImage("시간", "Image/UI/time.bmp", 50, 45, true, RGB(255, 0, 255));
	bullet = ImageManager::GetSingleton()->AddImage("총알", "Image/UI/bullet.bmp", 20, 40, true, RGB(255, 0, 255));

	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));

	reloadBox = { 0,0,0,0 };
	reloadGauge = { 0,0,0,0 };

	hBrush = CreateSolidBrush(RGB(255, 0, 255));

	gaugeX = gaugeY = 0;

	elapsedTime = 2;
	count = 0;

	reload = false;
	isReady = false;

	hit = 180;

	return S_OK;
}

void UI::Release()
{
	SAFE_ARR_DELETE(heartKey);

	DeleteObject(hFont);
}

void UI::Update()
{
	if (reload)
		ReloadUI();

	if (player->GetHp() == 50)
		heartKey[2].curFrameX = heartKey[2].curFrameX + 1;

	else if (player->GetHp() == 40)
		hit = 120;

	else if (player->GetHp() == 30)
		heartKey[1].curFrameX = heartKey[1].curFrameX + 1;

	else if (player->GetHp() == 20)
		hit = 60;

	else if (player->GetHp() == 10)
		heartKey[0].curFrameX = heartKey[0].curFrameX + 1;

	else if (player->GetHp() == 0)
		hit = 0;
}

void UI::Render(HDC hdc)
{
	for (int i = 0; i < hit / 60; i++)
		heart[i].FrameRender(hdc, 50 + (heart[i].GetFrameWidth() * i), 40, heartKey[i].curFrameX, heartKey[i].curFrameY);

	power->Render(hdc, 50, 95);
	sprintf_s(szText, "%d", *player->GetMissileMf()->GetMissileNum());
	TextOut(hdc, 70, 95, szText, strlen(szText));

	speed->Render(hdc, 50, 150);

	bullet->Render(hdc, 50, 200);
	sprintf_s(szText, "%d", *player->GetMissileMf()->GetMissileNum());
	TextOut(hdc, 70, 200, szText, strlen(szText));

	if (reload)
	{
		RenderRectToCenter(hdc, player->GetPos().x, player->GetPos().y - 25, 40, 10);
		SelectObject(hdc, hBrush);
		RenderRect(hdc, reloadGauge.left, reloadGauge.top, reloadGauge.right, reloadGauge.bottom);
	}

}

void UI::ReloadUI()
{
	reloadGauge = { (float)player->GetPos().x - 20, (float)player->GetPos().y - 30, (float)player->GetPos().x + 20 - gaugeX, (float)player->GetPos().y - 20 };

	int tempFirstX = player->GetPos().x - 20;
	int tempSecondX = player->GetPos().x + 20 - gaugeX;

	count++;
	if (count % elapsedTime == elapsedTime - 1)
	{
		gaugeX += 1;
		count = 0;
	}

	if (tempFirstX > tempSecondX)
	{
		gaugeX = 0;

		reload = false;
		isReady = true;
	}
}

void UI::SetReload(bool _reload)
{
	reload = _reload;
}

bool UI::GetReload()
{
	return reload;
}

void UI::SetIsReady(bool _isReady)
{
	isReady = _isReady;
}

bool UI::GetIsReady()
{
	return isReady;
}

void UI::SetPlayer(Player * _player)
{
	player = _player;
}
