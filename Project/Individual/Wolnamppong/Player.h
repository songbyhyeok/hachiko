#pragma once

#include "OtherElement.h"
#include "PlayingCard.h"
#include "Dealer.h"

class Player
{
private:
	string name;
	int money;
	int playerBet; //플레이어가 배팅을 할지 안할지 선택변수.
	int playerSelect;
	bool participation;
	int bet;

public:
	PlayingCard card[RECEIVECARD];

public:
	Player();
	void DecideBet(Dealer * dealer, int & gamecount);
	void SetName(string _name);
	void SetMoney(int _money);
	void SetBet(int _bet);
	int GetBet();
	void PutMoney(int possession_money);
	int GetMoney();
	int TakeMoney(int possession_money);
	void SetOrder(int _order);
	void SetChoice(int _choice);
	int ShowMoney();
	string GetName();
	void SetParticipation(bool _participation);
	bool GetParticipation();
};

