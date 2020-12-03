#pragma once
#include "pch.h"

class Animation
{
protected:
	vector<POINT> vecFramelist;		// key frame ��ġ ����Ʈ
	vector<int> vecPlayList;		// �÷��� ����Ʈ
	
	int frameCount;					// ��ü ������ ��
	int frameWidth;					// ������ ����ũ��
	int frameHeight;				// ������ ����ũ��

	bool isLoop;					// �ݺ� �Ǵ��� ����
	int nowPlayIdx;					// ���� �÷��� ������ �ε���
	bool isPlaying;					// ���� �÷��� ������ ����

	float keyFrameUpdateTime;		// ������Ʈ ���� �ð�
	float accumulateTime;			// �����ð�

public:
	Animation();
	virtual ~Animation();

	HRESULT Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);
	virtual void SetPlayFrame(bool isReverse = FALSE, bool isLoop = FALSE);
	virtual void SetPlayFrame(int startFrame, int endFrame, bool isReverse = FALSE, bool isLoop = FALSE);
	virtual void SetPlayFrame(int* arr, int arrlength, BOOL isReverse = FALSE, BOOL isLoop = FALSE);
	virtual void UpdateKeyFrame(float dt)=0;

	
	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; }

	POINT GetFramePos() { return vecFramelist[vecPlayList[nowPlayIdx]]; }

	void Start();
	void Stop();
	void Pause();
	void Resume();


};

class DefaultAnimation : public Animation
{
public:

	virtual void UpdateKeyFrame(float dt) override;

	DefaultAnimation();
	virtual ~DefaultAnimation();
};

class FrameAnimation : public Animation
{
public:

	virtual void UpdateKeyFrame(float dt) override;

	FrameAnimation();
	virtual ~FrameAnimation();
};

class ArrAnimation : public Animation
{
public:
	
	virtual void UpdateKeyFrame(float dt) override;

	ArrAnimation();
	virtual ~ArrAnimation();

};


