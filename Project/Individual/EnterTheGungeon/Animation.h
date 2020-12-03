#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

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
	virtual void SetPlayFrame(int* arr, int arrlength, BOOL isLoop = TRUE);
	virtual void UpdateKeyFrame(float dt) = 0;

	void SetUpdateTime(int fps) { keyFrameUpdateTime = 1.0f / fps; }

	POINT GetFramePos() { return vecFramelist[vecPlayList[nowPlayIdx]]; }

	void SetNowPlayIdx(int idx);
	int GetNowPlayIdx();

	void Start();
	void Stop();
	void Pause();
	void Resume();
};

class ArrAnimation : public Animation
{
public:
	virtual void UpdateKeyFrame(float dt) override;

	ArrAnimation();
	virtual ~ArrAnimation();
};