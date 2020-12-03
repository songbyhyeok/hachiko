#pragma once

#include "OtherElement.h"

class PlayingCard
{
private:
	int num;
	string shape;

public:
	PlayingCard();
	void SetShape(string _shape);
	void SetNum(int _num);
	int GetNum();
	string GetShape();
};

