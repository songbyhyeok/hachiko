#pragma once

#include <Windows.h>
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <ctime>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

#define FPS			30.0f

#define WINSTART_X	50
#define WINSTART_Y	50
#define WINSIZE_X	1200
#define WINSIZE_Y	900

#define SAFE_DELETE(p)		{ if (p) { delete p; p = NULL; }}
#define SAFE_ARR_DELETE(p)	{ if (p) { delete [] p; p = NULL; }}

#define PI			3.141592
#define DEGREE_TO_RADIAN(x)	( x * (PI / 180) )
#define RADIAN_TO_DEGREE(x) ( x * (180 / PI) )

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern HCURSOR hCursor;
extern POINT g_ptMouse;

#include "macroFunction.h"



