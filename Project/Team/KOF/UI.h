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
		// �ﰢ��
		RECT triangleBorder1P,  triangleBorder2P;
		RECT blackBorder1P,		blackBorder2P;
		int triangleFrame;

		// ��ų��
		RECT border1P,		border2P;
		RECT stack1P,		stack2P;
		RECT * rect1P,		* rect2P;
		int frame;

		//�ʻ�� ����
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
	PHPBAR		hp;			// ü��
	PHITBAR		hitBar;		// ����
	PSKILLBAR	skillBar;	// ��ų
	PKO			ko;			// KO ��Ȳ�� �� BG���� ����
	PLAYERNAME  isName;		// �÷��̾� �̸����� ����	
	PPROFILE	isProfile;

public:
	virtual HRESULT Init();	// ������� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();	// �޸� ����
	virtual void Update();	// ������ ���� ���� ���� ���� (������ ����)
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

