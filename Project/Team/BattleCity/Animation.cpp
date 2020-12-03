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
			vecFramelist[i*frameWidthCount + j].x= j * frameWidth;
			vecFramelist[i*frameWidthCount + j].y = i * frameHeight;
		}
	}
	// 기본 플레이 리스트 셋팅
	//SetPlayFrame();

	return S_OK;
}

void Animation::SetPlayFrame(bool isReverse, bool isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}

		for (int i = frameCount - 1; i > 0; i--)
		{
			vecPlayList.push_back(i);
		}
	}

	else
	{
		//정방향
		for (int i = 0; i < frameCount; i++)
		{
			vecPlayList.push_back(i);
		}
	}

}

void Animation::SetPlayFrame(int startFrame, int endFrame, bool isReverse, bool isLoop)
{
	bool check;
	this->isLoop = isLoop;

	vecPlayList.clear();
	if (startFrame == endFrame)
	{
		Stop();
		return;
	}

	if (startFrame < endFrame)
	{
		check = true;
	}

	else
	{
		check = false;
	}
	//startFrame이 0보다 크거나 같고 endFrame이 마지막 frame보다 작거나 같을 때

	if (check)
	{
		if (isReverse)
		{
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}

			for (int i = endFrame - 1; i > startFrame; i--)
			{
				vecPlayList.push_back(i);
			}
		}

		else
		{
			//정방향
			for (int i = startFrame; i < endFrame + 1; i++)
			{
				vecPlayList.push_back(i);
			}
		}
	}
	//startFrame = 8 endFrame =3 인 경우
	else
	{
		if (isReverse)
		{
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
				if (i == (frameCount - 1))
				{
					for (int j = 0; j < endFrame; j++)
					{
						vecPlayList.push_back(j);
					}
				}
			}

			for (int i = endFrame; i >= 0; i--)
			{
				vecPlayList.push_back(i);
				if (i == 0)
				{
					for (int j = frameCount - 1; j > startFrame; j--)
					{
						vecPlayList.push_back(j);
					}
				}
			}


		}

		else
		{
			//정방향
			for (int i = startFrame; i < frameCount; i++)
			{
				vecPlayList.push_back(i);
				if (i == (frameCount - 1))
				{
					for (int j = 0; j < endFrame + 1; j++)
					{
						vecPlayList.push_back(j);
					}
				}
			}
		}
	}

}

void Animation::SetPlayFrame(int * arr, int arrlength, BOOL isReverse, BOOL isLoop)
{
	this->isLoop = isLoop;

	vecPlayList.clear();

	if (isReverse)
	{
		for (int i = 0; i < arrlength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}

		for (int i = arrlength - 1; i >= 0; i--)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrlength; i++)
		{
			vecPlayList.push_back(arr[i]);
		}
	}
}

void Animation::UpdateKeyFrame(float dt)
{
	
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

void DefaultAnimation::UpdateKeyFrame(float dt)
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

DefaultAnimation::DefaultAnimation()
{
}

DefaultAnimation::~DefaultAnimation()
{
}

void FrameAnimation::UpdateKeyFrame(float dt)
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

FrameAnimation::FrameAnimation()
{
}

FrameAnimation::~FrameAnimation()
{
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
