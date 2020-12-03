#pragma once
#include "GameNode.h"

class Image;
class SpaceShip : public GameNode
{
private:
	Image* image;
	float angle;
	float moveSpeed;

	double rotateAngle;

public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	SpaceShip();
	~SpaceShip();
};

