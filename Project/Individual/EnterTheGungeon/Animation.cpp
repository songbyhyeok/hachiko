#include "Animation.h"

Animation::Animation()
	: frameCount(0)				// 전체 프레임 수
	, frameWidth(0)					// 프레임 가로크기
	, frameHeight(0)			// 프레임 세로크기
	, isLoop(FALSE)					// 반복 되는지 여부
	, nowPlayIdx(0)					// 현재 플레이 프레임 인덱스
	, isPlaying(false)					// 현재 플레이 중인지 여부
	, keyFrameUpdateTime(0.0f)
	, accumulateTime(0.0f)
{
}

Animation::~Animation()
{
}

HRESULT Animation::Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight)
{
	// 가로 프레임 수
	int frameWidthCount = totalWidth / frameWidth;
	// 세로 프레임 수
	int frameHeightCount = totalHeight / frameHeight;
	// 전체 프레임 수
	frameCount = frameWidthCount * frameHeightCount;
	// 프레임 위치 리스트 셋팅
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
				// 루프일 때
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
