#pragma once

//전방선언
class Player;
class AI;
class PlayingCard;
class Dealer;

class GameManager
{
private:
	Player* player;
	AI* ai;
	PlayingCard** card, * card_scan;
	Dealer* dealer;
	int totalparticipant, ainum_allocate, decide_ai;
	int gamecount; //카드를 얼마나 사용했는지 알 수 있는 변수
	int cardcount; //임시 카드공간에 얼마나 담았는지 알 수 있는 변수
	int calculateCount; // 다음 판에 카드를 나눠줄 때 카드 여유 숫자가 있는지 미리 체크하는 카운트

public:
	GameManager();
	void SetCalculateCount();
	int GetCalculateCount();
	void ShowStatus();
	void GameDescription();
	void SetGame();
	void Shuffle();
	void DealerDecide();
	void CardDistribute();
	void JudgeSituation();
};

