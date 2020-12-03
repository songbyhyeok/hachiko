#include "GameManager.h"
#include "Player.h"
#include "AI.h"
#include "PlayingCard.h"
#include "Dealer.h"
#include "OtherElement.h"

GameManager::GameManager()
	:totalparticipant(0), ainum_allocate(0), decide_ai(0), gamecount(0), cardcount(0)
{
	int i, j;

	//�÷��̾ ���� ����
	player = new Player;

	player->SetName("������");	player->SetMoney(1000);

	//AI�� ���� ����
	ai = new AI[AINUM_ADJUST];

	for (i = 0; i < 4; i++)
		ai[i].SetMoney(1000);

	ai[0].SetName("���");		ai[1].SetName("������");
	ai[2].SetName("�����");		ai[3].SetName("����");
	ai[4].SetName("��ö��");		ai[5].SetName("�ڹ���");
	ai[6].SetName("�Ʊ�");		ai[7].SetName("¦��");
	ai[8].SetName("�ʱ���");

	AI ai_tempname[AINUM_ADJUST];

	ai_tempname[0].SetName("���");		ai_tempname[1].SetName("������");
	ai_tempname[2].SetName("�����");	ai_tempname[3].SetName("����");
	ai_tempname[4].SetName("��ö��");	ai_tempname[5].SetName("�ڹ���");
	ai_tempname[6].SetName("�Ʊ�");		ai_tempname[7].SetName("¦��");
	ai_tempname[8].SetName("�ʱ���");

	int random_Name, duplicatedScan[AINUM_ADJUST] = { 0 };

	//AI �̸��� �����ִ� FOR��
	for (i = 0; i < AINUM_ADJUST; i++)
	{
		while (true)
		{	
			random_Name = rand() % AINUM_ADJUST;
			
			if (duplicatedScan[random_Name] == 0) 
			{
				ai[i].SetName(ai_tempname[random_Name].GetName());
				duplicatedScan[random_Name] = 1;

				break;
			}
		}	
	}

	//ī�忡 ���� ����
	card = new PlayingCard*[SHAPE_NUM];

	for (i = 0; i < SHAPE_NUM; i++)
		card[i] = new PlayingCard[CARD_NUM];

	for (i = 0; i < SHAPE_NUM; i++)
	{
		for (j = 0; j < CARD_NUM; j++)
		{
			if (i == 0)
			card[i][j].SetShape("��");

			else if (i == 1)
			card[i][j].SetShape("��");

			else if (i == 2)
			card[i][j].SetShape("��");

			else if (i == 3)
			card[i][j].SetShape("��");

			card[i][j].SetNum(j + 2);
		}
	}

	//������ ���� ����
	dealer = new Dealer;
}

void GameManager::SetCalculateCount()
{
	calculateCount = gamecount + (totalparticipant * 3);
}

int GameManager::GetCalculateCount()
{
	return calculateCount;
}

void GameManager::ShowStatus()
{
	if (player->GetParticipation() == true)
	{
		cout << "�̸�: " << player->GetName() << "		������: " << player->ShowMoney() << endl;
		cout << "ù��° ī��: " << player->card[0].GetShape() << "�� " << player->card[0].GetNum() << "�Դϴ�" << "	";
		cout << "�ι�° ī��: " << player->card[1].GetShape() << "�� " << player->card[1].GetNum() << "�Դϴ�" << endl;
	}

	for (int i = 0; i < ainum_allocate; i++)
	{
		if (ai[i].GetParticipation() == true)
		{
			cout << "�̸�: " << ai[i].GetName() << "		������: " << ai[i].ShowMoney() << endl;
			cout << "ù��° ī��: " << ai[i].card[0].GetShape() << "�� " << ai[i].card[0].GetNum() << "�Դϴ�" << "	";
			cout << "�ι�° ī��: " << ai[i].card[1].GetShape() << "�� " << ai[i].card[1].GetNum() << "�Դϴ�" << endl;
		}
	}

	cout << endl << "���� ī�� ��: " << gamecount << endl;
	cout << "���� ������ ���ñ�: " << dealer->GetAmount() << endl;
}

void GameManager::GameDescription()
{
	system("cls");

	cout << "������ ����" << endl;

	cout << "���Ӽ���: ";
	cout << "��Ʈ�� ������� ī����� ���� ���� ȭ���� ���ö���¡ �� ���� �����̴�." << endl;

	system("pause");
}

void GameManager::SetGame()
{
	cout << "���� �ο����� �Է��ϼ���. " << endl;
	cin >> totalparticipant;

	if (totalparticipant < 1 || totalparticipant > 10)
	{
		cout << "10����� �����մϴ�." << endl;
		return;
	}

	ainum_allocate = totalparticipant - 1;
}

void GameManager::Shuffle()
{
	int mixCard, mixCard2, mixShape, mixShape2;

	PlayingCard tempCard;

	//ī�� ����
	for (int i = 0; i < 100; i++)
	{
		mixShape = rand() % SHAPE_NUM;		mixCard = rand() % CARD_NUM;
		mixShape2 = rand() % SHAPE_NUM;		mixCard2 = rand() % CARD_NUM;

		tempCard = card[mixShape][mixCard];
		card[mixShape][mixCard] = card[mixShape2][mixCard2];
		card[mixShape2][mixCard2] = tempCard;
	}
}

void GameManager::DealerDecide()
{
	system("cls");

	int decideDealer = rand() % 10; // ������ �������ִ� ����

	int decideBet = rand() % 5 + 1;

	switch (decideBet)
	{
	case 1:
		decideBet = ONE_HUNDRED;
			break;
	case 2:
		decideBet = TWO_HUNDRED;
			break;
	case 3:
		decideBet = THREE_HUNDRED;
			break;
	case 4:
		decideBet = FOUR_HUNDRED;
			break;
	case 5:
		decideBet = FIVE_HUNDRED;
			break;
	}

	int i;

	//���� ���������� �ִ� bool��
	player->SetParticipation(true);

	for (i = 0; i < ainum_allocate; i++)
		 ai[i].SetParticipation(true);

	if (dealer->GetAmount() == 0) // �߾� ���̺� �ǵ��� 0�̶�� �ٽ� ������ �籸���Ѵ�.
	{
		dealer->SetBet(decideBet);	// �������� ������ ���� ���� 100 ~ 500 ����

		// ���� ���� ����
		player->TakeMoney(dealer->GetBet());	player->SetBet(dealer->GetBet());
		dealer->SetAmount(dealer->GetBet());

		for (i = 0; i < ainum_allocate; i++)
		{
			ai[i].TakeMoney(dealer->GetBet());	ai->SetBet(dealer->GetBet());
			dealer->SetAmount(dealer->GetBet());
		}

		if (decideDealer < 5)
		{
			dealer->pick_player = player;

			cout << "������ ù��° ������ �÷��̾ �����׽��ϴ�. " << endl;

			dealer->SetRoad(true);
		}

		else
		{
			decide_ai = rand() % ainum_allocate; // � AI�� �������� �˷��ִ� ����

			(*dealer).pick_ai = &ai[decide_ai];
			cout << dealer->pick_ai->GetName() << "���� ù��° �����Դϴ�." << endl;

			dealer->SetRoad(false);
		}

		cout << "������ ���ñ��� " << dealer->GetBet() << "���� ���Ͽ����ϴ�." << endl;
	}

	else
		cout << "���� �ǵ��� ���� �����Ƿ� ������ ��ȿ�մϴ�." << endl;

	system("pause");
}

void GameManager::CardDistribute()
{
	system("cls");

	int i, j;

	int mixCard, mixShape;

	//���� ���������� �ִ� bool��
	player->SetParticipation(true);

	for (int i = 0; i < ainum_allocate; i++)
		ai[i].SetParticipation(true);

	//�÷��̾�� ī�带 �����ִ� �ڵ�
	for (i = 0; i < 3; i++)
	{
		mixShape = rand() % SHAPE_NUM;		mixCard = rand() % CARD_NUM;

		if (card[mixShape][mixCard].GetNum() != -1)
			player->card[i] = card[mixShape][mixCard];

		else
		{
			while (true)
			{
				mixShape = rand() % SHAPE_NUM;		mixCard = rand() % CARD_NUM;

				if (card[mixShape][mixCard].GetNum() != -1)
				{
					player->card[i] = card[mixShape][mixCard];

					break;
				}
			}
		}

		card[mixShape][mixCard].SetNum(-1);		card[mixShape][mixCard].SetShape("-1");

		if (i != 2)
			gamecount++;
	}

	//AI���� ī�带 �����ִ� �ڵ�
	for (i = 0; i < ainum_allocate; i++)
	{
		for (j = 0; j < 3; j++)
		{
			mixShape = rand() % SHAPE_NUM;	mixCard = rand() % CARD_NUM;

			if (card[mixShape][mixCard].GetNum() != -1)
				ai[i].card[j] = card[mixShape][mixCard];

			else
			{
				while (true)
				{
					mixShape = rand() % SHAPE_NUM;		mixCard = rand() % CARD_NUM;

					if (card[mixShape][mixCard].GetNum() != -1)
					{
						ai[i].card[j] = card[mixShape][mixCard];

						break;
					}
				}
			}

			card[mixShape][mixCard].SetNum(-1);		card[mixShape][mixCard].SetShape("-1");

			if (j != 2)
				gamecount++;
		}
	}

	//�÷��̾� or AI �� ���� ���� ������ ����ִ� �ڵ�
	cout << "������ ī�带 �����ϴ�." << endl << endl;
	 
	if (dealer->GetRoad() == true)
	{
		for (i = 0; i < 2; i++)
		{
			if (i == 1)
				cout << endl;

			cout << dealer->pick_player->GetName() << "�Կ��� " << i + 1 << "��° ī�带 �־����ϴ�." << endl;

			for (j = 0; j < ainum_allocate; j++)
				cout << ai[j].GetName() << "�Կ��� " << i + 1 << "��° ī�带 �־����ϴ�." << endl;
		}
	}

	else if (dealer->GetRoad() == false)
	{
		for (i = 0; i < 2; i++)
		{
			if (i == 1)
				cout << endl;

			cout << dealer->pick_ai->GetName() << "�Կ��� " << i + 1 << "��° ī�带 �־����ϴ�." << endl;
			cout << player->GetName() << "�Կ��� " << i + 1 << "��° ī�带 �־����ϴ�." << endl;

			for (j = 0; j < ainum_allocate; j++)
			{
				if (ai[j].GetName() != dealer->pick_ai->GetName())
					cout << ai[j].GetName() << "�Կ��� " << i + 1 << "��° ī�带 �־����ϴ�." << endl;
			}
		}
	}

	cout << endl;

	//���ĺ� K�� ������ �� �ڵ�
	if (player->card[0].GetNum() == ALPHABET_K && player->card[1].GetNum() == ALPHABET_K)
	{
		cout << "�÷��̾��� ī�尡 ~~! ���ĺ� K���� !! �߾ӿ� �ִ� ���� ��� �����ɴϴ�." << endl;

		player->PutMoney(player->GetBet());		dealer->SetAmount(0);

		player->SetParticipation(false);
	}

	else if (player->card[0].GetNum() == ALPHABET_K || player->card[1].GetNum() == ALPHABET_K)
	{
		cout << "��.. ���ĺ� K�� ���Խ��ϴ�. �̹� ���ӿ��� �����ϴ�." << endl;

		player->SetParticipation(false);
	}

	else if (player->card[0].GetNum() == player->card[1].GetNum())
	{
		cout << "���� �� ī�尡 �����մϴ�. �̹� ���ӿ��� �����ϴ�." << endl;

		player->PutMoney(player->GetBet());		dealer->SetAmount(-player->GetBet());

		player->SetParticipation(false);
	}

	for (i = 0; i < ainum_allocate; i++)
	{
		if (ai[i].card[0].GetNum() == ALPHABET_K && ai[i].card[1].GetNum() == ALPHABET_K)
		{
			cout << "���ĺ� K���� !! " << ai[i].GetName() << "���� �߾ӿ� �ִ� ���� ��� �������ϴ�." << endl;

			ai[i].PutMoney(ai[i].GetBet());		dealer->SetAmount(0);

			ai[i].SetParticipation(false);
		}

		else if (ai[i].card[0].GetNum() == ALPHABET_K || ai[i].card[1].GetNum() == ALPHABET_K)
		{
			cout << "���ĺ� K�� ���Խ��ϴ�. " << ai[i].GetName() << "���� �̹� ���ӿ��� �����ϴ�." << endl;

			ai[i].SetParticipation(false);
		}

		else if (ai[i].card[0].GetNum() == ai[i].card[1].GetNum())
		{
			cout << "�� ī�尡 �����մϴ�. " << ai[i].GetName() << "���� �̹� ���ӿ��� �����ϴ�." << endl;

			ai[i].PutMoney(ai[i].GetBet());		dealer->SetAmount(-ai[i].GetBet());

			ai[i].SetParticipation(false);
		}
	}
	
	PlayingCard tempCard;

	//�÷��̾�, AI�� ���� ù��° ī�尡 �ι�° ī�庸�� ���ڰ� ���� ��� �ٲ��ִ� �ڵ�
	if (player->card[0].GetNum() > player->card[1].GetNum())
	{
			   tempCard = player->card[0];
		player->card[0] = player->card[1];
		player->card[1] = tempCard;
	}

	for (i = 0; i < ainum_allocate; i++)
	{
		if (ai[i].card[0].GetNum() > ai[i].card[1].GetNum())
		{
			tempCard = ai[i].card[0];
			ai[i].card[0] = ai[i].card[1];
			ai[i].card[1] = tempCard;
		}
	}

	system("pause");
}

void GameManager::JudgeSituation()
{
		system("cls");

		ShowStatus();

		//���ñ�
		if (dealer->GetRoad() == true && dealer->pick_player->GetParticipation() == true)
		{	
			player->DecideBet(dealer, this->gamecount);
			ai->DecideBet(dealer, this->ainum_allocate, this->gamecount);	
		}

		else if (dealer->GetRoad() == false && dealer->pick_ai->GetParticipation() == true)
		{
			ai->DecideBet(dealer, this->ainum_allocate, this->gamecount);
			player->DecideBet(dealer, this->gamecount);
		}

		
}
