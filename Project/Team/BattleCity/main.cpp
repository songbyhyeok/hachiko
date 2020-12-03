// main.cpp

/*
	Win32 API
	: Application Programing Interface
	운영체제가 응용프로그램을 위해 제공하는 함수의 집합

	하드웨어 ----------운영체제(Windows)-------- 응용프로그램
						(API 함수)

	핸들(Handle)
	메시지(Message)
*/

#include "pch.h"
#include <Windows.h>
#include "MainGame.h"

// 전역변수
HINSTANCE	g_hInstance;	// 프로그램 인스턴스 핸들
HWND		g_hWnd;			// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("BattleCity");

POINT		g_ptMouse;
MainGame mainGame;

void SetWindowSize(int x, int y, int width, int height);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// 윈도우를 생성하기 위한 함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
		LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우 생성을 위한 기본셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X, WINSTART_Y,
		WINSIZE_X, WINSIZE_Y,
		NULL,
		NULL,
		g_hInstance,
		NULL);

	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 윈도우 작업영역 설정
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	// 메인게임 초기화
	if (mainGame.Init())
	{
		return 0;
	}

	// 메시지 큐에 있는 메시지 처리
	MSG message;

	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimeManager::GetSingleton()->Update(FPS);

			mainGame.Update();
			mainGame.Render();
		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	// 해제
	mainGame.Release();

	return message.wParam;
}


//void SetWindowSize(int x, int y, int width, int height)
//{
//	// 윈도우 작업영역 지정
//	RECT rc;
//	rc.left = 0; rc.top = 0;
//	rc.right = width; rc.bottom = height;
//
//	// 실제 윈도우 크기 받아온다.
//	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
//
//	// 이동
//	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}