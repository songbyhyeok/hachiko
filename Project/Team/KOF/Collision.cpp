#include "Collision.h"
#include "UI.h"
#include "SieKensou.h"
#include "SieKensou2.h"

HRESULT Collision::Init()
{
	isUI = new UI();
	isUI->Init();

	player1 = nullptr;		player2 = nullptr;

	return S_OK;
}

void Collision::Release()
{
	isUI->Release();
	delete isUI;
}

void Collision::Update()
{
	CheckPlayerCollision();
	ManageMentHP();
	ManageMentHit();
	ManageMentSkill();
}

void Collision::Render(HDC hdc)
{
	ManageMentName(hdc, 0, 2);
	SetWinLose(hdc);
	RenderKO(hdc);
	RenderHitBar(hdc);
	RenderHpBar(hdc);
	RenderSkill(hdc);
}

void Collision::ManageMentHP()
{
	if (isUI->GetHpInf()->bar1P.right <= 100)
		isUI->GetHpInf()->bar1P.right = 100;

	else if (isUI->GetHpInf()->redBar1P.right <= 100)
		isUI->GetHpInf()->redBar1P.right = 100;

	if (isUI->GetHpInf()->bar2P.right <= 1000)
		isUI->GetHpInf()->bar2P.right = 1000;

	else if (isUI->GetHpInf()->redBar2P.right <= 1000)
		isUI->GetHpInf()->redBar2P.right = 1000;

	if (player1->GetSufferInf().moveMent)
		isUI->GetHpInf()->bar1P.right -= 1;

	if (isUI->GetHpInf()->bar1P.right != isUI->GetHpInf()->redBar1P.right)
	{
		isUI->GetHpInf()->frame++;
		if (isUI->GetHpInf()->frame % 3 == 2)
		{
			isUI->GetHpInf()->frame = 0;

			isUI->GetHpInf()->redBar1P.right -= 1;
		}
	}

	if (player2->GetSufferInf().moveMent)
		isUI->GetHpInf()->bar2P.right -= 1;

	if (isUI->GetHpInf()->bar2P.right != isUI->GetHpInf()->redBar2P.right)
	{
		isUI->GetHpInf()->frame++;
		if (isUI->GetHpInf()->frame % 3 == 2)
		{
			isUI->GetHpInf()->frame = 0;

			isUI->GetHpInf()->redBar2P.right -= 1;
		}
	}
}

void Collision::ManageMentHit()
{
	isUI->GetHitBarInf()->frame++;
	if (player2->GetSufferInf().moveMent && isUI->GetHitBarInf()->frame % 8 == 7)
	{
		isUI->GetHitBarInf()->frame = 0;

		isUI->GetHitBarInf()->score1P++;
	}

	if (player1->GetSufferInf().moveMent && isUI->GetHitBarInf()->frame % 8 == 7)
	{
		isUI->GetHitBarInf()->frame = 0;

		isUI->GetHitBarInf()->score2P++;
	}

	if (isUI->GetHitBarInf()->score1P > 0 && isUI->GetHitBarInf()->frame % 30 == 29)
	{
		isUI->GetHitBarInf()->frame = 0;

		isUI->GetHitBarInf()->score1P = 0;
	}

	if (isUI->GetHitBarInf()->score2P > 0 && isUI->GetHitBarInf()->frame % 30 == 29)
	{
		isUI->GetHitBarInf()->frame = 0;

		isUI->GetHitBarInf()->score2P = 0;
	}
}

void Collision::ManageMentSkill()
{
	if (player1->GetJabInf().moveMent && player2->GetSufferInf().moveMent ||
		player1->GetKickInf().moveMent && player2->GetSufferInf().moveMent)
	{
		isUI->GetSkillBarInf()->frame++;
		if (isUI->GetSkillBarInf()->frame % 3 == 2)
		{
			isUI->GetSkillBarInf()->frame = 0;

			isUI->GetSkillBarInf()->stack1P.right += 3;
		}
	}

	if (player2->GetJabInf().moveMent && player1->GetSufferInf().moveMent ||
		player2->GetKickInf().moveMent && player1->GetSufferInf().moveMent)
	{
		isUI->GetSkillBarInf()->frame++;
		if (isUI->GetSkillBarInf()->frame % 3 == 2)
		{
			isUI->GetSkillBarInf()->frame = 0;

			isUI->GetSkillBarInf()->stack2P.right -= 3;
		}
	}
	
	if (isUI->GetSkillBarInf()->stack1P.right >= isUI->GetSkillBarInf()->border1P.right)
	{
		isUI->GetSkillBarInf()->stack1P.right = 130;

		isUI->GetSkillBarInf()->skillCount1P++;
	}

	if (isUI->GetSkillBarInf()->stack2P.right <= isUI->GetSkillBarInf()->border2P.left)
	{
		isUI->GetSkillBarInf()->stack2P.right = 1370;

		isUI->GetSkillBarInf()->skillCount2P++;
	}

	if (isUI->GetSkillBarInf()->skillCount1P == 5)
		isUI->GetSkillBarInf()->skillCount1P = 0;

	else if (isUI->GetSkillBarInf()->skillCount2P == 5)
		isUI->GetSkillBarInf()->skillCount2P = 0;
}

void Collision::ManageMentName(HDC hdc, int select1P, int select2P)
{
	/*
	YOU SELECT -> PLAYER::TERRY		PLAYER::KENSOU		PLAYER::Koehan
							0번				 1번					2번
	*/
	
	if (player1)
	{
		myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
		oldFont = (HFONT)SelectObject(hdc, myFont);
	
		SetTextColor(hdc, RGB(0, 0, 255));	// 블루색
		TextOut(hdc, 100, 9, isUI->GetPlayerNameInf()[select1P], strlen(isUI->GetPlayerNameInf()[select1P]) + 1);
		TextOut(hdc, 100, 10, isUI->GetPlayerNameInf()[select1P], strlen(isUI->GetPlayerNameInf()[select1P]) + 1);
		TextOut(hdc, 100, 11, isUI->GetPlayerNameInf()[select1P], strlen(isUI->GetPlayerNameInf()[select1P]) + 1);
	
		SetBkMode(hdc, 1);
	
		DeleteObject(myFont);
	}
	
	if (player2)
	{
		myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
		oldFont = (HFONT)SelectObject(hdc, myFont);
	
		SetTextColor(hdc, RGB(240, 160, 0));	// 옅은 주황
		TextOut(hdc, 1000, 9, isUI->GetPlayerNameInf()[select2P], strlen(isUI->GetPlayerNameInf()[select2P]) + 1);
		TextOut(hdc, 1000, 10, isUI->GetPlayerNameInf()[select2P], strlen(isUI->GetPlayerNameInf()[select2P]) + 1);
		TextOut(hdc, 1000, 11, isUI->GetPlayerNameInf()[select2P], strlen(isUI->GetPlayerNameInf()[select2P]) + 1);
	
		SetBkMode(hdc, 1);
	
		DeleteObject(myFont);
	}
}

void Collision::RenderKO(HDC hdc)
{
	if (isUI->GetKoInf()->mode)
	{
		if (isUI->GetKoInf() && !player1->GetIsWin())
		{
			isUI->GetKoInf()->frame++;
			if (isUI->GetKoInf()->frame % 10 == 9)
			{
				isUI->GetKoInf()->frame = 0;

				isUI->GetKoInf()->koBG->Render(hdc, 0, 0);
			}
		}

		else if (isUI->GetKoInf() && !player2->GetIsWin())
		{
			isUI->GetKoInf()->frame++;
			if (isUI->GetKoInf()->frame % 10 == 9)
			{
				isUI->GetKoInf()->frame = 0;

				isUI->GetKoInf()->koBG->Render(hdc, 0, 0);
			}
		}
	}
}

void Collision::RenderHitBar(HDC hdc)
{	
	// RUSH
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	if (player2->GetSufferInf().moveMent)
		TextOut(hdc, 100, 100, isUI->GetHitBarInf()->name[UI::RUSHORHIT::RUSH], strlen(isUI->GetHitBarInf()->name[UI::RUSHORHIT::RUSH]) + 1);

	if (player1->GetSufferInf().moveMent)
		TextOut(hdc, 1000, 100, isUI->GetHitBarInf()->name[UI::RUSHORHIT::RUSH + 1], strlen(isUI->GetHitBarInf()->name[UI::RUSHORHIT::RUSH + 1]) + 1);

	SetBkMode(hdc, 1);

	DeleteObject(myFont);

	// NUMBER
	myFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	SetTextColor(hdc, RGB(255, 0, 0));
	
	sprintf_s(isUI->GetHitBarInf()->scoreSave1P, "%d ", isUI->GetHitBarInf()->score1P);
	if (player2->GetSufferInf().moveMent)
		TextOut(hdc, 180, 90, isUI->GetHitBarInf()->scoreSave1P, strlen(isUI->GetHitBarInf()->scoreSave1P) + 1);

	sprintf_s(isUI->GetHitBarInf()->scoreSave2P, "%d ", isUI->GetHitBarInf()->score2P);
	if (player1->GetSufferInf().moveMent)
		TextOut(hdc, 1080, 90, isUI->GetHitBarInf()->scoreSave2P, strlen(isUI->GetHitBarInf()->scoreSave2P) + 1);

	SetBkMode(hdc, 1);

	DeleteObject(myFont);

	// HIT
	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	if (player2->GetSufferInf().moveMent)
		TextOut(hdc, 250, 100, isUI->GetHitBarInf()->name[UI::RUSHORHIT::HITS], strlen(isUI->GetHitBarInf()->name[UI::RUSHORHIT::HITS]) + 1);

	if (player1->GetSufferInf().moveMent)
		TextOut(hdc, 1160, 100, isUI->GetHitBarInf()->name[UI::RUSHORHIT::HITS + 1], strlen(isUI->GetHitBarInf()->name[UI::RUSHORHIT::HITS + 1]) + 1);

	SetBkMode(hdc, 1);

	DeleteObject(myFont);
}

void Collision::RenderHpBar(HDC hdc)
{
	//HP 테두리
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, isUI->GetHpInf()->border1P, isUI->GetHpInf()->border2P);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);
	
	//레드 체력
	hBrush = CreateSolidBrush(RGB(255, 120, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, isUI->GetHpInf()->redBar1P, isUI->GetHpInf()->redBar2P);

	DeleteObject(hBrush);

	//초록색 체력
	hBrush = CreateSolidBrush(RGB(45, 205, 45));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, isUI->GetHpInf()->bar1P, isUI->GetHpInf()->bar2P);

	DeleteObject(hBrush);
}

void Collision::RenderSkill(HDC hdc)
{
	//삼각형바 
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RenderRect(hdc, isUI->GetSkillBarInf()->triangleBorder1P, isUI->GetSkillBarInf()->triangleBorder2P);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RenderRect(hdc, isUI->GetSkillBarInf()->blackBorder1P, isUI->GetSkillBarInf()->blackBorder2P);

	DeleteObject(hBrush);

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	
	isUI->GetSkillBarInf()->triangleFrame++;
	if (isUI->GetSkillBarInf()->triangleFrame % 10 == 9)
	{
		isUI->GetSkillBarInf()->triangleFrame = 0;

		MoveToEx(hdc, 110, 370, NULL);
		LineTo(hdc, 125, 385);
		LineTo(hdc, 110, 400);
		LineTo(hdc, 110, 370);

		MoveToEx(hdc, 1390, 370, NULL);
		LineTo(hdc, 1375, 385);
		LineTo(hdc, 1390, 400);
		LineTo(hdc, 1390, 370);
	}

	DeleteObject(hPen);
	
	//기술바 테두리
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, isUI->GetSkillBarInf()->border1P, isUI->GetSkillBarInf()->border2P);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	//기술바 게이지
	hBrush = CreateSolidBrush(RGB(255, 120, 0));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, isUI->GetSkillBarInf()->stack1P, isUI->GetSkillBarInf()->stack2P);
	
	DeleteObject(hBrush);

	//기술바 개수
	hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	for (int i = 0; i < SKILL_BOX; i++)
		RenderRect(hdc, isUI->GetSkillBarInf()->rect1P[i], isUI->GetSkillBarInf()->rect2P[i]);
	
	DeleteObject(hPen);
	DeleteObject(hBrush);

	//기술바 생성
	isUI->GetSkillBarInf()->frame++;
	if (isUI->GetSkillBarInf()->frame % 10 == 9)
	{
		isUI->GetSkillBarInf()->frame = 0;

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	}
	
	for (int i = 0; i < isUI->GetSkillBarInf()->skillCount1P; i++)
		RenderRect(hdc, isUI->GetSkillBarInf()->rect1P[i]);

	for (int i = 0; i < isUI->GetSkillBarInf()->skillCount2P; i++)
		RenderRect(hdc, isUI->GetSkillBarInf()->rect2P[i]);

	DeleteObject(hBrush);
}

void Collision::RenderProfile(HDC hdc, int selectP1, int selectP2)
{
	if (player1->GetIsPlayer())
	{
		if (selectP1 == 0)
			isUI->GetProfileInf()->terry1P->Render(hdc, 100, 0);

		else if (selectP1 == 1)
			isUI->GetProfileInf()->kensou1P->Render(hdc, 100, 0);

		else if (selectP1 == 2)
			isUI->GetProfileInf()->koehan1P->Render(hdc, 100, 0);
	}

	if (player2->GetIsPlayer())
	{
		if (selectP2 == 0)
		isUI->GetProfileInf()->terry2P->Render(hdc, 1400, 0);

		else if (selectP2 == 1)
		isUI->GetProfileInf()->kensou2P->Render(hdc, 1400, 0);

		else if (selectP2 == 2)
		isUI->GetProfileInf()->koehan2P->Render(hdc, 1400, 0);
	}
}

void Collision::SetWinLose(HDC hdc)
{
	myFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	oldFont = (HFONT)SelectObject(hdc, myFont);

	if (isUI->GetHpInf()->redBar2P.right == 600)
	{
		if (player1->GetIsWin())
		{
			TextOut(hdc, 300, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::WIN], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::WIN]) + 1);
			TextOut(hdc, 1000, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE]) + 1);
		}

		else
		{
			TextOut(hdc, 300, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE]) + 1);
			TextOut(hdc, 1000, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::WIN], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::WIN]) + 1);
		}
	}

	else if (isUI->GetHpInf()->redBar1P.right == 100)
	{
		if (player2->GetIsWin())
		{
			TextOut(hdc, 1000, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::WIN], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::WIN]) + 1);
			TextOut(hdc, 300, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE]) + 1);
		}

		else
		{
			TextOut(hdc, 1000, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::LOSE]) + 1);
			TextOut(hdc, 300, 150, isUI->GetHpInf()->decide[UI::WINORLOSE::WIN], strlen(isUI->GetHpInf()->decide[UI::WINORLOSE::WIN]) + 1);
		}
	}

	SetTextColor(hdc, RGB(0, 0, 255));
	SetBkMode(hdc, 1);
	SelectObject(hdc, oldFont);

	DeleteObject(myFont);
}

void Collision::SetPlayer(SieKensou * _player1, SieKensou2 * _player2) { player1 = _player1;	player2 = _player2;}

void Collision::CheckPlayerCollision()
{
	if (player1->GetJabInf().moveMent && !player2->GetDefendInf().moveMent ||
		player1->GetKickInf().moveMent && !player2->GetDefendInf().moveMent)
	{
		if (CheckRectCollision(player1->GetCharInf().hit, player2->GetCharInf().body))
		{
			player2->SetStandInf(false);
			player2->SetSuffer(true);
		}
	}

	if (player2->GetJabInf().moveMent && !player1->GetDefendInf().moveMent ||
		player2->GetKickInf().moveMent && !player1->GetDefendInf().moveMent)
	{
		if (CheckRectCollision(player2->GetCharInf().hit, player1->GetCharInf().body))
		{
			player1->SetStandInf(false);
			player1->SetSuffer(true);
		}
	}

	if (player1->GetDefendInf().moveMent && player2->GetKickInf().moveMent ||
		player1->GetDefendInf().moveMent && player2->GetJabInf().moveMent)
	{
		if (CheckRectCollision(player1->GetCharInf().defence, player2->GetCharInf().hit))
			player1->SetBack(10);
	}

	if (player2->GetDefendInf().moveMent && player1->GetKickInf().moveMent ||
		player2->GetDefendInf().moveMent && player1->GetJabInf().moveMent)
	{
		if (CheckRectCollision(player2->GetCharInf().defence, player1->GetCharInf().hit))
			player2->SetBack(10);
	}
}

