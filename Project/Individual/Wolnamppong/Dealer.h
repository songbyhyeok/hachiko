#pragma once

#include "OtherElement.h"

#include "PlayingCard.h"

//전방선언
class AI;
class Player;

class Dealer
{
private:
	int bet, amount;
	bool road;

public:
	Player * pick_player;
	AI * pick_ai;

public:
	Dealer();
	void SetBet(int _bet);
	void SetAmount(int _amount);
	void SetRoad(bool _switch);
	int GetBet();
	int GetAmount();
	bool GetRoad();
};

