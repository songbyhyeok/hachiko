#include "OtherElement.h"
#include "GameManager.h"
#include "Player.h"

int main()
{
	srand(time(NULL));

	GameManager * _GM = new GameManager;
	Player * _Player = new Player;

	_GM->SetGame();
	_GM->Shuffle();

	 while (_GM->GetCalculateCount() <= CARD_TOTAL)
	{
		_GM->DealerDecide();
		_GM->CardDistribute();
		_GM->JudgeSituation();

		

	}

	return 0;
}