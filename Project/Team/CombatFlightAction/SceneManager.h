#pragma once

#include "GameNode.h"

class PlayerManager;
class EnemyManager;
class UI;

class SceneManager : public GameNode
{
private:
	enum tagSceneName
	{
		INTRO, SELECT, SCENE1, SCENE2, SCENE3, END
	};

	Image * bg;
	Image * stage1;
	Image * stage2;
	Image * stage3;
	Image * isEnd;
	Image * back;

	PlayerManager * playerMgr;
	EnemyManager * enemyMgr;
	
	UI * isUI;

	int gameScene;
	int nY;			// stageȭ�� �̵���Ʈ�� ����

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void IntroScene();
	void SelectScene();
	void PlayScene();
	void Scene1();
	void Scene2();
	void Scene3();
	void EndScene();

	void SetMgr(PlayerManager * _playerMgr, EnemyManager* _enemyMgr, UI * _isUI);

	SceneManager();
	~SceneManager();

};

