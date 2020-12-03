#pragma once

#include "OtherElement.h"
#include "PlayingCard.h"
#include "Dealer.h"

class AI
{
private:
	string name;
	int money;
	int numericalgap;
	int	bet;
	bool participation;

public:
	PlayingCard card[RECEIVECARD];

public:
	AI();
	void DecideBet(Dealer * dealer, int & _ainum_allocate, int & gamecount);
	void SetNumGap(int _numericalgap);
	int GetNumGap();
	void SetBet(int _bet);
	int GetBet();
	void SetName(string _name);
	void SetMoney(int _money);
	void PutMoney(int possession_money);
	int GetMoney();
	int TakeMoney(int possession_money);
	int ShowMoney();
	string GetName();
	void SetParticipation(bool _participation);
	bool GetParticipation();
};

