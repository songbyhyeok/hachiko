#include "SoundManager.h"

HRESULT SoundManager::Init()
{
	// 사운드 시스템 생성
	System_Create(&system);

	//채널 설정
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel*[TOTALSOUNDBUFFER];

	memset(sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	return S_OK;
}

void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channel);

	system->close();
	system->release();
}

void SoundManager::Update()
{
	if (system)
		system->update();
}

void SoundManager::AddSound(string key, string filePath, bool isBGM, bool isLoop)
{
	if (isLoop)
	{
		if (isBGM)
		{
			system->createStream(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]); // bgm일 경우 이걸로 파일을 만듬(파일 크기가 큰 애들)
		}

		else
		{
			system->createSound(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]); //이펙트 음이나 루프가 별로 없는 애들일 경우 이걸로
		}
	}

	else
	{
		system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound[mapSoundDatas.size()]); //이펙트 음이나 루프가 별로 없는 애들일 경우 이걸로
	}

	mapSoundDatas.insert(make_pair(key, &sound[mapSoundDatas.size()])); //애를 사용하는 시점에서는 &sound[mapSoundDatas.size()]가 0이었다가 insert되면 1로 바뀜
}

void SoundManager::Play(string key, float volume)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (key == it->first)
		{
			system->playSound(FMOD_CHANNEL_FREE, (*mapSoundDatas[key]), false, &channel[count]);
			channel[count]->setVolume(volume);

			break;
		}

		
	}
}

void SoundManager::Stop(string key)
{
	map<string, Sound**>::iterator it;

	int count = 0;
	
	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->stop();

			break;
		}
	}
}

void SoundManager::Pause(string key)
{
	map<string, Sound**>::iterator it;

	int count = 0;
	
	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(true);

			break;
		}
	}
}

void SoundManager::Resume(string key)
{
	map<string, Sound**>::iterator it;

	int count = 0;
	
	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(false);

			break;
		}
	}
}

void SoundManager::VolumeUp(string key, float volume)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setVolume(volume);


			break;
		}
	}
}

SoundManager::SoundManager()
	:system(nullptr), sound(nullptr), channel(nullptr)
{
}

SoundManager::~SoundManager()
{
}
