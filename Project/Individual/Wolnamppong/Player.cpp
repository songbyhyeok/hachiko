#include "Player.h"

Player::Player() : participation(true) {}

void Player::DecideBet(Dealer * dealer, int & gamecount)
{
	if (this->GetParticipation() == true)
	{
		cout << "���� �Ͻðڽ��ϱ�? " << endl;
		cout << "1. �����Ѵ�" << endl;	cout << "2. ���Ѵ�." << endl;

		cin >> playerSelect;

		if (playerSelect == 1)
		{
			cout << "���ñݾ��� �Է� ���ּ���." << endl;
			cin >> playerBet;

			if (ShowMoney() < playerBet)
			{
				cout << "������ �ݾ��� ���ڸ��ϴ� " << endl;
				DecideBet(dealer, gamecount);
			}

			else
			{
				SetBet(playerBet);

				cout << GetName() << "���� ���ο� ī�带 �޾ҽ��ϴ�." << endl;
				cout << card[2].GetShape() << ", " << card[2].GetNum() << "�Դϴ�." << endl;
			}

			if (card[0].GetNum() < card[2].GetNum() && card[1].GetNum() > card[2].GetNum())
			{
				cout << "�����մϴ�. �̱�̽��ϴ�." << endl;
				PutMoney(playerBet);	dealer->SetAmount(-playerBet);

				SetParticipation(false);
			}

			else
			{
				cout << "�ƽ��׿�. �̤� " << endl;

				TakeMoney(playerBet);	dealer->SetAmount(playerBet);

				SetParticipation(false);
			}

			gamecount++;
		}

		else if (playerSelect == 2)
		{
			cout << GetName() << "���� �̹� ���ӿ��� �����ϴ�." << endl;

			SetParticipation(false);
		}
	}

	system("pause");
}

void Player::SetName(string _name) { name = _name; }

void Player::SetMoney(int _money) { money = _money; }

void Player::SetBet(int _bet) { bet = _bet; }

int Player::GetBet() { return bet; }

void Player::PutMoney(int possession_money) { money += possession_money; }

int Player::GetMoney() { return money; }

int Player::TakeMoney(int possession_money) 
{ 
	if (money < possession_money)
	{
		cout << "���� ���ġ �ʽ��ϴ�. " << endl;
		return 0;
	}

	money -= possession_money;
	return money;
}

int Player::ShowMoney() { return money; }

string Player::GetName() { return name; }

void Player::SetParticipation(bool _participation) { participation = _participation; }

bool Player::GetParticipation() { return participation; }