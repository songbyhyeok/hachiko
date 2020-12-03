
#include "MainGame.h"
#include "pch.h"

// 전역변수
HINSTANCE	g_hInstance;	// 프로그램 인스턴스 핸들
HWND		g_hWnd;			// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("Enter the Gungeon");
HCURSOR		hCursor;
POINT		g_ptMouse;
MainGame	mainGame;

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
	wndClass.hCursor = LoadCursor(NULL, NULL);
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

	mainGame.Release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}