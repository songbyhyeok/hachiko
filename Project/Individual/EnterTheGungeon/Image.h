#pragma once
#include "pch.h"

class Animation;
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE, FILE, EMPTY, END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;		// 리소스의 고유한 아이디
		HDC		hMemDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hBitmap;	// 이미지 정보
		HBITMAP hOldBit;	// 기존 이미지 정보
		int		width;		// 이미지 가로 크기
		int		height;		// 이미지 세로 크기
		BYTE	loadType;	// 로드 타입

		HDC		hTempDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hTempBitmap;	// 이미지 정보
		HBITMAP hTempOldBit;	// 기존 이미지 정보

		HDC		hBlendDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hBlendBitmap;	// 이미지 정보
		HBITMAP hBlendOldBit;	// 기존 이미지 정보

		HDC		hRotateDC;		// 그리기를 주관하는 핸들(메모리 관리)
		HBITMAP	hRotateBitmap;	// 이미지 정보
		HBITMAP hRotateOldBit;	// 기존 이미지 정보
		int		rotateMaxSize;

		float	x, y;					// 출력 위치 좌표
		int		currentKeyFrameX, currentKeyFrameY;	// 현재 키프레임 인덱스
		int		maxKeyFrameX, maxKeyFrameY;		// 최대 키프레임 수
		int		keyFrameWidth, keyFrameHeight;		// 키프레임 당 크기

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;	height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			x = 0.0f;	y = 0.0f;
			currentKeyFrameX = 0;	currentKeyFrameY = 0;
			maxKeyFrameX = 0;	maxKeyFrameY = 0;
			keyFrameWidth = 0;	keyFrameHeight = 0;
			rotateMaxSize = 0;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;	// 이미지정보 구조체 포인터
	char* fileName;			// 파일 경로 + 이름
	bool isTrans;			// 투명화 여부
	COLORREF transColor;	// 투명화할 색

	BLENDFUNCTION	blendFunc;

public:
	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(int width, int height);

	// 리소스로부터 데이터를 읽어서 만든다.
	HRESULT Init(const DWORD resID, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 데이터를 읽어서 만든다.
	HRESULT Init(const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 키프레임 초기화
	HRESULT Init(const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	// 메모리 해제
	void Release();

	void Render(HDC hdc, int destX, int destY, bool reverse = false);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, bool _bitBlt = false, bool isReverse = false);
	void FrameRender(HDC hdc, int destX, int destY,
		int currentKeyFrameX, int currentKeyFrameY, bool reverse = false, bool reverse2 = false, float scale = 1.0f);

	// 알파 렌더
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, bool isReverse = false);

	// 회전
	void RotateRender(HDC hdc, double dblAngle,
		int destX, int destY, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	// 회전 & 알파
	void RotateAlphaRender(HDC hdc, double dblAngle,
		int destX, int destY, BYTE alpha = 255, double dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

	void AngleRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, double _dblAngle, BYTE alpha, bool _bitBlt, bool isReverse);

	// 애니메이션
	void AnimationRender(HDC hdc, int destX, int destY, Animation* ani, bool _bitBlt = false, bool isReverse = false);
	void AnimationAlphaRender(HDC hdc, int destX, int destY, Animation * ani, BYTE alpha, bool isReverse = false);
	void AniAngleRender(HDC hdc, int destX, int destY, Animation* ani, double _dblAngle, bool _bitBlt = false, bool isReverse = false);

	HDC GetMemDC();

	int GetMaxKeyFrameX();
	int GetMaxKeyFrameY();

	int GetWidth();
	int GetHeight();

	int GetFrameWidth();
	int GetFrameHeight();

	Image();
	~Image();
};

