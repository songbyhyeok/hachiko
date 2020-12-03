#include "AI.h"

AI::AI() : numericalgap(0), participation(true) {}

void AI::DecideBet(Dealer * dealer, int & _ainum_allocate, int & gamecount)
{
	int meetEighty = rand() % PROBABILITY < 80; // <- 80�ۼ�Ʈ�� ����Ŵ
	int meetSixty = rand() % PROBABILITY < 60; // <- 60�ۼ�Ʈ�� ����Ŵ
	int meetForty = rand() % PROBABILITY < 40; // <- 40�ۼ�Ʈ�� ����Ŵ
	int meetTwenty = rand() % PROBABILITY < 20; // <- 20�ۼ�Ʈ�� ����Ŵ

	int veryhighBet = 750;	int highBet = 500;
	int midBet = 250;	int lowBet = 100;

	int i;
	
	for (i = 0; i < _ainum_allocate; i++)
	{
		if (this[i].GetParticipation() == true)
		{
			this[i].SetNumGap(this[i].card[0].GetNum() - this[i].card[1].GetNum());

			if (-10 >= this[i].GetNumGap() && this[i].GetNumGap() >= -12 && meetEighty == PROBABILITY_TRUE)
			{
				cout << this[i].GetName() << "���� " << veryhighBet << "��ŭ ���� �Ͽ����ϴ�." << endl;

				this[i].PutMoney(-veryhighBet);	dealer->SetAmount(veryhighBet);
				this[i].SetBet(veryhighBet);
			}

			else if (-7 >= this[i].GetNumGap() && this[i].GetNumGap() >= -9 && meetSixty == PROBABILITY_TRUE)
			{
				cout << this[i].GetName() << "���� " << highBet << "��ŭ ���� �Ͽ����ϴ�." << endl;

				this[i].PutMoney(-highBet);	dealer->SetAmount(highBet);
				this[i].SetBet(highBet);
			}

			else if (-4 >= this[i].GetNumGap() && this[i].GetNumGap() >= -6 && meetForty == PROBABILITY_TRUE)
			{
				cout << this[i].GetName() << "���� " << midBet << "��ŭ ���� �Ͽ����ϴ�." << endl;

				this[i].PutMoney(-midBet);	dealer->SetAmount(midBet);
				this[i].SetBet(midBet);
			}

			else if (-1 >= this[i].GetNumGap() && this[i].GetNumGap() >= -3 && meetTwenty == PROBABILITY_TRUE)
			{
				cout << this[i].GetName() << "���� " << lowBet << "��ŭ ���� �Ͽ����ϴ�." << endl;

				this[i].PutMoney(-lowBet);	dealer->SetAmount(lowBet);
				this[i].SetBet(lowBet);
			}

			else
			{
				cout << this[i].GetName() << "���� ���� �ϼ̽��ϴ�." << endl;
				this[i].SetParticipation(false);
			}
		}
	}

	for (i = 0; i < _ainum_allocate; i++)
	{
		if (this[i].GetParticipation() == true)
		{
			cout << this[i].GetName() << "�Կ��� ���ο� ī�带 �־����ϴ�." << endl;

			if (this[i].card[0].GetNum() < this[i].card[2].GetNum() && this[i].card[1].GetNum() > this[i].card[2].GetNum())
			{
				cout << this[i].GetName() << "���� ���ÿ� ���� �Ͽ����ϴ�." << endl;

				this[i].PutMoney(this[i].GetBet() * 2);		dealer->SetAmount(-this[i].GetBet() * 2);
			}

			else
			{
				cout << "����..." << endl;

				this[i].SetParticipation(false);
			}

			gamecount++;
		}
	}

	system("pause");
}

void AI::SetNumGap(int _numericalgap) { numericalgap = _numericalgap; }

int AI::GetNumGap() { return numericalgap; }

void AI::SetBet(int _bet) { bet = _bet; }

int AI::GetBet() { return bet; }

void AI::SetName(string _name) { name = _name; }

void AI::SetMoney(int _money) { money = _money; }

void AI::PutMoney(int possession_money) { money += possession_money; }

int AI::GetMoney() { return money; }

int AI::TakeMoney(int possession_money)
{
	if (money < possession_money)
	{
		cout << "���� ���ġ �ʽ��ϴ�. " << endl;
		return 0;
	}

	money -= possession_money;

	return money;
}

int AI::ShowMoney() { return money; }

string AI::GetName() { return name; }

void AI::SetParticipation(bool _participation) { participation = _participation; }

bool AI::GetParticipation() { return participation; }
