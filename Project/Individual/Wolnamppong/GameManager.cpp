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

	//플레이어에 대한 정보
	player = new Player;

	player->SetName("남궁혁");	player->SetMoney(1000);

	//AI에 대한 정보
	ai = new AI[AINUM_ADJUST];

	for (i = 0; i < 4; i++)
		ai[i].SetMoney(1000);

	ai[0].SetName("고니");		ai[1].SetName("정마담");
	ai[2].SetName("평경장");		ai[3].SetName("고광렬");
	ai[4].SetName("곽철용");		ai[5].SetName("박무석");
	ai[6].SetName("아귀");		ai[7].SetName("짝귀");
	ai[8].SetName("너구리");

	AI ai_tempname[AINUM_ADJUST];

	ai_tempname[0].SetName("고니");		ai_tempname[1].SetName("정마담");
	ai_tempname[2].SetName("평경장");	ai_tempname[3].SetName("고광렬");
	ai_tempname[4].SetName("곽철용");	ai_tempname[5].SetName("박무석");
	ai_tempname[6].SetName("아귀");		ai_tempname[7].SetName("짝귀");
	ai_tempname[8].SetName("너구리");

	int random_Name, duplicatedScan[AINUM_ADJUST] = { 0 };

	//AI 이름을 섞어주는 FOR문
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

	//카드에 대한 정보
	card = new PlayingCard*[SHAPE_NUM];

	for (i = 0; i < SHAPE_NUM; i++)
		card[i] = new PlayingCard[CARD_NUM];

	for (i = 0; i < SHAPE_NUM; i++)
	{
		for (j = 0; j < CARD_NUM; j++)
		{
			if (i == 0)
			card[i][j].SetShape("♤");

			else if (i == 1)
			card[i][j].SetShape("◇");

			else if (i == 2)
			card[i][j].SetShape("♧");

			else if (i == 3)
			card[i][j].SetShape("♡");

			card[i][j].SetNum(j + 2);
		}
	}

	//딜러에 대한 정보
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
		cout << "이름: " << player->GetName() << "		소지금: " << player->ShowMoney() << endl;
		cout << "첫번째 카드: " << player->card[0].GetShape() << "의 " << player->card[0].GetNum() << "입니다" << "	";
		cout << "두번째 카드: " << player->card[1].GetShape() << "의 " << player->card[1].GetNum() << "입니다" << endl;
	}

	for (int i = 0; i < ainum_allocate; i++)
	{
		if (ai[i].GetParticipation() == true)
		{
			cout << "이름: " << ai[i].GetName() << "		소지금: " << ai[i].ShowMoney() << endl;
			cout << "첫번째 카드: " << ai[i].card[0].GetShape() << "의 " << ai[i].card[0].GetNum() << "입니다" << "	";
			cout << "두번째 카드: " << ai[i].card[1].GetShape() << "의 " << ai[i].card[1].GetNum() << "입니다" << endl;
		}
	}

	cout << endl << "사용된 카드 수: " << gamecount << endl;
	cout << "현재 누적된 배팅금: " << dealer->GetAmount() << endl;
}

void GameManager::GameDescription()
{
	system("cls");

	cout << "월남뽕 게임" << endl;

	cout << "게임설명: ";
	cout << "베트남 병사들이 카드게임 레드 독을 화투로 로컬라이징 한 것이 시초이다." << endl;

	system("pause");
}

void GameManager::SetGame()
{
	cout << "참여 인원수를 입력하세요. " << endl;
	cin >> totalparticipant;

	if (totalparticipant < 1 || totalparticipant > 10)
	{
		cout << "10명까지 가능합니다." << endl;
		return;
	}

	ainum_allocate = totalparticipant - 1;
}

void GameManager::Shuffle()
{
	int mixCard, mixCard2, mixShape, mixShape2;

	PlayingCard tempCard;

	//카드 섞기
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

	int decideDealer = rand() % 10; // 딜러를 결정해주는 변수

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

	//게임 참여권한을 주는 bool값
	player->SetParticipation(true);

	for (i = 0; i < ainum_allocate; i++)
		 ai[i].SetParticipation(true);

	if (dealer->GetAmount() == 0) // 중앙 테이블 판돈이 0이라면 다시 딜러가 재구성한다.
	{
		dealer->SetBet(decideBet);	// 랜덤으로 딜러가 배팅 금을 100 ~ 500 설정

		// 배팅 금을 누적
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

			cout << "딜러가 첫번째 순서로 플레이어를 가리켰습니다. " << endl;

			dealer->SetRoad(true);
		}

		else
		{
			decide_ai = rand() % ainum_allocate; // 어떤 AI가 먼저인지 알려주는 변수

			(*dealer).pick_ai = &ai[decide_ai];
			cout << dealer->pick_ai->GetName() << "님이 첫번째 순서입니다." << endl;

			dealer->SetRoad(false);
		}

		cout << "딜러가 배팅금을 " << dealer->GetBet() << "으로 정하였습니다." << endl;
	}

	else
		cout << "현재 판돈이 남아 있으므로 순서가 유효합니다." << endl;

	system("pause");
}

void GameManager::CardDistribute()
{
	system("cls");

	int i, j;

	int mixCard, mixShape;

	//게임 참여권한을 주는 bool값
	player->SetParticipation(true);

	for (int i = 0; i < ainum_allocate; i++)
		ai[i].SetParticipation(true);

	//플레이어에게 카드를 나눠주는 코드
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

	//AI에게 카드를 나눠주는 코드
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

	//플레이어 or AI 중 누가 먼저 선인지 골라주는 코드
	cout << "딜러가 카드를 섞습니다." << endl << endl;
	 
	if (dealer->GetRoad() == true)
	{
		for (i = 0; i < 2; i++)
		{
			if (i == 1)
				cout << endl;

			cout << dealer->pick_player->GetName() << "님에게 " << i + 1 << "번째 카드를 주었습니다." << endl;

			for (j = 0; j < ainum_allocate; j++)
				cout << ai[j].GetName() << "님에게 " << i + 1 << "번째 카드를 주었습니다." << endl;
		}
	}

	else if (dealer->GetRoad() == false)
	{
		for (i = 0; i < 2; i++)
		{
			if (i == 1)
				cout << endl;

			cout << dealer->pick_ai->GetName() << "님에게 " << i + 1 << "번째 카드를 주었습니다." << endl;
			cout << player->GetName() << "님에게 " << i + 1 << "번째 카드를 주었습니다." << endl;

			for (j = 0; j < ainum_allocate; j++)
			{
				if (ai[j].GetName() != dealer->pick_ai->GetName())
					cout << ai[j].GetName() << "님에게 " << i + 1 << "번째 카드를 주었습니다." << endl;
			}
		}
	}

	cout << endl;

	//알파벳 K가 나왔을 때 코드
	if (player->card[0].GetNum() == ALPHABET_K && player->card[1].GetNum() == ALPHABET_K)
	{
		cout << "플레이어의 카드가 ~~! 알파벳 K더블 !! 중앙에 있는 돈을 모두 가져옵니다." << endl;

		player->PutMoney(player->GetBet());		dealer->SetAmount(0);

		player->SetParticipation(false);
	}

	else if (player->card[0].GetNum() == ALPHABET_K || player->card[1].GetNum() == ALPHABET_K)
	{
		cout << "어.. 알파벳 K가 나왔습니다. 이번 게임에서 빠집니다." << endl;

		player->SetParticipation(false);
	}

	else if (player->card[0].GetNum() == player->card[1].GetNum())
	{
		cout << "받은 두 카드가 동일합니다. 이번 게임에서 빠집니다." << endl;

		player->PutMoney(player->GetBet());		dealer->SetAmount(-player->GetBet());

		player->SetParticipation(false);
	}

	for (i = 0; i < ainum_allocate; i++)
	{
		if (ai[i].card[0].GetNum() == ALPHABET_K && ai[i].card[1].GetNum() == ALPHABET_K)
		{
			cout << "알파벳 K더블 !! " << ai[i].GetName() << "님이 중앙에 있는 돈을 모두 가져갑니다." << endl;

			ai[i].PutMoney(ai[i].GetBet());		dealer->SetAmount(0);

			ai[i].SetParticipation(false);
		}

		else if (ai[i].card[0].GetNum() == ALPHABET_K || ai[i].card[1].GetNum() == ALPHABET_K)
		{
			cout << "알파벳 K가 나왔습니다. " << ai[i].GetName() << "님이 이번 게임에서 빠집니다." << endl;

			ai[i].SetParticipation(false);
		}

		else if (ai[i].card[0].GetNum() == ai[i].card[1].GetNum())
		{
			cout << "두 카드가 동일합니다. " << ai[i].GetName() << "님이 이번 게임에서 빠집니다." << endl;

			ai[i].PutMoney(ai[i].GetBet());		dealer->SetAmount(-ai[i].GetBet());

			ai[i].SetParticipation(false);
		}
	}
	
	PlayingCard tempCard;

	//플레이어, AI가 받은 첫번째 카드가 두번째 카드보다 숫자가 높을 경우 바꿔주는 코드
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

		//선택권
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
