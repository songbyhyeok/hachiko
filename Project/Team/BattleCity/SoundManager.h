#pragma once
#include "pch.h"
#include "SingletonBase.h"

// FMOD ฐüทร
#include "inc\fmod.hpp"
#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER		10
#define EXTRACHANNELBUFFER	5
#define TOTALSOUNDBUFFER	SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:
	FMOD::System*	system;
	Sound**			sound;
	Channel**		channel;

	map<string, Sound**>	mapSoundDatas;

public:
	HRESULT Init();
	void Release();
	void Update();

	void AddSound(string key, string filePath, bool isBGM = false, bool isLoop = false);
	void Play(string key, float volume = 1.0f);		// 0.0f ~ 1.0f
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	SoundManager();
	~SoundManager();
};

