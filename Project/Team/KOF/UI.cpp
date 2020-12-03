#include "UI.h"
#include "Image.h"

HRESULT UI::Init()
{
	//������ �ʱ�ȭ
	{
		isProfile = new PROFILE();

		isProfile->terry1P = new Image();
		isProfile->terry1P->Init("Image/ŷ����UI/profile/terry.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->terry2P = new Image();
		isProfile->terry2P->Init("Image/ŷ����UI/profile/terry2.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->kensou1P = new Image();
		isProfile->kensou1P->Init("Image/ŷ����UI/profile/kensou.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->kensou2P = new Image();
		isProfile->kensou2P->Init("Image/ŷ����UI/profile/kensou2.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->koehan1P = new Image();
		isProfile->koehan1P->Init("Image/ŷ����UI/profile/Koehan.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->koehan2P = new Image();
		isProfile->koehan2P->Init("Image/ŷ����UI/profile/Koehan2.bmp",
			0, 0, 100, 75, 1, 1, true, RGB(255, 0, 255));

		isProfile->mode = false;
	}
	
	// hpBar �ʱ�ȭ
	{
		hp = new HPBAR();
		hp->decide = new char*[2];

		for (int i = 0; i < UI::WINORLOSE::END; i++)
			hp->decide[i] = new char[NAME_SIZE];

		strcpy_s(hp->decide[WIN], NAME_SIZE, "WIN");
		strcpy_s(hp->decide[LOSE], NAME_SIZE, "LOSE");

		// 1P hpBar
		hp->border1P = { 100, 50, 500, 90 };
		hp->bar1P = { 100, 50, 500, 90 };
		hp->redBar1P = { 100, 50, 500, 90 };

		// 2P hpBar
		hp->border2P = { 1000, 50, 1400, 90 };
		hp->bar2P = { 1000, 50, 1400, 90 };
		hp->redBar2P = { 1000, 50, 1400, 90 };

		hp->frame = 0;
	}

	// hitBar �ʱ�ȭ
	{
		hitBar = new HITBAR();
		hitBar->name = new char*[HITBAT_TYPE];
		for (int i = 0; i < HITBAT_TYPE; i++)
			hitBar->name[i] = new char[HITBAT_SIZE];

		strcpy_s(hitBar->name[RUSH], NAME_SIZE, "RUSH");	strcpy_s(hitBar->name[RUSH + 1], NAME_SIZE, "RUSH");
		strcpy_s(hitBar->name[HITS], NAME_SIZE, "HITS");	strcpy_s(hitBar->name[HITS + 1], NAME_SIZE, "HITS");

		for (int i = 0; i < 10; i++)
		{
			hitBar->scoreSave1P[i] = 0;
			hitBar->scoreSave2P[i] = 0;
		}

		hitBar->score1P = 0;		hitBar->score2P = 0;
		hitBar->mode1P = false;		hitBar->mode2P = false;

		hitBar->frame = 0;
	}

	// skillBar �ʱ�ȭ
	{
		skillBar = new SKILLBAR();

		// �ﰢ�� ������
		skillBar->triangleBorder1P = { 100, 370, 130, 400 };	skillBar->triangleBorder2P = { 1370, 370, 1400, 400 };
		skillBar->blackBorder1P = { 100, 370, 130, 400 };		skillBar->blackBorder2P = { 1370, 370, 1400, 400 };
		skillBar->triangleFrame = 0;

		// ��ų ������
		skillBar->border1P = { 130, 370, 300, 400 };			skillBar->border2P = { 1200, 370, 1370, 400 };
		skillBar->stack1P = { 130, 370, 130, 400 };				skillBar->stack2P = { 1370, 370, 1370, 400 };
		skillBar->rect1P = new RECT[SKILL_BOX];					skillBar->rect2P = new RECT[SKILL_BOX];

		for (int i = 0; i < 4; i++)
		{
			skillBar->rect1P[i] = { 300, 370, 300 + 25 * (i + 1), 400 };
			skillBar->rect2P[i] = { 1200 - 25 * (i + 1), 370, 1200, 400 };
		}

		skillBar->frame = 0;
		skillBar->skillCount1P = 0;			skillBar->skillCount2P = 0;
	}

	// KO���� �� ��׶���
	{
		ko = new KO();
		ko->koBG = new Image();
		ko->koBG->Init("Image/KORED.bmp", WIN_SIZE_X, WIN_SIZE_Y);

		ko->frame = 0;
		ko->mode = false;
	}

	// �÷��̾� �̸�����
	{
		isName = new char*[PLAYER_NUM];
		for (int i = 0; i < PLAYER_NUM; i++)
			isName[i] = new char[NAME_SIZE];

		strcpy_s(isName[0], NAME_SIZE, "Terry");		strcpy_s(isName[1], NAME_SIZE, "Kensou");
		strcpy_s(isName[2], NAME_SIZE, "Koehan");
	}

	return S_OK;
}

void UI::Release()	
{
	//// �÷��̾� �̸� ����
	//for (int i = 0; i < PLAYER_NUM; i++)
	//	delete[] isName[i];
	//delete[] isName;

	//// Ko ����
	//delete ko->koBG;
	//delete ko;

	//// skillBar ����
	//delete[] skillBar->rect1P, skillBar->rect2P;
	//delete skillBar;

	//// hitBar ����
	//for (int i = 0; i < HITBAT_TYPE; i++)
	//	delete[] hitBar->name[i];
	//delete[] hitBar->name;

	//// HP ����
	//for (int i = 0; i < UI::WINORLOSE::END; i++)
	//	delete[] hp->decide[i];
	//delete[] hp->decide;

	//// ������ ����
	//delete isProfile->terry1P, isProfile->terry2P;
	//delete isProfile->kensou1P, isProfile->kensou2P;
	//delete isProfile->koehan1P, isProfile->koehan2P;
	//delete isProfile;
}
void UI::Update() {}
void UI::Render(HDC hdc) {}

UI::PHPBAR UI::GetHpInf() { return hp; }
UI::PHITBAR UI::GetHitBarInf() {return hitBar;}
UI::PSKILLBAR UI::GetSkillBarInf(){return skillBar;}
UI::PKO UI::GetKoInf(){return ko;}
UI::PLAYERNAME UI::GetPlayerNameInf() { return isName; }
UI::PPROFILE UI::GetProfileInf() { return isProfile; }

UI::UI()	{}
UI::~UI()	{}
