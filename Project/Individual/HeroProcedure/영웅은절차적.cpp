#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

#define NAMESIZE 30					//�̸� ������
#define LEVELNAMESIZE 10			//�̸� ������
#define typeContents 60				//���� ����ũ��
#define YPOS_QUARTER 4				//y�� for���� �� 1/4 �б⾿ ������ ���� ����
#define MAPTYPE_MIX 3				//�� Type�� ���� ���� �뵵
#define MONSTER_OBJECT_NUMBER 13    // <- ���� ���Ͱ�ü �迭 �� ����
#define MONSTER_NAME_NUMBER 15	    // <- ���� �̸� �迭 �� ����
#define ORIGINAL_MONSTER_NUMBER	5   // <- ���� ���� ��� �� ����
#define MONSTER_PROBABILITY 100		//Ȯ�� ������ �� ����
#define ROCK_PAPER_SCISSORS 3		//���� ���� ���� ����
#define POTION_TYPE 5				// ���� Ÿ��
#define POTION_POSSESSION 10		// �÷��̾ ���������� ���ǰ���
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
	char _Name[NAMESIZE];				//�����̸�
	char _Type[typeContents];			//���Ǽ���
	int purchasePrice, sellingPrice;	//���Ű���, �ǸŰ���
	int _Effect;						//ȿ��
	bool _Use;							//��뿩��
};

struct PLAYER
{
	char iName[NAMESIZE];
	string levelName;	// <- ���̵��� ���� �ǽð� ���̵� �̸�ǥ��
	int imaxHP, iHP;
	int imaxExp, iExp;
	int _Money, iLevel;
	int yPos, xPos;	// <- �÷��̾� �ǽð� ��ġ ��ǥ
	int srpWeapon, beforeWeapon; // <- ���� ���� �� ���⸦ ����.
	bool _Possession, fightMode; // <- ����ǰ ���� ���� & �ο���
	POTION _Potion[POTION_POSSESSION];	// <- �÷��̾ ������ ���Ƿ�
	int catchMonster, catchWin; // <- ���̵��� ���� ��ƾ� �� ���� ���Ǻ�����
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

	PLAYER mPlayer;								playerReset(&mPlayer); // �÷��̾� �������� �� �÷��̾� �ʱ⼳��
	MONSTER mMonster[MONSTER_OBJECT_NUMBER];	monsterDatabase(mMonster); // ���� �������� �� ���� �����ͼ���
	POTION mPotion[POTION_TYPE];				PotionDatabase(mPotion); //���� �������� �� ���� �����ͼ���

	//�ʱ� �Էº���
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
			cout << "���� ������: ������" << endl;
			system("pause");

			iInput = gameMenu();
		}
	}

	gameIntro();

	system("cls");

	cout << "=============================================" << endl;
	cout << "	�÷��̾��� �̸��� �Է��ϼ���:" << endl;
	cout << "=============================================" << endl;

	cout << "�Է�:";  cin >> mPlayer.iName;

	cout << endl;

	int mapX, mapY; //�� ũ�� ���� ����
	bool levelLow = false, levelNormal = false, levelHigh = false, levelVeryhigh = false; //���̵��� ���� ���� ���� ������ �޶�����.

	MapAdjust(&levelLow, &levelNormal, &levelHigh, &levelVeryhigh, &mapX, &mapY, &mPlayer);

	system("pause");

	const int mapXpos = mapX, mapYpos = mapY;	//�� ������ ����

	mPlayer.yPos = 0, mPlayer.xPos = 0;	//�÷��̾� ��ġ ����

	TILE ** _Map;	setMap(mapXpos, mapYpos, &_Map);	// <- ����� �� ����
	TILE **_Store;	setStore(&_Store);					// <- ���� �� ����

	bool accessStore = false;		bool setHunt = true; // <- ������ ����� bool ��
	bool iQuit = false; // <- ���� bool ��

	while (true)
	{
		system("cls");

		drawMap(mapXpos, mapYpos, &mPlayer.xPos, &mPlayer.yPos, &_Map);
		playerStats(&mPlayer);

		if (mPlayer.iExp >= mPlayer.imaxExp)
		{
			cout << "����.. ! ������" << endl;

			system("pause");

			levelSystem(&mPlayer, mMonster);
		}

		char keyInput = _getch(); // Ű �Է� ���� �� getch ����

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
					cout << endl << "�ȳ��ϼ��� ����~ ���� ��ȭ���� ���� ���� ȯ���մϴ�." << endl;
					cout << "�� ���ɱ� ��f��" << endl;
				}

				else if (mPlayer.yPos == 4 && mPlayer.xPos == 0 || mPlayer.yPos == 5 && mPlayer.xPos == 0)
				{
					cout << endl << "���� �����ǰ̴ϱ�??? ,....." << endl;
					cout << "�� ������ ��t��" << endl;
				}

				char keyInput2 = _getch();
				moveFunction(keyInput2, mapXpos, mapYpos, &mPlayer.xPos, &mPlayer.yPos, &accessStore, &iQuit, &_Store, mPotion, &mPlayer);

				if (iQuit == true)
				{
					cout << "������ �����մϴ�. ~~" << endl;

					return 0;
				}
			}
		}

		rpsSystem(keyInput, mapXpos, mapYpos, &levelLow, &levelNormal, &levelHigh, &levelVeryhigh, &mPlayer.xPos, &mPlayer.yPos,
			&mPlayer, mMonster, &_Map);

		if (iQuit == true)
		{
			cout << "������ �����մϴ�. ~~" << endl;

			return 0;
		}

		if (mPlayer.catchMonster == mPlayer.catchWin)
		{
			cout << "���� �¸�! ���ϵ帳�ϴ�." << endl;

			deleteMap(mapXpos, mapYpos, &_Map, &_Store);

			break;
		}

		if (mPlayer.iHP <= 0)
		{
			cout << "���ӿ���" << endl;

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
	cout << "============�� ������ ������ 2 ��============" << endl;
	cout << "=============================================" << endl;
	cout << "=============================================" << endl << endl;
	cout << "1.���ӽ���" << endl;
	cout << "2.��������" << endl;
	cout << "3.������" << endl;
	cout << "�Է�:";

	int iInput = errorCheck();

	if (iInput <= NONE || iInput > MAKER)
	{
		cout << "�Է� ���� ������ �Ѿ���ϴ�." << endl;
		system("pause");

		return gameMenu();
	}

	return iInput;
}

void gameIntro()
{
	system("cls");

	//��Ʈ��
	cout << endl;
	cout << "=============================================" << endl;
	cout << "�������� � ������. " << endl;
	cout << "����� �ٷ� �� ������ ���ΰ��Դϴ�." << endl;
	cout << "��, ��, �� �ʵ忡 �ִ� ���Ϳ� �ο� �̰ܼ� ����� ������ �÷�������! ��" << endl;
	cout << "=============================================" << endl;

	system("pause");
}

void MaptypeExplain(int _Maptype)
{
	if (_Maptype == HYBRID)
	{
		cout << "�ݡݡݡ� ���� Ÿ�� �������� �ݡݡݡ� ~~ " << endl;
	}

	else if (_Maptype == LAND)
	{
		cout << "�ݡݡݡ� ���� Ÿ�� ������ �ݡݡݡ� ~~ " << endl;
	}

	else if (_Maptype == FOREST)
	{
		cout << "�ݡݡݡ� ���� Ÿ�� ������ �ݡݡݡ� ~~ " << endl;
	}

	else if (_Maptype == MARSH)
	{
		cout << "�ݡݡݡ� ���� Ÿ�� ���ˡ� �ݡݡݡ� ~~ " << endl;
	}
}

void MapAdjust(bool *levelLow, bool *levelNormal, bool *levelHigh, bool *levelVeryhigh, int * mapX, int * mapY, PLAYER * pPlayer)
{
	//�� ũ�⿡ ���� ���̵� ���� �ý���
	while (true)
	{
		system("cls");

		cout << "MAP x, y ��ǥ ���� 4�� ��� ������ �����Ͻÿ�." << endl;
		cout << "x�� �Է�:"; cin >> (*mapX);
		cout << "y�� �Է�:"; cin >> (*mapY);

		cout << endl;

		if ((*mapX) % 4 != 0 || (*mapY) % 4 != 0)
		{
			cout << endl;

			cout << "4�� ����� �ƴմϴ�. �ٽ� �Է��Ͻʽÿ�." << endl;

			system("pause");
			continue;
		}

		if ((*mapX) < 17 && (*mapY) < 17)
		{
			cout << (*mapY) << " * " << (*mapX) << " �� ���ÿϷ�" << endl;
			cout << "���� ����Դϴ�." << endl;

			(*levelLow) = true;		pPlayer->levelName = "����";
			pPlayer->catchWin = 5;
		}

		else if ((*mapX) < 25 && (*mapY) < 25)
		{
			cout << (*mapY) << " * " << (*mapX) << " �� ���ÿϷ�" << endl;
			cout << "���� ����Դϴ�." << endl;

			(*levelNormal) = true;		pPlayer->levelName = "����";
			pPlayer->catchWin = 15;
		}

		else if ((*mapX) < 33 && (*mapY) < 33)
		{
			cout << (*mapY) << " * " << (*mapX) << " �� ���ÿϷ�" << endl;
			cout << "����� ����Դϴ�." << endl;

			(*levelHigh) = true;		pPlayer->levelName = "�����";
			pPlayer->catchWin = 20;
		}

		else if ((*mapX) < 41 && (*mapY) < 41)
		{
			cout << (*mapY) << " * " << (*mapX) << " �� ���ÿϷ�" << endl;
			cout << "�ſ� ����� ����Դϴ�." << endl;

			(*levelVeryhigh) = true;	pPlayer->levelName = "�ſ� �����";
			pPlayer->catchWin = 30;
		}

		else
		{
			cout << "�������� �ʴ� ��ǥ �����Դϴ�. �ٽ� �����Ͻʽÿ�." << endl;

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

	// Map i, j �� ����
	for (i = 0; i < mapYpos; i++)
	{
		for (j = 0; j < mapXpos; j++)
		{
			(*mapInf)[i][j].yPos = i;
			(*mapInf)[i][j].xPos = j;
		}
	}

	int xIncrease, yIncrease;	// x�� y�� �б⿪��
	int iPower = YPOS_QUARTER; // y�� for���� �� 1/4 �б⾿ ������ ���� �ʿ��� ����
	int jPower = 0, kPower = 0;// j, k�� ������ ���� ������ ����

	//x�� y���� i�� �������� �� ���� 4�� ������ �ϱ����� for��
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

	int mixType1, mixType2, mixType3, mixType4;	//�� Ÿ��

	// Map Tile �� �� �� 3�� ����
	for (i = 0; i < iPower; i++)
	{
		// + 1�� �ǹ̴� HYBRID�� ���� �ʿ� ���� �ʱ� ���ؼ���
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
				cout << "��";

			else if ((*_Map)[i][j]._Type == LAND)
				cout << "��";

			else if ((*_Map)[i][j]._Type == FOREST)
				cout << "��";

			else if ((*_Map)[i][j]._Type == MARSH)
				cout << "��";
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
				cout << "��";

			else if ((*storemapInf)[i][j]._Type == 0)
				cout << "��";

			else if ((*storemapInf)[i][j]._Type == 1)
				cout << "��";			//����ũ

			else if ((*storemapInf)[i][j]._Type == 2)
				cout << "��";			//������

			else if ((*storemapInf)[i][j]._Type == 3)
				cout << "��";			//NPC
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

	// w a s d Ű �ܿ� �̵� Ű�� ����� rand �Լ��� �۵����� �ʴ´�.
	// �̷��� ���� ������ while������ �ٸ� Ű�� �ڴ�� �ԷµǾ� �� ���
	// Rand ���� ���� �÷��̾ �������� �ʾ������� ���͸� ������ �ȴ�.
	if (keyInput == 'w' || keyInput == 'a' || keyInput == 's' || keyInput == 'd')
	{
		//���� ���� Ȯ�� ���
		meetSeventy = rand() % MONSTER_PROBABILITY < 70; // <- 70�ۼ�Ʈ�� ����Ŵ
		meetFifty = rand() % MONSTER_PROBABILITY < 50; // <- 50�ۼ�Ʈ�� ����Ŵ
		meetThirty = rand() % MONSTER_PROBABILITY < 30; // <- 30�ۼ�Ʈ�� ����Ŵ
		meetTenth = rand() % MONSTER_PROBABILITY < 10; // <- 10�ۼ�Ʈ�� ����Ŵ
	}

	int monsterNamemix = rand() % ORIGINAL_MONSTER_NUMBER; // <- ���� ���� �̸��� �������� ����� �ִ� ����
	int new_monsterLow, new_monsterNormal, new_monsterHigh, new_monsterVeryhigh; // <- ���̵��� ���� �ű� ���� ��ü �� ���� ����

	MONSTER monsterSubstitute; // <- ���� �����͸� �ӽ������� �޾� ó���ϴ� ����
	int numberSubstitute; // <- ������ �̸��� �������� �����ϰ� ���ִ� ������ �ӽ������� �޾� ó���ϴ� ����

	int escapeChoice = -1; // <- �÷��̾ ������ �� �ְ� ���ִ� ����

	if ((*levelLow))
	{
		new_monsterLow = rand() % 4; //���̵��� ���� ���� �� ��������

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[8]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[8]._Type);
			cout << "��!, " << pMonster[8]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[8];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[0]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[0]._Type);
			cout << "��!, " << pMonster[0]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[0];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[4]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[4]._Type);
			cout << "��!, " << pMonster[4]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
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
			cout << "1.�º��ϱ� !" << endl;
			cout << "2.�������� ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelNormal))
	{
		new_monsterNormal = rand() % 8; //���̵��� ���� ���� �� ��������

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[9]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[9]._Type);
			cout << "��!, " << pMonster[9]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[9];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[1]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[1]._Type);
			cout << "��!, " << pMonster[1]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[1];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[5]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[5]._Type);
			cout << "��!, " << pMonster[5]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
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
			cout << "��!, " << pMonster[12]._Name[new_monsterNormal] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterNormal;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.�º��ϱ� !" << endl;
			cout << "2.�������� ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelHigh))
	{
		new_monsterHigh = rand() % 12; //���̵��� ���� ���� �� ��������

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[10]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[10]._Type);
			cout << "��!, " << pMonster[10]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[10];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[2]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[2]._Type);
			cout << "��!, " << pMonster[2]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[2];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[6]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[6]._Type);
			cout << "��!, " << pMonster[6]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
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
			cout << "��!, " << pMonster[12]._Name[new_monsterHigh] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterHigh;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.�º��ϱ� !" << endl;
			cout << "2.�������� ..." << endl;

			cin >> escapeChoice;
		}
	}

	else if ((*levelVeryhigh))
	{
		new_monsterVeryhigh = rand() % 15; //���̵��� ���� ���� �� ��������

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == LAND &&
			pMonster[11]._Type == LAND &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[11]._Type);
			cout << "��!, " << pMonster[11]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[11];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == FOREST &&
			pMonster[3]._Type == FOREST &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[3]._Type);
			cout << "��!, " << pMonster[3]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[3];
			numberSubstitute = monsterNamemix;

			pPlayer->fightMode = true;
		}

		//�÷��̾ �� ��ġ�� ���� �� ? Ȯ���� ���͸� ����
		else if ((*_Map)[pPlayer->yPos][pPlayer->xPos]._Type == MARSH &&
			pMonster[7]._Type == MARSH &&
			meetTenth == PROBABILITY_TRUE)
		{
			MaptypeExplain(pMonster[7]._Type);
			cout << "��!, " << pMonster[7]._Name[monsterNamemix] << " ��(��) ��Ÿ����." << endl;
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
			cout << "��!, " << pMonster[12]._Name[new_monsterVeryhigh] << " ��(��) ��Ÿ����." << endl;
			monsterSubstitute = pMonster[12];
			numberSubstitute = new_monsterVeryhigh;

			pPlayer->fightMode = true;
		}

		else
			pPlayer->fightMode = false;

		if (pPlayer->fightMode)
		{
			cout << "1.�º��ϱ� !" << endl;
			cout << "2.�������� ..." << endl;

			cin >> escapeChoice;
		}
	}

	if (escapeChoice == ESCAPE)
		return;

	escapeChoice = -1;

	//���Ϳ� ����� ��
	while (pPlayer->fightMode == true)
	{
		system("cls");

		drawMap(mapXpos, mapYpos, &pPlayer->xPos, &pPlayer->yPos, _Map);

		//�÷��̾� ����
		playerStats(pPlayer);

		//����ģ ���� ����
		cout << "���� �̸�:" << monsterSubstitute._Name[numberSubstitute];
		cout << "		����:" << monsterSubstitute._Level << endl;
		cout << "HP:" << monsterSubstitute._HP << " / " << monsterSubstitute.maxHP;
		cout << "		Ÿ��:";

		if (monsterSubstitute._Type == HYBRID)
			cout << "����" << endl;

		else if (monsterSubstitute._Type == LAND)
			cout << "��" << endl;

		else if (monsterSubstitute._Type == FOREST)
			cout << "��" << endl;

		else if (monsterSubstitute._Type == MARSH)
			cout << "��" << endl;

		int srpmonsterWeapon = rand() % ROCK_PAPER_SCISSORS + 1; // <- ���� ���� ���� �� ���⸦ ����.

		cout << "1.����	2.���� 3. ��" << endl;
		cin >> pPlayer->srpWeapon;		pPlayer->beforeWeapon = pPlayer->srpWeapon;	// <- ������ ���� ��� �뵵 ����

		//�÷��̾ ������ ������ ��
		if (pPlayer->srpWeapon == ROCK)
		{
			//�÷��̾�� ���Ͱ� �Ȱ��� ���⸦ ������ ��
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "���º��Դϴ�. ���� ���� == " << "ROCK" << endl;

			//���Ͱ� ���� �����Ͽ� ü���� ���� ��
			else if (pPlayer->srpWeapon < srpmonsterWeapon)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "ü���� �￴���ϴ�." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "���� ���� == PAPER " << endl;

				cout << "���� ���ðڽ��ϱ�?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//���Ͱ� ������ �����Ͽ� �÷��̾ �̰��� ��
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "���� Ÿ���� �������ϴ�." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "��(��) " << monsterSubstitute._Name[numberSubstitute]
						<< "��(��) �̱�̽��ϴ�." << endl;
					cout << monsterSubstitute.giveMoney << "��ŭ�� ���� ȹ���Ͽ����ϴ�." << endl;
					cout << monsterSubstitute.giveExp << "��ŭ�� ����ġ�� ȹ���Ͽ����ϴ�." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "���� ���� == SCISSORS" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		//�÷��̾ ���� ������ ��
		else if (pPlayer->srpWeapon == PAPER)
		{
			//�÷��̾�� ���Ͱ� �Ȱ��� ���⸦ ������ ��
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "���º��Դϴ�. ���� ���� == " << "PAPER" << endl;

			//���Ͱ� ������ �����Ͽ� ü���� ���� ��
			else if (pPlayer->srpWeapon > srpmonsterWeapon && srpmonsterWeapon == SCISSORS)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "ü���� �￴���ϴ�." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "���� ���� == SCISSORS" << endl;

				cout << "���� ���ðڽ��ϱ�?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//���Ͱ� ������ �����Ͽ� �÷��̾ �̰��� ��
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "���� Ÿ���� �������ϴ�." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "��(��) " << monsterSubstitute._Name[numberSubstitute]
						<< "��(��) �̱�̽��ϴ�." << endl;
					cout << monsterSubstitute.giveMoney << "��ŭ�� ���� ȹ���Ͽ����ϴ�." << endl;
					cout << monsterSubstitute.giveExp << "��ŭ�� ����ġ�� ȹ���Ͽ����ϴ�." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "���� ���� == ROCK" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		//�÷��̾ ������ ������ ��
		else if (pPlayer->srpWeapon == SCISSORS)
		{
			//�÷��̾�� ���Ͱ� �Ȱ��� ���⸦ ������ ��
			if (pPlayer->srpWeapon == srpmonsterWeapon)
				cout << "���º��Դϴ�. ���� ���� == " << "SCISSORS" << endl;

			//���Ͱ� ������ �����Ͽ� ü���� ���� ��
			else if (pPlayer->srpWeapon < srpmonsterWeapon && srpmonsterWeapon == ROCK)
			{
				pPlayer->iHP -= monsterSubstitute._HP;

				cout << "ü���� �￴���ϴ�." << endl;

				if (pPlayer->iHP <= 0)
					break;

				cout << "���� ���� == ROCK" << endl;

				cout << "���� ���ðڽ��ϱ�?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;

				cin >> escapeChoice;
			}

			//���Ͱ� ���� �����Ͽ� �÷��̾ �̰��� ��
			else
			{
				if (monsterSubstitute._HP > 1)
				{
					cout << monsterSubstitute._Name[numberSubstitute] << "���� Ÿ���� �������ϴ�." << endl;
					monsterSubstitute._HP--;
				}

				else
				{
					cout << pPlayer->iName << "��(��) " << monsterSubstitute._Name[numberSubstitute]
						<< "��(��) �̱�̽��ϴ�." << endl;
					cout << monsterSubstitute.giveMoney << "��ŭ�� ���� ȹ���Ͽ����ϴ�." << endl;
					cout << monsterSubstitute.giveExp << "��ŭ�� ����ġ�� ȹ���Ͽ����ϴ�." << endl;

					pPlayer->_Money += monsterSubstitute.giveMoney;
					pPlayer->iExp += monsterSubstitute.giveExp;

					cout << "���� ���� == PAPER" << endl;

					pPlayer->catchMonster++;

					pPlayer->fightMode = false;

					system("pause");
					break;
				}
			}
		}

		if (escapeChoice == 1)	//�÷��̾ ������ �������� ��
		{
			pPlayer->fightMode = false;		return;
		}

		system("pause");
	}
}

void playerStats(PLAYER * pPlayer)
{
	cout << "�̸�:" << pPlayer->iName << "		����:" << pPlayer->iLevel << endl;
	cout << "HP:" << pPlayer->iHP << " / " << pPlayer->imaxHP
		<< "		���̵�:" << pPlayer->levelName << endl;
	cout << "������:" << pPlayer->_Money << "		";
	cout << "����ġ:" << pPlayer->iExp << " / " << pPlayer->imaxExp << endl;
	cout << "���� ����:";

	if (pPlayer->beforeWeapon == NONE_RPS) cout << "NONE		";

	else if (pPlayer->beforeWeapon == SCISSORS) cout << "����		";

	else if (pPlayer->beforeWeapon == ROCK) cout << "����		";

	else cout << "����		";

	cout << "����ǰ: ";
	if (pPlayer->_Possession)
	{
		for (int i = 0; i < pPlayer->possisionNum; i++)
		{
			cout << i + 1 << ". " << pPlayer->_Potion[i]._Name << "	";
		}
	}

	else				   cout << "NONE" << endl;

	cout << endl << "��ƾߵ� ���� ��:" << pPlayer->catchMonster << " / " << pPlayer->catchWin << endl << endl;
	cout << "���� Ű �� t �� || �� T ��		���� ��� Ű �� e �� || �� E ��" << endl;

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

				cout << endl << "�� ���� ��ȭ�� ��" << endl << endl;

				for (i = 0; i < POTION_TYPE - 1; i++)
				{
					cout << i + 1 << ".	���ĸ�: " << pPotion[i]._Name << endl;
					cout << "	����: " << pPotion[i]._Type << endl;
					cout << "	���԰�: " << pPotion[i].purchasePrice << endl;
					cout << "	���ǸŰ�: " << pPotion[i].sellingPrice << endl;
					cout << "	HP ȸ����: " << pPotion[i]._Effect << endl << endl;
				}
				cout << POTION_TYPE << ". ������" << endl;

				cin >> pSelect;

				if (pSelect == STORE_EXIT)
					break;

				if (pPlayer->_Money >= pPotion[pSelect - 1].purchasePrice)
				{
					pPlayer->_Potion[pPlayer->possisionNum++] = pPotion[pSelect - 1];
					pPlayer->_Money -= pPotion[pSelect - 1].purchasePrice;

					pPlayer->_Possession = true;

					cout << "���� ����~" << endl;
				}

				else
					cout << "���� �����մϴ�....." << endl;

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
				cout << "����� ü���� Full�Դϴ�." << endl;

				system("pause");
				break;
			}

			cout << "����� ������ ����ּ���.~~" << endl;

			cin >> pSelect;

			for (i = 0; i < pPlayer->possisionNum; i++)
			{
				if (pSelect == i + 1)
				{
					cout << "�������� " << pPlayer->_Potion[pSelect - 1]._Effect << "��ŭ ȸ�� �Ǿ����ϴ�. !!" << endl;

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
			cout << "������ ���� �ʽ��ϴ�~..." << endl;

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
	//�÷��̾� ���� �ʱ�ȭ
	pPlayer->imaxHP = 10;			pPlayer->iHP = 10;
	pPlayer->_Money = 1500;			pPlayer->iLevel = 1;
	pPlayer->imaxExp = 10;			pPlayer->iExp = 0;
	pPlayer->yPos = -1;				pPlayer->xPos = -1;				// <- ��ġ�� ���������� ����.
	pPlayer->srpWeapon = -1;		pPlayer->beforeWeapon = -1;		// <- ���⸦ �������� �ʾҴ�.
	pPlayer->_Possession = false;	pPlayer->fightMode = false;		// <- ����ǰ ���� / �ο��� ����
	pPlayer->catchMonster = 0;		pPlayer->catchWin = 0;
	pPlayer->possisionNum = 0;
}

void monsterDatabase(MONSTER * pMonster)
{
	//�� ���ϸ�

//���̵� ���� ����
	pMonster[0]._Name[0] = "�̻��ؾ�";		pMonster[0]._Name[1] = "ĳ����";
	pMonster[0]._Name[2] = "������";			pMonster[0]._Name[3] = "����";
	pMonster[0]._Name[4] = "�����";
	pMonster[0]._Type = FOREST;				pMonster[0]._Level = 1;
	pMonster[0].maxHP = 1;					pMonster[0]._HP = 1;
	pMonster[0].giveExp = 10;				pMonster[0].giveMoney = 100;

	//���̵� ���� ����	
	pMonster[1]._Name[0] = "�̻���Ǯ";		pMonster[1]._Name[1] = "�ܵ���";
	pMonster[1]._Name[2] = "������";			pMonster[1]._Name[3] = "����";
	pMonster[1]._Name[4] = "������";
	pMonster[1]._Type = FOREST;				pMonster[1]._Level = 5;
	pMonster[1].maxHP = 5;					pMonster[1]._HP = 5;
	pMonster[1].giveExp = 50;				pMonster[1].giveMoney = 200;

	//���̵� ���� ����
	pMonster[2]._Name[0] = "�̻��ز�";		pMonster[2]._Name[1] = "������";
	pMonster[2]._Name[2] = "��ħ��";			pMonster[2]._Name[3] = "������";
	pMonster[2]._Name[4] = "������Ʈ";
	pMonster[2]._Type = FOREST;				pMonster[2]._Level = 10;
	pMonster[2].maxHP = 10;					pMonster[2]._HP = 10;
	pMonster[2].giveExp = 100;				pMonster[2].giveMoney = 500;

	//���̵� �ſ���� ����
	pMonster[3]._Name[0] = "�ް��̻��ز�";	pMonster[3]._Name[1] = "����_������";
	pMonster[3]._Name[2] = "�ް���ħ��";		pMonster[3]._Name[3] = "�ް�������";
	pMonster[3]._Name[4] = "����_������Ʈ";
	pMonster[3]._Type = FOREST;				pMonster[3]._Level = 15;
	pMonster[3].maxHP = 15;					pMonster[3]._HP = 15;
	pMonster[3].giveExp = 200;				pMonster[3].giveMoney = 750;

	//�� ���ϸ�

	//���̵� ���� ����
	pMonster[4]._Name[0] = "���α�";			pMonster[4]._Name[1] = "����";
	pMonster[4]._Name[2] = "�ƺ�";			pMonster[4]._Name[3] = "������";
	pMonster[4]._Name[4] = "����";
	pMonster[4]._Type = MARSH;				pMonster[4]._Level = 1;
	pMonster[4].maxHP = 1;					pMonster[4]._HP = 1;
	pMonster[4].giveExp = 10;				pMonster[4].giveMoney = 100;

	//���̵� ���� ����
	pMonster[5]._Name[0] = "��Ϻα�";		pMonster[5]._Name[1] = "��Ʈ��";
	pMonster[5]._Name[2] = "�ƺ�ũ";			pMonster[5]._Name[3] = "������";
	pMonster[5]._Name[4] = "������";
	pMonster[5]._Type = MARSH;				pMonster[5]._Level = 5;
	pMonster[5].maxHP = 5;					pMonster[5]._HP = 5;
	pMonster[5].giveExp = 50;				pMonster[5].giveMoney = 200;

	//���̵� ���� ����
	pMonster[6]._Name[0] = "�źϿ�";			pMonster[6]._Name[1] = "����_��Ʈ��";
	pMonster[6]._Name[2] = "����_�ƺ�ũ";	pMonster[6]._Name[3] = "����_������";
	pMonster[6]._Name[4] = "����_������";
	pMonster[6]._Type = MARSH;				pMonster[6]._Level = 10;
	pMonster[6].maxHP = 10;					pMonster[6]._HP = 10;
	pMonster[6].giveExp = 100;				pMonster[6].giveMoney = 500;

	//���̵� �ſ���� ����
	pMonster[7]._Name[0] = "�ް��źϿ�";		pMonster[7]._Name[1] = "����_��Ʈ��";
	pMonster[7]._Name[2] = "����_�ƺ�ũ";	pMonster[7]._Name[3] = "����_������";
	pMonster[7]._Name[4] = "����_������";
	pMonster[7]._Type = MARSH;				pMonster[7]._Level = 15;
	pMonster[7].maxHP = 15;					pMonster[7]._HP = 15;
	pMonster[7].giveExp = 200;				pMonster[7].giveMoney = 750;

	//�� ���ϸ�

	//���̵� ���� ����
	pMonster[8]._Name[0] = "���̸�";			pMonster[8]._Name[1] = "����";
	pMonster[8]._Name[2] = "������";			pMonster[8]._Name[3] = "�ö�Ҹ�";
	pMonster[8]._Name[4] = "ĳ�̽�";
	pMonster[8]._Type = LAND;				pMonster[8]._Level = 1;
	pMonster[8].maxHP = 1;					pMonster[8]._HP = 1;
	pMonster[8].giveExp = 10;				pMonster[8].giveMoney = 100;

	//���̵� ���� ����						 
	pMonster[9]._Name[0] = "���ڵ�";			pMonster[9]._Name[1] = "��ī��";
	pMonster[9]._Name[2] = "������";			pMonster[9]._Name[3] = "ȫ����";
	pMonster[9]._Name[4] = "���ֶ�";
	pMonster[9]._Type = LAND;				pMonster[9]._Level = 5;
	pMonster[9].maxHP = 5;					pMonster[9]._HP = 5;
	pMonster[9].giveExp = 50;				pMonster[9].giveMoney = 200;

	//���̵� ���� ����						 
	pMonster[10]._Name[0] = "���ڸ�";		pMonster[10]._Name[1] = "������";
	pMonster[10]._Name[2] = "������";		pMonster[10]._Name[3] = "����_ȫ����";
	pMonster[10]._Name[4] = "�ĵ�";
	pMonster[10]._Type = LAND;				pMonster[10]._Level = 10;
	pMonster[10].maxHP = 10;				pMonster[10]._HP = 10;
	pMonster[10].giveExp = 100;				pMonster[10].giveMoney = 500;

	//���̵� �ſ���� ����					 
	pMonster[11]._Name[0] = "�ް����ڸ�";	pMonster[11]._Name[1] = "����_������";
	pMonster[11]._Name[2] = "����_������";	pMonster[11]._Name[3] = "����_ȫ����";
	pMonster[11]._Name[4] = "����_�ĵ�";
	pMonster[11]._Type = LAND;				pMonster[11]._Level = 15;
	pMonster[11].maxHP = 15;				pMonster[11]._HP = 15;
	pMonster[11].giveExp = 200;				pMonster[11].giveMoney = 750;

	//�� ����								 
	pMonster[12]._Name[0] = "�߻�";			pMonster[12]._Name[1] = "����";
	pMonster[12]._Name[2] = "��״�";		pMonster[12]._Name[3] = "�丣�ÿ�";
	pMonster[12]._Name[4] = "��Ű";			pMonster[12]._Name[5] = "����Ĵ�";
	pMonster[12]._Name[6] = "����";			pMonster[12]._Name[7] = "�մ���";
	pMonster[12]._Name[8] = "�극��";		pMonster[12]._Name[9] = "�ߵ�";
	pMonster[12]._Name[10] = "ũ��";			pMonster[12]._Name[11] = "�ս���";
	pMonster[12]._Name[12] = "������";		pMonster[12]._Name[13] = "����";
	pMonster[12]._Name[14] = "���Ӹ�";
	pMonster[12]._Type = HYBRID;			pMonster[12]._Level = 3;
	pMonster[12].maxHP = 3;					pMonster[12]._HP = 3;
	pMonster[12].giveExp = 30;				pMonster[12].giveMoney = 150;
}

void PotionDatabase(POTION * pPotion)
{
	strcpy_s(pPotion[0]._Name, strlen("��ġ�") + 1, "��ġ�");
	strcpy_s(pPotion[0]._Type, typeContents, "�ʰ� ¥�� ��~~ ����� �ѳ��� �����Ѵ�!");
	pPotion[0].purchasePrice = 150;
	pPotion[0].sellingPrice = 50;
	pPotion[0]._Effect = 2;
	pPotion[0]._Use = false;

	strcpy_s(pPotion[1]._Name, strlen("ġ��") + 1, "ġ��");
	strcpy_s(pPotion[1]._Type, typeContents, "��¥����~~�� �� �ε巯�� ��ɵ��");
	pPotion[1].purchasePrice = 300;
	pPotion[1].sellingPrice = 200;
	pPotion[1]._Effect = 5;
	pPotion[1]._Use = false;

	strcpy_s(pPotion[2]._Name, strlen("�׳�ġŲ") + 1, "�׳�ġŲ");
	strcpy_s(pPotion[2]._Type, typeContents, "������ �⸧���� Ƣ�� ���ִ� �Ķ��̵�");
	pPotion[2].purchasePrice = 450;
	pPotion[2].sellingPrice = 350;
	pPotion[2]._Effect = 7;
	pPotion[2]._Use = false;

	strcpy_s(pPotion[3]._Name, strlen("���̳�����") + 1, "���̳�����");
	strcpy_s(pPotion[3]._Type, typeContents, "���� ���ڴ� ���̳��� ~~~!!");
	pPotion[3].purchasePrice = 700;
	pPotion[3].sellingPrice = 500;
	pPotion[3]._Effect = 9;
	pPotion[3]._Use = false;
}

void levelSystem(PLAYER * pPlayer, MONSTER * pMonster)
{
	//�÷��̾� �ɷ�ġ ���
	pPlayer->iLevel++;
	pPlayer->imaxHP += 5;	pPlayer->iHP += 5;
	pPlayer->iExp = 0;		pPlayer->imaxExp += 50;

	// ���� �ɷ�ġ ���

	//���̵� ����
	pMonster[0]._Level++;
	pMonster[0].maxHP++;					pMonster[0]._HP++;
	pMonster[0].giveExp += 10;				pMonster[0].giveMoney += 50;

	//���̵� ���� 
	pMonster[1]._Level++;
	pMonster[1].maxHP++;					pMonster[1]._HP++;
	pMonster[1].giveExp += 20;				pMonster[1].giveMoney += 70;

	//���̵� ���� 
	pMonster[2]._Level++;
	pMonster[2].maxHP++;					pMonster[2]._HP++;
	pMonster[2].giveExp += 30;				pMonster[2].giveMoney += 100;

	//���̵� �ſ����
	pMonster[3]._Level++;
	pMonster[3].maxHP++;					pMonster[3]._HP++;
	pMonster[3].giveExp += 40;				pMonster[3].giveMoney += 150;

	//�� ���ϸ�

	//���̵� ����
	pMonster[4]._Level++;
	pMonster[4].maxHP++;					pMonster[4]._HP++;
	pMonster[4].giveExp += 10;				pMonster[4].giveMoney += 50;

	//���̵� ���� 
	pMonster[5]._Level++;
	pMonster[5].maxHP++;					pMonster[5]._HP++;
	pMonster[5].giveExp += 20;				pMonster[5].giveMoney += 70;

	//���̵� ���� 
	pMonster[6]._Level++;
	pMonster[6].maxHP++;					pMonster[6]._HP++;
	pMonster[6].giveExp += 30;				pMonster[6].giveMoney += 100;

	//���̵� �ſ����
	pMonster[7]._Level++;
	pMonster[7].maxHP++;					pMonster[7]._HP++;
	pMonster[7].giveExp += 40;				pMonster[7].giveMoney += 150;

	//�� ���ϸ�

	//���̵� ����
	pMonster[8]._Level++;
	pMonster[8].maxHP++;					pMonster[8]._HP++;
	pMonster[8].giveExp += 10;				pMonster[8].giveMoney += 50;

	//���̵� ���� 
	pMonster[9]._Level++;
	pMonster[9].maxHP++;					pMonster[9]._HP++;
	pMonster[9].giveExp += 20;				pMonster[9].giveMoney += 70;

	//���̵� ���� 
	pMonster[10]._Level++;
	pMonster[10].maxHP++;					pMonster[10]._HP++;
	pMonster[10].giveExp += 30;				pMonster[10].giveMoney += 100;

	//���̵� �ſ����
	pMonster[11]._Level++;
	pMonster[11].maxHP++;					pMonster[11]._HP++;
	pMonster[11].giveExp += 40;				pMonster[11].giveMoney += 150;

	//�� ����
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
