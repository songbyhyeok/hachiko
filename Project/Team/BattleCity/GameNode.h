#pragma once
#include "pch.h"

class GameNode
{
protected:
	
	FPOINT pos ;
public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	FPOINT GetPos() { return pos; }

	GameNode();
	~GameNode();
};

