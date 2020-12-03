#pragma once
#include "GameNode.h"

class Image;
class KofPlayer : public GameNode
{
private:
	float posX;
	float posY;
	Image* img;
	int currKeyFrameX;
	int currKeyFrameY;
	int elapsedFrame;
	float scale;

public:
	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }
	void SetScale(float scale) { this->scale = scale; }

	KofPlayer();
	~KofPlayer();
};

