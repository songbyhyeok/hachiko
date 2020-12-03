#pragma once

#include "GameNode.h"

class Image;
class SieKensou;

class SieKensou2 : public GameNode
{
private:
	//ĳ���� ����
	FPOINT pos;
	CRECT cRect;

	CHARINF standInf, sitDownInf, jumpInf;
	CHARINF leftInf, rightInf;
	CHARINF eatInf;
	CHARINF jabInf, kickInf;
	CHARINF defendInf;
	CHARINF sufferInf;
	CHARINF deadInf;

	int hp;
	bool isWin;
	bool isPlayer;

	int curKeyFrameX, curKeyFrameY;
	int elapsedFrame;
	float scale;

	Image * stand, *sitDown, *jump;
	Image * left, *right;
	Image * eat;
	Image * jab, *kick;
	Image * defend;
	Image * suffer;
	Image * dead;

	SieKensou * target;

	HPEN			hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;

public:
	// override ���������� �߸� ����Ͽ��� �� ���� Ű���带 ����ش�.
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float _x);
	void SetPosY(float _y);
	void SetScale(float _scale);
	void SetStandInf(bool TF);
	void SetSuffer(bool TF);
	void SetTarget(SieKensou * enemyInf);
	void SetBack(float push);
	void SetLoseHp(int _hp);

	CHARINF GetJabInf();
	CHARINF GetKickInf();
	CHARINF GetDefendInf();
	CHARINF GetSufferInf();
	CRECT GetCharInf();
	SieKensou * GetTarget();
	int GetHp();
	bool GetIsPlayer();
	bool GetIsWin();

	SieKensou2();
	~SieKensou2();
};

