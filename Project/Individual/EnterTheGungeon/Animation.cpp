#include "Animation.h"

Animation::Animation()
	: frameCount(0)				// ��ü ������ ��
	, frameWidth(0)					// ������ ����ũ��
	, frameHeight(0)			// ������ ����ũ��
	, isLoop(FALSE)					// �ݺ� �Ǵ��� ����
	, nowPlayIdx(0)					// ���� �÷��� ������ �ε���
	, isPlaying(false)					// ���� �÷��� ������ ����
	, keyFrameUpdateTime(0.0f)
	, accumulateTime(0.0f)
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight)
{
	// ���� ������ ��
	int frameWidthCount = totalWidth / frameWidth;
	// ���� ������ ��
	int frameHeightCount = totalHeight / frameHeight;
	// ��ü ������ ��
	frameCount = frameWidthCount * frameHeightCount;
	// ������ ��ġ ����Ʈ ����
	vecFramelist.clear();
	vecFramelist.resize(frameCount);

	for (int i = 0; i < frameHeightCount; i++)
	{
		for (int j = 0; j < frameWidthCount; j++)
		{
			vecFramelist[i*frameWidthCount + j].x = j * frameWidth;
			vecFramelist[i*frameWidthCount + j].y = i * frameHeight;
		}
	}

	return S_OK;
}

void Animation::SetPlayFrame(int * arr, int arrlength, BOOL isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	for (int i = 0; i < arrlength; i++)
	{
		vecPlayList.push_back(arr[i]);
	}
}

void Animation::UpdateKeyFrame(float dt)
{

}

void Animation::SetNowPlayIdx(int idx)
{
	nowPlayIdx = idx;
}

int Animation::GetNowPlayIdx()
{
	return nowPlayIdx;
}

void Animation::Start()
{
	nowPlayIdx = 0;
	isPlaying = true;
}

void Animation::Stop()
{
	nowPlayIdx = 0;
	isPlaying = false;
}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Resume()
{
	isPlaying = true;
}

void ArrAnimation::UpdateKeyFrame(float dt)
{
	if (isPlaying)
	{
		accumulateTime += dt;

		if (accumulateTime >= keyFrameUpdateTime)
		{
			nowPlayIdx++;

			if (nowPlayIdx >= vecPlayList.size())
			{
				// ������ ��
				if (isLoop)
				{
					nowPlayIdx = 0;
				}
				else
				{
					nowPlayIdx--;
					isPlaying = false;
				}
			}
			accumulateTime -= keyFrameUpdateTime;
		}
	}
}

ArrAnimation::ArrAnimation()
{
}

ArrAnimation::~ArrAnimation()
{
}
