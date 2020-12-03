#pragma once

#include "GameNode.h"

class UI;
class SieKensou;
class SieKensou2;

class Collision
{
private:
	UI * isUI;
	SieKensou * player1;	SieKensou2 * player2;

public:
	virtual HRESULT Init();	// ������� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();	// �޸� ����
	virtual void Update();	// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);
	
	void ManageMentHP();
	void ManageMentHit();
	void ManageMentSkill();
	void ManageMentName(HDC hdc, int selectP1, int selectP2);
	void RenderKO(HDC hdc);
	void RenderHitBar(HDC hdc);
	void RenderHpBar(HDC hdc);
	void RenderSkill(HDC hdc);
	void RenderProfile(HDC hdc, int selectP1, int selectP2);

	void SetWinLose(HDC hdc);
	void SetPlayer(SieKensou * _player1, SieKensou2 * _player2);

	void CheckPlayerCollision();

	HPEN		hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;
	HFONT		myFont, oldFont;
};

