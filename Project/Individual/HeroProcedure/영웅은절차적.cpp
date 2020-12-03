#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

#define NAMESIZE 30					//이름 사이즈
#define LEVELNAMESIZE 10			//이름 사이즈
#define typeContents 60				//물건 설명크기
#define YPOS_QUARTER 4				//y의 for문을 총 1/4 분기씩 돌리기 위해 존재
#define MAPTYPE_MIX 3				//맵 Type을 섞기 위한 용도
#define MONSTER_OBJECT_NUMBER 13    // <- 기존 몬스터객체 배열 수 조절
#define MONSTER_NAME_NUMBER 15	    // <- 몬스터 이름 배열 수 조절
#define ORIGINAL_MONSTER_NUMBER	5   // <- 기존 몬스터 출력 수 조절
#define MONSTER_PROBABILITY 100		//확률 적용할 때 쓰임
#define ROCK_PAPER_SCISSORS 3		//가위 바위 보에 쓰임
#define POTION_TYPE 5				// 포션 타입
#define POTION_POSSESSION 10		// 플레이어가 소유가능한 포션개수
#define STORE_EXIT 5

enum MENU { NONE, START, END, MAKER };

enum MONSTER_LEVEL { MONSTER_NONE, EASY, NORMAL, HARD, VERYHARD };

enum TYPE { HYBRID, LAND, FOREST, MARSH };

enum PROBABILITY { PROBABILITY_FLASE, PROBABILITY_TRUE };

enum RPS { NONE_RPS = -1, SCISSORS = 1, ROCK, PAPER };

enum { BATTLE = 1, ESCAPE = 2 };

struct TILE
{
	int xPos, yPos;
	int _Type;
};

struct POTION
{
	char _Name[NAMESIZE];				//포션이름
	char _Type[typeContents];			//포션설명
	int purchasePrice, sellingPrice;	//구매가격, 판매가격
	int _Effect;						//효과
	bool _Use;							//사용여부
};

struct PLAYER
{
	char iName[NAMESIZE];
	string levelName;	// <- 난이도에 따른 실시간 난이도 이름표기
	int imaxHP, iHP;
	int imaxExp, iExp;
	int _Money, iLevel;
	int yPos, xPos;	// <- 플레이어 실시간 위치 좌표
	int srpWeapon, beforeWeapon; // <- 가위 바위 보 무기를 뜻함.
	bool _Possession, fightMode; // <- 소지품 소유 여부 & 싸움모드
	POTION _Potion[POTION_POSSESSION];	// <- 플레이어가 소지한 포션류
	int catchMonster, catchWin; // <- 난이도에 따라 잡아야 될 몬스터 조건변수들
	int possisionNum;
};

struct MONSTER
{
	string _Name[MONSTER_NAME_NUMBER];
	TYPE _Type;
	int _Level;
	int maxHP, _HP;
	int giveMoney, giveExp;
};

int errorCheck();
int gameMenu();
void gameIntro();
void MaptypeExplain(int _Maptype);
void MapAdjust(bool *levelLow, bool *levelNormal, bool *levelHigh, bool *levelVeryhigh, int * mapX, int * mapY, PLAYER * pPlayer);
void setMap(const int mapXpos, const int mapYpos, TILE *** mapInf);
void setStore(TILE *** storemapInf);
void drawMap(const int mapXpos, const int mapYpos, int* playerXpos, int* playerYpos, TILE *** _Map);
void drawStore(int* playerXpos, int* playerYpos, TILE *** storemapInf);
void rpsSystem(char keyInput, const int mapXpos, const int mapYpos, bool *levelLow, bool * levelNormal, bool * levelHigh, bool * levelVeryhigh, int* playerXpos, int* playerYpos,
	PLAYER * pPlayer, MONSTER * pMonster, TILE *** _Map);
void playerStats(PLAYER * pPlayer);
void moveFunction(char iInput, const int mapXpos, const int mapYpos, int * playerXpos, int * playerYpos, bool * paccessStore, bool * piQuit, TILE *** storemapInf, POTION * pPotion, PLAYER * pPlayer);
void playerReset(PLAYER * pPlayer);
void monsterDatabase(MONSTER * pMonster);
void PotionDatabase(POTION * pPotion);
void levelSystem(PLAYER * pPlayer, MONSTER * pMonster);
void deleteMap(const int mapXpos, const int mapYpos, TILE *** _Map, TILE *** _Store);

int main()
{
	srand(time(NULL));

	PLAYER mPlayer;								playerReset(&mPlayer); // 플레이어 변수선언 및 플레이어 초기설정
	MONSTER mMonster[MONSTER_OBJECT_NUMBER];	monsterDatabase(mMonster); // 몬스터 변수선언 및 몬스터 데이터설정
	POTION mPotion[POTION_TYPE];				PotionDatabase(mPotion); //포션 변수선언 및 포션 데이터설정

	//초기 입력변수
	int iInput;		iInput = gameMenu();

	while (true)
	{
		system("cls");

		if (iInput == START)
			break;

		else if (iInput == END)
			return 0;

		else if (iInput == MAKER)
		{
			cout << "게임 제작자: 남궁혁" << endl;
			system("pause");

			iInput = gameMenu();
		}
	}

	gameIntro();

	system("cls");

	cout << "=============================================" << endl;
	cout << "	플레이어의 이름을 입력하세요:" << endl;
	cout << "=============================================" << endl;

	cout << "입력:";  cin >> mPlayer.iName;

	cout << endl;

	int mapX, mapY; //맵 크기 지정 변수
	bool levelLow = false, levelNormal = false, levelHigh = false, levelVeryhigh = false; //난이도에 따라 등장 몬스터 수준이 달라진다.

	MapAdjust(&levelLow, &levelNormal, &levelHigh, &levelVeryhigh, &mapX, &mapY, &mPlayer);

	system("pause");

	const int mapXpos = mapX, mapYpos = mapY;	//맵 사이즈 지정

	mPlayer.yPos = 0, mPlayer.xPos = 0;	//플레이어 위치 고정

	TILE ** _Map;	setMap(mapXpos, mapYpos, &_Map);	// <- 사냥터 맵 설정
	TILE **_Store;	setStore(&_Store);					// <- 상점 맵 설정

	bool accessStore = false;		bool setHunt = true; // <- 상점과 사냥터 bool 값
	bool iQuit = false; // <- 종료 bool 값

	while (true)
	{
		system("cls");

		drawMap(mapXpos, mapYpos, &mPlayer.xPos, &mPlayer.yPos, &_Map);
		playerStats(&mPlayer);

		if (mPlayer.iExp >= mPlayer.imaxExp)
		{
			cout << "오오.. ! 레벨업" << endl;

			system("pause");

			levelSystem(&mPlayer, mMonster);
		}

		char keyInput = _getch(); // 키 입력 변수 및 getch 셋팅

		moveFunction(keyInput, mapXpos, mapYpos, &mPlayer.xPos, &mPlayer.yPos, &accessStore, &iQuit, &_Store, mPotion, &mPlayer);

		if (accessStore == true)
		{
			mPlayer.xPos = 1;	mPlayer.yPos = 4;

			while (accessStore == true)
			{
				drawStore(&mPlayer.xPos, &mPlayer.yPos, &_Store);
				playerStats(&mPlayer);

				if (mPlayer.yPos == 4 && mPlayer.xPos == 5)
				{
					cout << endl << "안녕하세요 용사님~ 경일 잡화점에 오신 것을 환영합니다." << endl;
					cout << "▶ 말걸기 『f』" << endl;
				}

				else if (mPlayer.yPos == 4 && mPlayer.xPos == 0 || mPlayer.yPos == 5 && mPlayer.xPos == 0)
				{
					cout << endl << "용사님 나가실겁니까??? ,....." << endl;
					cout << "▶ 나가기 『t』" << endl;
				}

				char keyInput2 = _getch();
				moveFunction(keyInput2, mapXpos, mapYpos, &mPlayer.xPos, &mPlayer.yPos, &accessStore, &iQuit, &_Store, mPotion, &mPlayer);

				if (iQuit == true)
				{
					cout << "게임을 종료합니다. ~~" << endl;

					return 0;
				}
			}
		}

		rpsSystem(keyInput, mapXpos, mapYpos, &levelLow, &levelNormal, &levelHigh, &levelVeryhigh, &mPlayer.xPos, &mPlayer.yPos,
			&mPlayer, mMonster, &_Map);

		if (iQuit == true)
		{
			cout << "게임을 종료합니다. ~~" << endl;

			return 0;
		}

		if (mPlayer.catchMonster == mPlayer.catchWin)
		{
			cout << "게임 승리! 축하드립니다." << endl;

			deleteMap(mapXpos, mapYpos, &_Map, &_Store);

			break;
		}

		if (mPlayer.iHP <= 0)
		{
			cout << "게임오버" << endl;

			deleteMap(mapXpos, mapYpos, &_Map, &_Store);

			break;
		}
	}

	return 0;
}

int errorCheck()
{
	int iInput; cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');

		return errorCheck();
	}

	return iInput;
}

int gameMenu()
{
	system("cls");

	cout << "=============================================" << endl;
	cout << "=============================================" << endl;
	cout << "============『 영웅은 절차적 2 』============" << endl;
	cout << "=============================================" << endl;
	cout << "=============================================" << endl << endl;
	cout << "1.게임시작" << endl;
	cout << "2.게임종료" << endl;
	cout << "3.제작자" << endl;
	cout << "입력:";

	int iInput = errorCheck();

	if (iInput <= NONE || iInput > MAKER)
	{
		cout << "입력 값의 범위를 넘어섰습니다." << endl;
		system("pause");

		return gameMenu();
	}

	return iInput;
}

void gameIntro()
{
	system("cls");

	//인트로
	cout << endl;
	cout << "=============================================" << endl;
	cout << "「영웅님 어서 오세요. " << endl;
	cout << "당신이 바로 이 게임의 주인공입니다." << endl;
	cout << "숲, 늪, 땅 필드에 있는 몬스터와 싸워 이겨서 당신의 레벨을 올려보세요! 」" << endl;
	cout << "=============================================" << endl;

	system("pause");
}

void MaptypeExplain(int _Maptype)
{
	if (_Maptype == HYBRID)
	{
		cout << "◎◎◎◎ 몬스터 타입 「잡종」 ◎◎◎◎ ~~ " << endl;
	}

	else if (_Maptype == LAND)
	{
		cout << "◎◎◎◎ 몬스터 타입 「땅」 ◎◎◎◎ ~~ " << endl;
	}

	else if (_Maptype == FOREST)
	{
		cout << "◎◎◎◎ 몬스터 타입 「숲」 ◎◎◎◎ ~~ " << endl;
	}

	else if (_Maptype == MARSH)
	{
		cout << "◎◎◎◎ 몬스터 타입 「늪」 ◎◎◎◎ ~~ " << endl;
	}
}

void MapAdjust(bool *levelLow, bool *levelNormal, bool *levelHigh, bool *levelVeryhigh, int * mapX, int * mapY, PLAYER * pPlayer)
{
	//맵 크기에 따라 난이도 조절 시스템
	while (true)
	{
		system("cls");

		cout << "MAP x, y 좌표 값을 4의 배수 단위로 설정하시오." << endl;
		cout << "x값 입력:"; cin >> (*mapX);
		cout << "y값 입력:"; cin >> (*mapY);

		cout << endl;

		if ((*mapX) % 4 != 0 || (*mapY) % 4 != 0)
		{
			cout << endl;

			cout << "4의 배수가 아닙니다. 다시 입력하십시오." << endl;

			system("pause");
			continue;
		}

		if ((*mapX) < 17 && (*mapY) < 17)
		{
			cout << (*mapY) << " * " << (*mapX) << " 맵 셋팅완료" << endl;
			cout << "쉬움 모드입니다." << endl;

			(*levelLow) = true;		pPlayer->levelName = "쉬움";
			pPlayer->catchWin = 5;
		}

		else if ((*mapX) < 25 && (*mapY) < 25)
		{
			cout << (*mapY) << " * " << (*mapX) << " 맵 셋팅완료" << endl;
			cout << "보통 모드입니다." << endl;

			(*levelNormal) = true;		pPlayer->levelName = "보통";
			pPlayer->catchWin = 15;
		}

		else if ((*mapX) < 33 && (*mapY) < 33)
		{
			cout << (*mapY) << " * " << (*mapX) << " 맵 셋팅완료" << endl;
			cout << "어려움 모드입니다." << endl;

			(*levelHigh) = true;		pPlayer->levelName = "어려움";
			pPlayer->catchWin = 20;
		}

		else if ((*mapX) < 41 && (*mapY) < 41)
		{
			cout << (*mapY) << " * " << (*mapX) << " 맵 셋팅완료" << endl;
			cout << "매우 어려움 모드입니다." << endl;

			(*levelVeryhigh) = true;	pPlayer->levelName = "매우 어려움";
			pPlayer->catchWin = 30;
		}

		else
		{
			cout << "권장하지 않는 좌표 값들입니다. 다시 설정하십시오." << endl;

			system("pause");
			continue;
		}

		break;
	}
}

void setMap(const int mapXpos, const int mapYpos, TILE *** mapInf)
{
	(*mapInf) = new TILE*[mapYpos];

	int i, j, k;
	for (i = 0; i < mapYpos; i++)
		(*mapInf)[i] = new TILE[mapXpos];

	// Map i, j 값 설정
	for (i = 0; i < mapYpos; i++)
	{
		for (j = 0; j < mapXpos; j++)
		{
			(*mapInf)[i][j].yPos = i;
			(*mapInf)[i][j].xPos = j;
		}
	}

	int xIncrease, yIncrease;	// x값 y값 분기역할
	int iPower = YPOS_QUARTER; // y의 for문을 총 1/4 분기씩 돌리기 위해 필요한 변수
	int jPower = 0, kPower = 0;// j, k를 돌리기 위한 구동용 변수

	//x와 y값을 i로 나누었을 때 몫이 4가 나오게 하기위한 for문
	for (float i = 1; i < 100; i++)
	{
		if ((mapYpos / i) == 4.0)
		{
			yIncrease = i;

			for (i = 1; i < 100; i++)
			{

				if (mapXpos / i == 4.0)
				{
					xIncrease = i;
					break;
				}
			}

			break;
		}
	}

	int mixType1, mixType2, mixType3, mixType4;	//맵 타입

	// Map Tile 숲 늪 땅 3개 셋팅
	for (i = 0; i < iPower; i++)
	{
		// + 1의 의미는 HYBRID의 값을 맵에 주지 않기 위해서다
		mixType1 = rand() % MAPTYPE_MIX + 1;
		mixType2 = rand() % MAPTYPE_MIX + 1;
		mixType3 = rand() % MAPTYPE_MIX + 1;
		mixType4 = rand() % MAPTYPE_MIX + 1;

		for (j = jPower; j < (jPower + yIncrease); j++)
		{
			kPower = 0;

			for (k = 0; k < xIncrease; k++)
				(*mapInf)[j][k]._Type = mixType1;

			kPower += xIncrease;

			for (k = kPower; k < (xIncrease + kPower); k++)
				(*mapInf)[j][k]._Type = mixType2;

			kPower += xIncrease;

			for (k = kPower; k < (xIncrease + kPower); k++)
				(*mapInf)[j][k]._Type = mixType3;

			kPower += xIncrease;

			for (k = kPower; k < (xIncrease + kPower); k++)
				(*mapInf)[j][k]._Type = mixType4;
		}

		jPower += yIncrease;
	}
}

void setStore(TILE *** storemapInf)
{
	(*storemapInf) = new TILE*[10];

	int i, j, k;
	for (i = 0; i < 10; i++)
		(*storemapInf)[i] = new TILE[10];

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			(*storemapInf)[i][j]._Type = 0;
			(*storemapInf)[i][j].xPos = j;
			(*storemapInf)[i][j].yPos = i;
		}
	}

	for (i = 3; i < 7; i++)
		(*storemapInf)[i][6]._Type = 1;

	(*storemapInf)[3][7]._Type = 1;
	(*storemapInf)[6][7]._Type = 1;

	(*storemapInf)[4][7]._Type = 3;

	for (i = 0; i < 1; i++)
	{
		for (j = 1; j < 4; j++)
			(*storemapInf)[j][i]._Type = 2;

		for (j = 0; j < 10; j++)
			(*storemapInf)[i][j]._Type = 2;

		for (k = 0; k < j; k++)
			(*storemapInf)[k][j - 1]._Type = 2;

		for (j = j - 1; j >= i; j--)
			(*storemapInf)[k - 1][j]._Type = 2;

		for (j = 8; j > 5; j--)
			(*storemapInf)[j][i]._Type = 2;
	}
}

void drawMap(const int mapXpos, const int mapYpos, int* playerXpos, int* playerYpos, TILE *** _Map)
{
	for (int i = 0; i < mapYpos; i++)
	{
		for (int j = 0; j < mapXpos; j++)
		{
			if (i == (*playerYpos) && j == (*playerXpos))
				cout << "♥";

			else if ((*_Map)[i][j]._Type == LAND)
				cout << "〓";

			else if ((*_Map)[i][j]._Type == FOREST)
				cout << "＃";

			else if ((*_Map)[i][j]._Type == MARSH)
				cout << "※";
		}

		cout << endl;
	}

}

void drawStore(int* playerXpos, int* playerYpos, TILE *** storemapInf)
{
	system("cls");

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i == (*playerYpos) && j == (*playerXpos))
				cout << "♥";

			else if ((*storemapInf)[i][j]._Type == 0)
				cout << "○";

			else if ((*storemapInf)[i][j]._Type == 1)
				cout << "■";			//데스크

			else if ((*storemapInf)[i][j]._Type == 2)
				cout << "♤";			//조형물

			else if ((*storemapInf)[i][j]._Type == 3)
				cout << "＆";			//NPC
		}

		cout << endl;
	}

}

void rpsSystem(char keyInput, const int mapXpos, const int mapYpos, bool *levelLow, bool * levelNormal, bool * levelHigh, bool * levelVeryhigh, int* playerXpos, int* playerYpos,
	PLAYER * pPlayer, MONSTER * pMonster, TILE *** _Map)
{
	int meetSeventy = 0;
	int meetFifty = 0;
	int meetThirty = 0;
	int meetTenth = 0;

	// w a s d 키 외에 이동 키가 들어갈경우 rand 함수가 작동하지 않는다.
	// 이렇게 해준 이유는 while문에서 다른 키가 멋대로 입력되어 들어갈 경우
	// Rand 값이 들어가서 플레이어가 움직이지 않았음에도 몬스터를 만나게 된다.
	if (keyInput == 'w' || keyInput == 'a' || keyInput == 's' || keyInput == 'd')
	{
		//몬스터 만날 확률 계산
		meetSeventy = rand() % MONSTER_PROBABILITY < 70; // <- 70퍼센트를 가리킴
		meetFifty = rand() % MONSTER_PROBABILITY < 50; // <- 50퍼센트를 가리킴
		meetThirty = rand() % MONSTER_PROBABILITY < 30; // <- 30퍼센트를 가리킴
		meetTenth = rand() % MONSTER_PROBABILITY < 10; // <- 10퍼센트를 가리킴
	}

	int monsterNamemix = rand() % ORIGINAL_MONSTER_NUMBER; // <- 기존 몬스터 이름을 랜덤으로 출력해 주는 변수
	int new_monsterLow, new_monsterNormal, new_monsterHigh, new_monsterVeryhigh; // <- 난이도에 따라 신규 몬스터 개체 수 조정 변수

	MONSTER monsterSubstitute; // <- 몬스터 데이터를 임시적으로 받아 처리하는 변수
	int numberSubstitute; // <- 몬스터의 이름을 랜덤으로 선택하게 해주는 변수를 임시적으로 받아 처리하는 변수

	int escapeChoice = -1; // <- 플레이어가 도망갈 수 있게 해주는 변수

	if ((*levelLow))
	{
		new_monsterLow = rand() % 4; //난이도에 따라 몬스터 수 랜덤결정

		//플레이어가 땅 위치에 있을 때 ? 확률로 몬스터를 만남
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[8]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[8]._Type);
			cout << "앗!, " << pMonster[8]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[8];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 숲 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[0]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[0]._Type);
			cout << "앗!, " << pMonster[0]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[0];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 늪 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[4]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[4]._Type);
			cout << "앗!, " << pMonster[4]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[4];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		else if (((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH) &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[12]._Type);
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterLow;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.승부하기 !" << endl;
			cout << "2.도망가기 ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelNormal))
	{
		new_monsterNormal = rand() % 8; //난이도에 따라 몬스터 수 랜덤결정

		//플레이어가 땅 위치에 있을 때 ? 확률로 몬스터를 만남
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[9]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[9]._Type);
			cout << "앗!, " << pMonster[9]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[9];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 숲 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[1]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[1]._Type);
			cout << "앗!, " << pMonster[1]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[1];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 늪 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[5]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[5]._Type);
			cout << "앗!, " << pMonster[5]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[5];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		else if (((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH) &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[12]._Type);
			cout << "앗!, " << pMonster[12]._Name[new_monsterNormal] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterNormal;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.승부하기 !" << endl;
			cout << "2.도망가기 ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelHigh))
	{
		new_monsterHigh = rand() % 12; //난이도에 따라 몬스터 수 랜덤결정

		//플레이어가 땅 위치에 있을 때 ? 확률로 몬스터를 만남
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[10]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[10]._Type);
			cout << "앗!, " << pMonster[10]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[10];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 숲 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[2]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[2]._Type);
			cout << "앗!, " << pMonster[2]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[2];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 늪 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[6]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[6]._Type);
			cout << "앗!, " << pMonster[6]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[6];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		else if (((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH) &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[12]._Type);
			cout << "앗!, " << pMonster[12]._Name[new_monsterHigh] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterHigh;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.승부하기 !" << endl;
			cout << "2.도망가기 ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelVeryhigh))
	{
		new_monsterVeryhigh = rand() % 15; //난이도에 따라 몬스터 수 랜덤결정

		//플레이어가 땅 위치에 있을 때 ? 확률로 몬스터를 만남
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[11]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[11]._Type);
			cout << "앗!, " << pMonster[11]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[11];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 숲 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[3]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[3]._Type);
			cout << "앗!, " << pMonster[3]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[3];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//플레이어가 늪 위치에 있을 때 ? 확률로 몬스터를 만남
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[7]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[7]._Type);
			cout << "앗!, " << pMonster[7]._Name[monsterNamemix] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[7];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		else if (((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST ||
			(*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH) &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[12]._Type);
			cout << "앗!, " << pMonster[12]._Name[new_monsterVeryhigh] << " 이(가) 나타났다." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterVeryhigh;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.승부하기 !" << endl;
			cout << "2.도망가기 ..." << endl;

			cin >> escapeChoice;
		}
	}

	if (escapeChoice == ESCAPE)
		return;

	escapeChoice = -1;

	//몬스터와 대결할 때
	while (pPlayer->fightMode == true)
	{
		system("cls");

		drawMap(mapXpos, mapYpos, &pPlayer->xPos, &pPlayer->yPos, _Map);

		//플레이어 상태
		playerStats(pPlayer);

		//마주친 몬스터 상태
		cout << "몬스터 이름:" << monsterSubstitute._Name[numberSubstitute];
		cout << "		레벨:" << monsterSubstitute._Level << endl;
		cout << "HP:" << monsterSubstitute._HP << " / " << monsterSubstitute.maxHP;
		cout << "		타입:";

		if (monsterSubstitute._Type == HYBRID)
			cout << "잡종" << endl;

		else if (monsterSubstitute._Type == LAND)
			cout << "땅" << endl;

		else if (monsterSubstitute._Type == FOREST)
			cout << "숲" << endl;

		else if (monsterSubstitute._Type == MARSH)
			cout << "늪" << endl;

		int srpmonsterWeapon = rand() % ROCK_PAPER_SCISSORS + 1; // <- 몬스터 가위 바위 보 무기를 뜻함.

		cout << "1.가위	2.바위 3. 보" << endl;
		cin >> pPlayer->srpWeapon;		pPlayer->beforeWeapon = pPlayer->srpWeapon;	// <- 선택한 무기 기억 용도 변수

		//플레이어가 바위를 선택할 때
		if (pPlayer->srpWeapon == ROCK)
		{
			//플레이어와 몬스터가 똑같은 무기를 선택할 때
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "무승부입니다. 상대방 무기 == " << "ROCK" << endl;

			//몬스터가 보를 선택하여 체력이 깎일 때
			else if (pPlayer->srpWeapon < srpmonsterWeapon)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "체력이 깍였습니다." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "상대방 무기 == PAPER " << endl;

				cout << "도망 가시겠습니까?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//몬스터가 가위를 선택하여 플레이어가 이겼을 때
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "에게 타격을 입혔습니다." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "이(가) " << monsterSubstitute._Name[numberSubstitute]
						<< "님(을) 이기셨습니다." << endl;
					cout << monsterSubstitute.giveMoney << "만큼의 돈을 획득하였습니다." << endl;
					cout << monsterSubstitute.giveExp << "만큼의 경험치를 획득하였습니다." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "상대방 무기 == SCISSORS" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		//플레이어가 보를 선택할 때
		else if (pPlayer->srpWeapon == PAPER)
		{
			//플레이어와 몬스터가 똑같은 무기를 선택할 때
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "무승부입니다. 상대방 무기 == " << "PAPER" << endl;

			//몬스터가 가위를 선택하여 체력이 깎일 때
			else if (pPlayer->srpWeapon > srpmonsterWeapon && srpmonsterWeapon == SCISSORS)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "체력이 깍였습니다." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "상대방 무기 == SCISSORS" << endl;

				cout << "도망 가시겠습니까?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//몬스터가 바위를 선택하여 플레이어가 이겼을 때
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "에게 타격을 입혔습니다." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "이(가) " << monsterSubstitute._Name[numberSubstitute]
						<< "님(을) 이기셨습니다." << endl;
					cout << monsterSubstitute.giveMoney << "만큼의 돈을 획득하였습니다." << endl;
					cout << monsterSubstitute.giveExp << "만큼의 경험치를 획득하였습니다." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "상대방 무기 == ROCK" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		//플레이어가 가위를 선택할 때
		else if (pPlayer->srpWeapon == SCISSORS)
		{
			//플레이어와 몬스터가 똑같은 무기를 선택할 때
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "무승부입니다. 상대방 무기 == " << "SCISSORS" << endl;

			//몬스터가 바위를 선택하여 체력이 깎일 때
			else if (pPlayer->srpWeapon < srpmonsterWeapon && srpmonsterWeapon == ROCK)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "체력이 깍였습니다." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "상대방 무기 == ROCK" << endl;

				cout << "도망 가시겠습니까?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//몬스터가 보를 선택하여 플레이어가 이겼을 때
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "에게 타격을 입혔습니다." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "이(가) " << monsterSubstitute._Name[numberSubstitute]
						<< "님(을) 이기셨습니다." << endl;
					cout << monsterSubstitute.giveMoney << "만큼의 돈을 획득하였습니다." << endl;
					cout << monsterSubstitute.giveExp << "만큼의 경험치를 획득하였습니다." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "상대방 무기 == PAPER" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		if (escapeChoice == 1)	//플레이어가 도망을 선택했을 때
		{
			pPlayer->fightMode = false;		return;
		}

		system("pause");
	}
}

void playerStats(PLAYER * pPlayer)
{
	cout << "이름:" << pPlayer->iName << "		레벨:" << pPlayer->iLevel << endl;
	cout << "HP:" << pPlayer->iHP << " / " << pPlayer->imaxHP
		<< "		난이도:" << pPlayer->levelName << endl;
	cout << "소지금:" << pPlayer->_Money << "		";
	cout << "경험치:" << pPlayer->iExp << " / " << pPlayer->imaxExp << endl;
	cout << "이전 무기:";

	if (pPlayer->beforeWeapon == NONE_RPS) cout << "NONE		";

	else if (pPlayer->beforeWeapon == SCISSORS) cout << "가위		";

	else if (pPlayer->beforeWeapon == ROCK) cout << "바위		";

	else cout << "바위		";

	cout << "소지품: ";
	if (pPlayer->_Possession)
	{
		for (int i = 0; i < pPlayer->possisionNum; i++)
		{
			cout << i + 1 << ". " << pPlayer->_Potion[i]._Name << "	";
		}
	}

	else				   cout << "NONE" << endl;

	cout << endl << "잡아야될 몬스터 수:" << pPlayer->catchMonster << " / " << pPlayer->catchWin << endl << endl;
	cout << "상점 키 〔 t 〕 || 〔 T 〕		물약 사용 키 〔 e 〕 || 〔 E 〕" << endl;

	cout << endl;
}

void moveFunction(char iInput, const int mapXpos, const int mapYpos, int * playerXpos, int * playerYpos, bool * paccessStore, bool * piQuit, TILE *** storemapInf, POTION * pPotion, PLAYER * pPlayer)
{
	int i, pSelect;

	switch (iInput)
	{
	case 'w':
	case 'W':

		if ((*paccessStore) == false && (*playerYpos) > 0)
			(*playerYpos)--;

		else if ((*paccessStore) == true && (*storemapInf)[(*playerYpos) - 1][(*playerXpos)]._Type != 2 &&
			(*storemapInf)[(*playerYpos) - 1][(*playerXpos)]._Type != 1)
			(*playerYpos)--;

		break;
	case 'a':
	case 'A':
		if ((*paccessStore) == false && (*playerXpos) > 0)
			(*playerXpos)--;

		else if ((*paccessStore) == true && (*playerXpos) > 0 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos) - 1]._Type != 2 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos) - 1]._Type != 1)
			(*playerXpos)--;

		break;
	case 's':
	case 'S':
		if ((*paccessStore) == false && (*playerYpos) < mapYpos - 1)
			(*playerYpos)++;

		else if ((*paccessStore) == true &&
			(*storemapInf)[(*playerYpos) + 1][(*playerXpos)]._Type != 2 &&
			(*storemapInf)[(*playerYpos) + 1][(*playerXpos)]._Type != 1)
			(*playerYpos)++;

		break;
	case 'd':
	case 'D':
		if ((*paccessStore) == false && (*playerXpos) < mapXpos - 1)
			(*playerXpos)++;

		else if ((*paccessStore) == true &&
			(*storemapInf)[(*playerYpos)][(*playerXpos) + 1]._Type != 2 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos) + 1]._Type != 1)
			(*playerXpos)++;

		break;

	case 'f':
	case 'F':
		if ((*storemapInf)[(*playerYpos)][(*playerXpos)].yPos == 4 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos)].xPos == 5)
		{

			while (true)
			{
				system("cls");

				cout << endl << "《 경일 잡화점 》" << endl << endl;

				for (i = 0; i < POTION_TYPE - 1; i++)
				{
					cout << i + 1 << ".	음식명: " << pPotion[i]._Name << endl;
					cout << "	설명: " << pPotion[i]._Type << endl;
					cout << "	구입가: " << pPotion[i].purchasePrice << endl;
					cout << "	재판매가: " << pPotion[i].sellingPrice << endl;
					cout << "	HP 회복력: " << pPotion[i]._Effect << endl << endl;
				}
				cout << POTION_TYPE << ". 나가기" << endl;

				cin >> pSelect;

				if (pSelect == STORE_EXIT)
					break;

				if (pPlayer->_Money >= pPotion[pSelect - 1].purchasePrice)
				{
					pPlayer->_Potion[pPlayer->possisionNum++] = pPotion[pSelect - 1];
					pPlayer->_Money -= pPotion[pSelect - 1].purchasePrice;

					pPlayer->_Possession = true;

					cout << "구매 성공~" << endl;
				}

				else
					cout << "돈이 부족합니다....." << endl;

				system("pause");
			}

		}

		break;

	case 'e':
	case 'E':

		if (pPlayer->_Possession == true)
		{
			if (pPlayer->iHP == pPlayer->imaxHP)
			{
				cout << "당신의 체력은 Full입니다." << endl;

				system("pause");
				break;
			}

			cout << "사용할 포션을 골라주세요.~~" << endl;

			cin >> pSelect;

			for (i = 0; i < pPlayer->possisionNum; i++)
			{
				if (pSelect == i + 1)
				{
					cout << "오오오오 " << pPlayer->_Potion[pSelect - 1]._Effect << "만큼 회복 되었습니다. !!" << endl;

					pPlayer->iHP += pPlayer->_Potion[pSelect - 1]._Effect;

					if (pPlayer->iHP > pPlayer->imaxHP)
						pPlayer->iHP = pPlayer->imaxHP;

					pPlayer->_Potion[pSelect - 1]._Use = true;

					if (pPlayer->_Potion[pSelect - 1]._Use == true)
					{
						pPlayer->_Potion[pSelect - 1]._Use = false;

						if (pSelect - 1 < pPlayer->possisionNum)
							pPlayer->_Potion[pSelect - 1] = pPlayer->_Potion[pSelect];

						pPlayer->possisionNum--;
					}

					system("pause");
				}
			}

		}

		else
		{
			cout << "가지고 있지 않습니다~..." << endl;

			system("pause");
			break;
		}

		break;

	case 't':
	case 'T':
		if ((*paccessStore) == true &&
			(*storemapInf)[(*playerYpos)][(*playerXpos)].yPos == 4 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos)].xPos == 0)
			(*paccessStore) = false;

		else if ((*paccessStore) == true &&
			(*storemapInf)[(*playerYpos)][(*playerXpos)].yPos == 5 &&
			(*storemapInf)[(*playerYpos)][(*playerXpos)].xPos == 0)
			(*paccessStore) = false;

		else if ((*paccessStore) == false)
			(*paccessStore) = true;

		break;

	case 'q':
	case 'Q':
		if (*piQuit == false)
			*piQuit = true;

		break;

	default:
		break;
	}
}

void playerReset(PLAYER * pPlayer)
{
	//플레이어 정보 초기화
	pPlayer->imaxHP = 10;			pPlayer->iHP = 10;
	pPlayer->_Money = 1500;			pPlayer->iLevel = 1;
	pPlayer->imaxExp = 10;			pPlayer->iExp = 0;
	pPlayer->yPos = -1;				pPlayer->xPos = -1;				// <- 위치가 정해져있지 않음.
	pPlayer->srpWeapon = -1;		pPlayer->beforeWeapon = -1;		// <- 무기를 선택하지 않았다.
	pPlayer->_Possession = false;	pPlayer->fightMode = false;		// <- 소지품 소유 / 싸움모드 여부
	pPlayer->catchMonster = 0;		pPlayer->catchWin = 0;
	pPlayer->possisionNum = 0;
}

void monsterDatabase(MONSTER * pMonster)
{
	//숲 포켓몬

//난이도 낮음 출현
	pMonster[0]._Name[0] = "이상해씨";		pMonster[0]._Name[1] = "캐터피";
	pMonster[0]._Name[2] = "뿔충이";			pMonster[0]._Name[3] = "구구";
	pMonster[0]._Name[4] = "모다피";
	pMonster[0]._Type = FOREST;				pMonster[0]._Level = 1;
	pMonster[0].maxHP = 1;					pMonster[0]._HP = 1;
	pMonster[0].giveExp = 10;				pMonster[0].giveMoney = 100;

	//난이도 보통 출현	
	pMonster[1]._Name[0] = "이상해풀";		pMonster[1]._Name[1] = "단데기";
	pMonster[1]._Name[2] = "딱충이";			pMonster[1]._Name[3] = "피죤";
	pMonster[1]._Name[4] = "우츠동";
	pMonster[1]._Type = FOREST;				pMonster[1]._Level = 5;
	pMonster[1].maxHP = 5;					pMonster[1]._HP = 5;
	pMonster[1].giveExp = 50;				pMonster[1].giveMoney = 200;

	//난이도 높음 출현
	pMonster[2]._Name[0] = "이상해꽃";		pMonster[2]._Name[1] = "버터플";
	pMonster[2]._Name[2] = "독침붕";			pMonster[2]._Name[3] = "피죤투";
	pMonster[2]._Name[4] = "우츠보트";
	pMonster[2]._Type = FOREST;				pMonster[2]._Level = 10;
	pMonster[2].maxHP = 10;					pMonster[2]._HP = 10;
	pMonster[2].giveExp = 100;				pMonster[2].giveMoney = 500;

	//난이도 매우높음 출현
	pMonster[3]._Name[0] = "메가이상해꽃";	pMonster[3]._Name[1] = "노장_버터플";
	pMonster[3]._Name[2] = "메가독침붕";		pMonster[3]._Name[3] = "메가피죤투";
	pMonster[3]._Name[4] = "노장_우츠보트";
	pMonster[3]._Type = FOREST;				pMonster[3]._Level = 15;
	pMonster[3].maxHP = 15;					pMonster[3]._HP = 15;
	pMonster[3].giveExp = 200;				pMonster[3].giveMoney = 750;

	//늪 포켓몬

	//난이도 낮음 출현
	pMonster[4]._Name[0] = "꼬부기";			pMonster[4]._Name[1] = "꼬렛";
	pMonster[4]._Name[2] = "아보";			pMonster[4]._Name[3] = "질퍽이";
	pMonster[4]._Name[4] = "콘팡";
	pMonster[4]._Type = MARSH;				pMonster[4]._Level = 1;
	pMonster[4].maxHP = 1;					pMonster[4]._HP = 1;
	pMonster[4].giveExp = 10;				pMonster[4].giveMoney = 100;

	//난이도 보통 출현
	pMonster[5]._Name[0] = "어니부기";		pMonster[5]._Name[1] = "레트라";
	pMonster[5]._Name[2] = "아보크";			pMonster[5]._Name[3] = "질뻐기";
	pMonster[5]._Name[4] = "도나리";
	pMonster[5]._Type = MARSH;				pMonster[5]._Level = 5;
	pMonster[5].maxHP = 5;					pMonster[5]._HP = 5;
	pMonster[5].giveExp = 50;				pMonster[5].giveMoney = 200;

	//난이도 높음 출현
	pMonster[6]._Name[0] = "거북왕";			pMonster[6]._Name[1] = "강한_레트라";
	pMonster[6]._Name[2] = "강한_아보크";	pMonster[6]._Name[3] = "강한_질뻐기";
	pMonster[6]._Name[4] = "강한_도나리";
	pMonster[6]._Type = MARSH;				pMonster[6]._Level = 10;
	pMonster[6].maxHP = 10;					pMonster[6]._HP = 10;
	pMonster[6].giveExp = 100;				pMonster[6].giveMoney = 500;

	//난이도 매우높음 출현
	pMonster[7]._Name[0] = "메가거북왕";		pMonster[7]._Name[1] = "노장_레트라";
	pMonster[7]._Name[2] = "노장_아보크";	pMonster[7]._Name[3] = "노장_질뻐기";
	pMonster[7]._Name[4] = "노장_도나리";
	pMonster[7]._Type = MARSH;				pMonster[7]._Level = 15;
	pMonster[7].maxHP = 15;					pMonster[7]._HP = 15;
	pMonster[7].giveExp = 200;				pMonster[7].giveMoney = 750;

	//땅 포켓몬

	//난이도 낮음 출현
	pMonster[8]._Name[0] = "파이리";			pMonster[8]._Name[1] = "피츄";
	pMonster[8]._Name[2] = "꼬마돌";			pMonster[8]._Name[3] = "시라소몬";
	pMonster[8]._Name[4] = "캐이시";
	pMonster[8]._Type = LAND;				pMonster[8]._Level = 1;
	pMonster[8].maxHP = 1;					pMonster[8]._HP = 1;
	pMonster[8].giveExp = 10;				pMonster[8].giveMoney = 100;

	//난이도 보통 출현						 
	pMonster[9]._Name[0] = "리자드";			pMonster[9]._Name[1] = "피카츄";
	pMonster[9]._Name[2] = "데구리";			pMonster[9]._Name[3] = "홍수몬";
	pMonster[9]._Name[4] = "윤겔라";
	pMonster[9]._Type = LAND;				pMonster[9]._Level = 5;
	pMonster[9].maxHP = 5;					pMonster[9]._HP = 5;
	pMonster[9].giveExp = 50;				pMonster[9].giveMoney = 200;

	//난이도 높음 출현						 
	pMonster[10]._Name[0] = "리자몽";		pMonster[10]._Name[1] = "라이츄";
	pMonster[10]._Name[2] = "딱구리";		pMonster[10]._Name[3] = "강한_홍수몬";
	pMonster[10]._Name[4] = "후딘";
	pMonster[10]._Type = LAND;				pMonster[10]._Level = 10;
	pMonster[10].maxHP = 10;				pMonster[10]._HP = 10;
	pMonster[10].giveExp = 100;				pMonster[10].giveMoney = 500;

	//난이도 매우높음 출현					 
	pMonster[11]._Name[0] = "메가리자몽";	pMonster[11]._Name[1] = "노장_라이츄";
	pMonster[11]._Name[2] = "노장_딱구리";	pMonster[11]._Name[3] = "노장_홍수몬";
	pMonster[11]._Name[4] = "노장_후딘";
	pMonster[11]._Type = LAND;				pMonster[11]._Level = 15;
	pMonster[11].maxHP = 15;				pMonster[11]._HP = 15;
	pMonster[11].giveExp = 200;				pMonster[11].giveMoney = 750;

	//잡 몬스터								 
	pMonster[12]._Name[0] = "삐삐";			pMonster[12]._Name[1] = "나옹";
	pMonster[12]._Name[2] = "디그다";		pMonster[12]._Name[3] = "페르시온";
	pMonster[12]._Name[4] = "망키";			pMonster[12]._Name[5] = "고라파덕";
	pMonster[12]._Name[6] = "가디";			pMonster[12]._Name[7] = "왕눈해";
	pMonster[12]._Name[8] = "쥬레곤";		pMonster[12]._Name[9] = "야돈";
	pMonster[12]._Name[10] = "크랩";			pMonster[12]._Name[11] = "롱스톤";
	pMonster[12]._Name[12] = "탕구리";		pMonster[12]._Name[13] = "나시";
	pMonster[12]._Name[14] = "마임맨";
	pMonster[12]._Type = HYBRID;			pMonster[12]._Level = 3;
	pMonster[12].maxHP = 3;					pMonster[12]._HP = 3;
	pMonster[12].giveExp = 30;				pMonster[12].giveMoney = 150;
}

void PotionDatabase(POTION * pPotion)
{
	strcpy_s(pPotion[0]._Name, strlen("김치찌개") + 1, "김치찌개");
	strcpy_s(pPotion[0]._Type, typeContents, "맵고 짜고 신~~ 든든한 한끼를 제공한다!");
	pPotion[0].purchasePrice = 150;
	pPotion[0].sellingPrice = 50;
	pPotion[0]._Effect = 2;
	pPotion[0]._Use = false;

	strcpy_s(pPotion[1]._Name, strlen("치즈돈까스") + 1, "치즈돈까스");
	strcpy_s(pPotion[1]._Type, typeContents, "모짜렐라~~까 들어간 부드러운 등심돈까스");
	pPotion[1].purchasePrice = 300;
	pPotion[1].sellingPrice = 200;
	pPotion[1]._Effect = 5;
	pPotion[1]._Use = false;

	strcpy_s(pPotion[2]._Name, strlen("네네치킨") + 1, "네네치킨");
	strcpy_s(pPotion[2]._Type, typeContents, "깨끗한 기름에서 튀긴 맛있는 후라이드");
	pPotion[2].purchasePrice = 450;
	pPotion[2].sellingPrice = 350;
	pPotion[2]._Effect = 7;
	pPotion[2]._Use = false;

	strcpy_s(pPotion[3]._Name, strlen("도미노피자") + 1, "도미노피자");
	strcpy_s(pPotion[3]._Type, typeContents, "역시 피자는 도미노지 ~~~!!");
	pPotion[3].purchasePrice = 700;
	pPotion[3].sellingPrice = 500;
	pPotion[3]._Effect = 9;
	pPotion[3]._Use = false;
}

void levelSystem(PLAYER * pPlayer, MONSTER * pMonster)
{
	//플레이어 능력치 상승
	pPlayer->iLevel++;
	pPlayer->imaxHP += 5;	pPlayer->iHP += 5;
	pPlayer->iExp = 0;		pPlayer->imaxExp += 50;

	// 몬스터 능력치 상승

	//난이도 낮음
	pMonster[0]._Level++;
	pMonster[0].maxHP++;					pMonster[0]._HP++;
	pMonster[0].giveExp += 10;				pMonster[0].giveMoney += 50;

	//난이도 보통 
	pMonster[1]._Level++;
	pMonster[1].maxHP++;					pMonster[1]._HP++;
	pMonster[1].giveExp += 20;				pMonster[1].giveMoney += 70;

	//난이도 높음 
	pMonster[2]._Level++;
	pMonster[2].maxHP++;					pMonster[2]._HP++;
	pMonster[2].giveExp += 30;				pMonster[2].giveMoney += 100;

	//난이도 매우높음
	pMonster[3]._Level++;
	pMonster[3].maxHP++;					pMonster[3]._HP++;
	pMonster[3].giveExp += 40;				pMonster[3].giveMoney += 150;

	//늪 포켓몬

	//난이도 낮음
	pMonster[4]._Level++;
	pMonster[4].maxHP++;					pMonster[4]._HP++;
	pMonster[4].giveExp += 10;				pMonster[4].giveMoney += 50;

	//난이도 보통 
	pMonster[5]._Level++;
	pMonster[5].maxHP++;					pMonster[5]._HP++;
	pMonster[5].giveExp += 20;				pMonster[5].giveMoney += 70;

	//난이도 높음 
	pMonster[6]._Level++;
	pMonster[6].maxHP++;					pMonster[6]._HP++;
	pMonster[6].giveExp += 30;				pMonster[6].giveMoney += 100;

	//난이도 매우높음
	pMonster[7]._Level++;
	pMonster[7].maxHP++;					pMonster[7]._HP++;
	pMonster[7].giveExp += 40;				pMonster[7].giveMoney += 150;

	//땅 포켓몬

	//난이도 낮음
	pMonster[8]._Level++;
	pMonster[8].maxHP++;					pMonster[8]._HP++;
	pMonster[8].giveExp += 10;				pMonster[8].giveMoney += 50;

	//난이도 보통 
	pMonster[9]._Level++;
	pMonster[9].maxHP++;					pMonster[9]._HP++;
	pMonster[9].giveExp += 20;				pMonster[9].giveMoney += 70;

	//난이도 높음 
	pMonster[10]._Level++;
	pMonster[10].maxHP++;					pMonster[10]._HP++;
	pMonster[10].giveExp += 30;				pMonster[10].giveMoney += 100;

	//난이도 매우높음
	pMonster[11]._Level++;
	pMonster[11].maxHP++;					pMonster[11]._HP++;
	pMonster[11].giveExp += 40;				pMonster[11].giveMoney += 150;

	//잡 몬스터
	pMonster[12]._Level++;
	pMonster[12].maxHP++;				pMonster[12]._HP++;
	pMonster[12].giveExp += 10;			pMonster[12].giveMoney += 30;
}

void deleteMap(const int mapXpos, const int mapYpos, TILE *** _Map, TILE *** _Store)
{
	for (int i = 0; i < mapYpos; i++)
		delete[](*_Map)[i];

	delete[](*_Map);

	for (int i = 0; i < 10; i++)
		delete[](*_Store)[i];

	delete[](*_Store);

}
