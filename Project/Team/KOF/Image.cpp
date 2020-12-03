#include "Image.h"
#include "pch.h"

HRESULT Image::Init(int width, int height)
{
	// 윈도우를 담당하는 핸들을 가져와 사용
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	// 비트맵을 담당할 데이터 dc를 만들어준다.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	imageInfo->hBitMap = CreateCompatibleBitmap(hdc, width, height);
	// hMemDc와 hBitMap을 연결해준다. 리턴되어 이미지 인포 hOldBit가 받아준다.
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;	imageInfo->height = height;
	
	// 위에서 만들었던 HDC를 해제
	ReleaseDC(g_hWnd, hdc);

	// hBitMap 와 hOldBit를 삭제해주는 과정이 있다.
	// 핸들 값은 숫자가 들어가있으면 정상 DC가 섞인 주소가 있으면 비정상

	// 경로에 있는 파일을 로드 했는데 NULL이면 로드가 안된 것이다.
	if (imageInfo->hBitMap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	// 이 함수를 통해 메모리에 올리는 과정을 만든다.

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	// 윈도우를 담당하는 핸들을 가져와 사용
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	// 비트맵을 담당할 데이터 DC를 만들어준다.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	// 첫번째 매개변수로 인스턴스 핸들 HBITMAP으로 형변환
	imageInfo->hBitMap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	// hMemDc와 hBitMap을 연결해준다. 리턴되어 이미지 인포 hOldBit가 받아준다.
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;

	// 위에서 만들었던 HDC를 해제
	ReleaseDC(g_hWnd, hdc);

	// hBitMap와 hOldBit를 삭제해주는 과정이 있다.
	// 핸들 값은 숫자가 들어가있으면 정상 DC가 섞인 주소가 있으면 비정상

	// 경로에 있는 파일을 로드했는데 NULL이면 로드가 안된 것이다.
	if (imageInfo->hBitMap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	// 비트맵을 담당할 데이터 DC를 만들어준다.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	// 첫번째 매개변수로 인스턴스 핸들 HBITMAP으로 형변환
	imageInfo->hBitMap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;		imageInfo->height = height;
	
	// 추가
	imageInfo->x = x - (width / 2);					imageInfo->y = y - (height / 2);
	imageInfo->curKeyFrameX = 0;					imageInfo->curKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;		imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;	imageInfo->keyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;

	// 위에서 만들었던 HDC를 해제
	ReleaseDC(g_hWnd, hdc);

	// hBitMap, hOldBit를 삭제해주는 과정이 있다.
	// 핸들 값은 숫자가 들어가있으면 정상 DC가 섞인 주소가 있으면 비정상
	
	// 경로에 있는 파일을 로드했는데 NULL이면 로드가 안된 것이다.
	if (imageInfo->hBitMap == NULL)
	{
		// 메모리 해제
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		// 2개 정보를 연결
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitMap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
		GdiTransparentBlt(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDc, 0, 0, imageInfo->width, imageInfo->height, transColor);

	else // 트랜스 컬러를 제외하고 복사하라
		// 메모리에 있는 데이터를 화면에 고속 복사한다.
		// HDC 목적지
		// dust 복사될 시작좌표
		// imageInfo 원본에서 복사될 가로, 세로 크기
		// DC 0, 0 원본에서 복사 시작 위치 
		// STRCPY -> 복사 옵션
		BitBlt(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDc, 0, 0, SRCCOPY);
		//BitBlt(hdc, destX, destY, 458, 645, imageInfo->hMemDc, 669, 62, SRCCOPY);
}

void Image::FrameRender(HDC hdc, int destX, int destY, int curKeyFrameX, int curKeyFrameY, float scale)
{
	// 현재 키프레임 인덱스가 최대 키프레임 인덱스보다 클 때
	imageInfo->curKeyFrameX = curKeyFrameX;
	imageInfo->curKeyFrameY = curKeyFrameY;

	// 예외처리
	if (imageInfo->curKeyFrameX > imageInfo->maxKeyFrameX)
		imageInfo->curKeyFrameX = imageInfo->maxKeyFrameX;
	
	if (imageInfo->curKeyFrameY > imageInfo->maxKeyFrameY)
		imageInfo->curKeyFrameY = imageInfo->maxKeyFrameY;

	if (isTrans)
	{
		GdiTransparentBlt(hdc,
			destX, destY,
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,
			imageInfo->hMemDc,
			imageInfo->keyFrameWidth * imageInfo->curKeyFrameX, 
			imageInfo->keyFrameHeight * imageInfo->curKeyFrameY,
			imageInfo->keyFrameWidth, 
			imageInfo->keyFrameHeight,
			transColor);
	}

	else // 트랜스 컬러를 제외하고 복사하라
		BitBlt(hdc, destX, destY, 
			imageInfo->keyFrameWidth, 
			imageInfo->keyFrameHeight, 
			imageInfo->hMemDc,
			imageInfo->keyFrameWidth * imageInfo->curKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->curKeyFrameY, 
			SRCCOPY);
}

HDC Image::GetMemDc() { return imageInfo->hMemDc; }

Image::Image()
{
}

Image::~Image()
{
}
