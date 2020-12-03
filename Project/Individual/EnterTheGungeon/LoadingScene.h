#pragma once

#include "GameNode.h"

class Animation;
class LoadingScene : public GameNode
{
private:
	Image* bg;
	Animation* ani;
public:

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	LoadingScene();
	~LoadingScene();
};

