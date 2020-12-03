#pragma once
#include "pch.h"

class Animation
{
protected:
	vector<POINT> vecFramelist;		// key frame 위치 리스트
	vector<int> vecPlayList;		// 플레이 리스트
	
	int frameCount;					// 전체 프레임 수
	int frameWidth;					// 프레임 가로크기
	int frameHeight;				// 프레임 세로크기

	bool isLoop;					// 반복 되는지 여부
	int nowPlayIdx;					// 현재 플레이 프레임 인덱스
	bool isPlaying;					// 현재 플레이 중인지 여부

	float keyFrameUpdateTime;		// 업데이트 기준 시간
	float accumulateTime;			// 누적시간

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


