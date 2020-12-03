#pragma once

#include "GameNode.h"

class Image;
class SieKensou2;

class SieKensou : public GameNode
{
private:
	//캐릭터 설정
	FPOINT pos;
	CRECT cRect;

	int hp;
	int attack;
	int blast;
	bool isWin;
	bool isPlayer;

	CHARINF standInf, sitDownInf, jumpInf;
	CHARINF leftInf,  rightInf;
	CHARINF eatInf;
	CHARINF jabInf,	  kickInf;
	CHARINF energyInf, energyWaveInf;
	CHARINF defendInf;
	CHARINF sufferInf;
	CHARINF deadInf;

	int curKeyFrameX, curKeyFrameY;
	int elapsedFrame;
	float scale;

	Image * stand, * sitDown, * jump;
	Image * left,  * right;
	Image * eat;
	Image * jab,   * kick;
	Image * energy, * energyWave;
	Image * defend;
	Image * suffer;
	Image * dead;

	SieKensou2 * target;

	HPEN		hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;

public:
	// override 문법적으로 잘못 사용하였을 때 에러 키워드를 띄어준다.
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float _x);
	void SetPosY(float _y);
	void SetScale(float _scale);
	void SetStandInf(bool TF);
	void SetSuffer(bool TF);
	void SetTarget(SieKensou2 * enemyInf);
	void SetBack(float push);
	void SetLoseHp(int _hp);

	CHARINF GetJabInf();
	CHARINF GetKickInf();
	CHARINF GetDefendInf();
	CHARINF GetSufferInf();
	CRECT GetCharInf();
	SieKensou2 * GetTarget();
	int GetHp();
	int GetAttack();
	bool GetIsPlayer();
	bool GetIsWin();

	SieKensou();
	~SieKensou();
};

