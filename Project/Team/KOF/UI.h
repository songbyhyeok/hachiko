#pragma once

#include "GameNode.h"

#define NAME_SIZE 10
#define PLAYER_NUM 3
#define HITBAT_TYPE 4
#define HITBAT_SIZE 5
#define SKILL_BOX 4

class Image;

class UI
{
public:
	enum WINORLOSE { WIN, LOSE, END};
	enum RUSHORHIT { RUSH, HITS = 2 };
	enum PLAYER { TERRY, KENSOU, KOEHAN};
	 
public:
	typedef struct tagHpBarDataBase
	{
		char** decide;

		RECT border1P,	border2P;
		RECT bar1P,		bar2P;
		RECT redBar1P,	redBar2P;

		int frame;
	}HPBAR, *PHPBAR;

	typedef struct tagHitBarDataBase
	{
		char **name;
		char scoreSave1P[10], scoreSave2P[10]; 

		int score1P,	score2P;
		int frame;

		bool mode1P,		mode2P;
	}HITBAR, *PHITBAR;

	typedef struct tagSkillBarDataBase
	{
		// 삼각형
		RECT triangleBorder1P,  triangleBorder2P;
		RECT blackBorder1P,		blackBorder2P;
		int triangleFrame;

		// 스킬바
		RECT border1P,		border2P;
		RECT stack1P,		stack2P;
		RECT * rect1P,		* rect2P;
		int frame;

		//필살기 개수
		int skillCount1P,		skillCount2P;

	}SKILLBAR, *PSKILLBAR;

	typedef struct tagKO
	{
		Image * koBG;
		int frame;
		bool mode;
	}KO, *PKO;

	typedef struct tagProfile
	{
		Image * terry1P, * terry2P;
		Image * kensou1P, * kensou2P;
		Image * koehan1P, * koehan2P;
		
		bool mode;
	}PROFILE, *PPROFILE;

	typedef char ** PLAYERNAME;

private:
	PHPBAR		hp;			// 체력
	PHITBAR		hitBar;		// 공격
	PSKILLBAR	skillBar;	// 스킬
	PKO			ko;			// KO 상황일 때 BG설정 변수
	PLAYERNAME  isName;		// 플레이어 이름설정 변수	
	PPROFILE	isProfile;

public:
	virtual HRESULT Init();	// 멤버변수 초기화, 메모리 할당
	virtual void Release();	// 메모리 해제
	virtual void Update();	// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);

	PHPBAR		GetHpInf();
	PHITBAR		GetHitBarInf();
	PSKILLBAR	GetSkillBarInf();
	PKO			GetKoInf();
	PLAYERNAME  GetPlayerNameInf();
	PPROFILE	GetProfileInf();

	UI();
	~UI();
};

