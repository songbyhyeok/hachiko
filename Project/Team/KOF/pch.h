#pragma once

#include <Windows.h>
#include <ctime>
#include "KeyManager.h"
#include "MacroFunction.h"
#include "Image.h"

#define WIN_START_X		50
#define WIN_START_Y		50
#define WIN_SIZE_X		1500
#define WIN_SIZE_Y		447
#define NAME_SIZE		20

typedef struct tagFPOINT
{
	float x, y;
}FPOINT, *PFPOINT;

typedef struct tagCollisionBox
{
	RECT body;
	RECT leg;
	RECT hit;
	RECT defence;
}CRECT, *PCRECT;

typedef struct tagCharInf
{
	Image * motion;
	CRECT hitBox;
	int adjustHeight;
	int curKeyFrame;
	int maxKeyFrame;
	bool moveMent;
}CHARINF;

extern HWND			g_hWnd;
extern HINSTANCE	g_hInstance;

