#pragma once
#include "GameNode.h"
#include "pch.h"
/*

�Լ������� (�Լ��� �ּҸ� ��� ����)
������ (������ �ּҸ� ��� ����)
int a = 10;
int* pA = &a;

int sum(int a, int b);
����Ÿ�� (*�Լ��������̸�) (�Ű�����1�� Ÿ��, �Ű�����2�� Ÿ��);
int (*calculatePointer)(int, int);

void func(void);			// �Լ��� ������ ����
void (*funcPointer)(void);	// �Լ�������(����)�� ����  
funcPointer = func;			// �Լ������Ϳ� �Լ��� �ּҸ� ����

func();
funcPointer();				// == func();

void makeRect(void);
funcPointer = makeRect;
funcPointer();				// == makeRect();

*/



enum BUTTON_STATE
{
	NONE,
	UP,
	DOWN
};

class Image;
class TitleScene;
class ChangeScene;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* image;
	RECT rc;

	POINT btnDownFramePoint;
	POINT btnUpFramePoint;
	
	ChangeScene* changescene;
	
	// ��ư ������ ���� �Լ� (�Լ�������)
	void(ChangeScene::*buttonFunc)(const char*, const char*);
	
	//HRESULT(*buttonFunc)(string, string);
	ARGUMENT_INFO* args;

public:

	HRESULT Init(const char* imageName, int posX, int posY, POINT downFramePoint, POINT upFramePoint);

	void SetButtonFunc(ChangeScene* ch, void(ChangeScene::* buttonFunc)(const char *, const char *), ARGUMENT_INFO * args);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetState(BUTTON_STATE _state) { state = _state; }
	void SetbtnUpFramePoint(POINT btnupframepoint) { btnUpFramePoint = btnupframepoint; }
	void SetbtnDownFramePoint(POINT btndownframepoint) { btnDownFramePoint = btndownframepoint; }

	Button();
	virtual ~Button();
};

