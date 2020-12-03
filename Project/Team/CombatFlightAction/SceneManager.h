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
	int nY;			// stage화면 이동컨트롤 변수

public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

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

