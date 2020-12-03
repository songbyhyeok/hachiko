#include "MainGame.h"

HINSTANCE g_hInstance;
//�ڵ� + �ν��Ͻ��� ������ �̸� �ν��Ͻ� �ڵ��� ������ �� ���
//'Instance Handle'�� �������� �ü������ ����Ǵ� ���α׷����� �����ϱ� ���� ID ���Դϴ�. 
//�� ���� �����̰� ���α׷��� �����ϱ� ���� ���̱� ������ ������ ���α׷��� ���� �� ������ ��쿡�� ���� ���� ������ �˴ϴ�.
HWND	g_hWnd;	//������ �ڵ�
LPSTR	g_lpszClass = (LPSTR)TEXT("WIN MAIN START");

MainGame mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void SetWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;	// ������ ���� �޸�
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

	if (mainGame.Init())	// ���ΰ��� �ʱ�ȭ
		return 0;

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	mainGame.Release();	// ����

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int x, int y, int width, int height)
{
	// ������ �۾����� ����
	RECT _Rc;
	_Rc.left = 0;	_Rc.top = 0;
	_Rc.right = width;	_Rc.bottom = height;

	// ���� ������ ũ�� �޾ƿ´�.
	AdjustWindowRect(&_Rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, x, y, _Rc.right - _Rc.left, _Rc.bottom - _Rc.top, true);
}