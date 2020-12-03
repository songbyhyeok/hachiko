#include "Player.h"

Player::Player() : participation(true) {}

void Player::DecideBet(Dealer * dealer, int & gamecount)
{
	if (this->GetParticipation() == true)
	{
		cout << "배팅 하시겠습니까? " << endl;
		cout << "1. 배팅한다" << endl;	cout << "2. 안한다." << endl;

		cin >> playerSelect;

		if (playerSelect == 1)
		{
			cout << "배팅금액을 입력 해주세요." << endl;
			cin >> playerBet;

			if (ShowMoney() < playerBet)
			{
				cout << "배팅할 금액이 모자릅니다 " << endl;
				DecideBet(dealer, gamecount);
			}

			else
			{
				SetBet(playerBet);

				cout << GetName() << "님이 새로운 카드를 받았습니다." << endl;
				cout << card[2].GetShape() << ", " << card[2].GetNum() << "입니다." << endl;
			}

			if (card[0].GetNum() < card[2].GetNum() && card[1].GetNum() > card[2].GetNum())
			{
				cout << "축하합니다. 이기셨습니다." << endl;
				PutMoney(playerBet);	dealer->SetAmount(-playerBet);

				SetParticipation(false);
			}

			else
			{
				cout << "아쉽네요. ㅜㅜ " << endl;

				TakeMoney(playerBet);	dealer->SetAmount(playerBet);

				SetParticipation(false);
			}

			gamecount++;
		}

		else if (playerSelect == 2)
		{
			cout << GetName() << "님이 이번 게임에서 빠집니다." << endl;

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
		cout << "돈이 충분치 않습니다. " << endl;
		return 0;
	}

	money -= possession_money;
	return money;
}

int Player::ShowMoney() { return money; }

string Player::GetName() { return name; }

void Player::SetParticipation(bool _participation) { participation = _participation; }

bool Player::GetParticipation() { return participation; }