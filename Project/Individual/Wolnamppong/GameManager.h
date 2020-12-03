#pragma once

//���漱��
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
	int gamecount; //ī�带 �󸶳� ����ߴ��� �� �� �ִ� ����
	int cardcount; //�ӽ� ī������� �󸶳� ��Ҵ��� �� �� �ִ� ����
	int calculateCount; // ���� �ǿ� ī�带 ������ �� ī�� ���� ���ڰ� �ִ��� �̸� üũ�ϴ� ī��Ʈ

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

