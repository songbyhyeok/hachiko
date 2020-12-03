#pragma once

#include <Windows.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <list>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"


// enum, struct, .h, #define


enum TERRAIN
{
	EMPTY,
	BRICK,
	CONCRETE,
	GRASS,
	WATER,
	ICE,
	EAGLE,
	USERTANK,
	ENEMYTANK1,
	ENEMYTANK2,
	ENEMYTANK3,
};

enum BOX
{
	BOX_First,
	BOX_Second,
	BOX_End
};

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagArgumnets
{
	const char* sceneName;
	const char* loadingName;
} ARGUMENT_INFO;

typedef struct battletagTile
{
	TERRAIN terrain;
	TERRAIN objterrain;
	RECT rcTile;
	int frameX;
	int frameY;
	int objframeX;
	int objframeY;

}BATTLE_TILE_INFO;


#define TILESIZE		30 //	Ÿ�� �ϳ��� ������
#define SAMPLE_TILE_X		7 //	���� Ÿ���� ����
#define SAMPLE_TILE_Y		1  //	���� Ÿ���� ����
#define OBJECT_TILE_X		12 //	���� Ÿ���� ����
#define OBJECT_TILE_Y		2  //	���� Ÿ���� ����

#define TILE_X			26 //	���� Ÿ���� ����
#define TILE_Y			26 //	���� Ÿ���� ����


#define FPS			30.0f
#define WINSIZE_X	600
#define WINSIZE_Y	780
#define WINSTART_X	50
#define WINSTART_Y	50

#define WINSIZE_TILE_MAP_X 1400
#define WINSIZE_TILE_MAP_Y 780
#define WINSIZE_BATTLE_MAP_X 880
#define WINSIZE_BATTLE_MAP_Y 780

#define PI			3.141592

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define DEGREE_TO_RADIAN(x)	( x * PI / 180 )
#define RADIAN_TO_DEGREE(x) (int)( x * 180 / PI )

#define TANKUP 0
#define TANKDOWN 4
#define TANKLEFT 2
#define TANKRIGHT 6

#define DEFAULTTANKNUM 4
#define SPEEDTANKNUM 3
#define POWERTANKNUM 2

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

#include "macroFunction.h"

