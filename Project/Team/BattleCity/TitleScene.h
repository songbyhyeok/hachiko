#pragma once
#include "GameNode.h"
class Button;
class ChangeScene;
class TitleScene : public GameNode
{
private:
	Image* bg;

	Button* button1;
	Button* button2;
	ARGUMENT_INFO* args;
	ARGUMENT_INFO* args1;

	ChangeScene* changescene;

	int curFrameX;
public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	

	TitleScene();
	~TitleScene();
};

