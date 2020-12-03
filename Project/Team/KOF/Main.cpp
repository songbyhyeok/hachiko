#include "MainGame.h"

HINSTANCE g_hInstance;
//핸들 + 인스턴스로 구성된 이름 인스턴스 핸들을 저장할 때 사용
//'Instance Handle'은 윈도우즈 운영체제에서 실행되는 프로그램들을 구별하기 위한 ID 값입니다. 
//이 값은 정수이고 프로그램을 구별하기 위한 값이기 때문에 동일한 프로그램을 여러 개 실행한 경우에는 같은 값을 가지게 됩니다.
HWND	g_hWnd;	//윈도우 핸들
LPSTR	g_lpszClass = (LPSTR)TEXT("WIN MAIN START");

MainGame mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void SetWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 50, 50, WIN_SIZE_X, WIN_SIZE_Y, NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);
	SetWindowSize(WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);

	if (mainGame.Init())	// 메인게임 초기화
		return 0;

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	mainGame.Release();	// 해제

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int x, int y, int width, int height)
{
	// 윈도우 작업영역 지정
	RECT _Rc;
	_Rc.left = 0;	_Rc.top = 0;
	_Rc.right = width;	_Rc.bottom = height;

	// 실제 윈도우 크기 받아온다.
	AdjustWindowRect(&_Rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, x, y, _Rc.right - _Rc.left, _Rc.bottom - _Rc.top, true);
}