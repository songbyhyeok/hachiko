#pragma once

#include <Windows.h>

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	// 리소스 파일에서 가져온다.
		FILE,		// 외부 파일을 로드해서 메모리 저장
		EMPTY,		// 비어있는 비트맵 공간을 하나 만드는 것
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;							// 리소스의 고유한 아이디
		HDC		hMemDc;							// 그리기를 주관하는 핸들 메모리DC 메모리 관리를 하며 비트맵 정보를 가진다.
		HBITMAP hBitMap;						// 이미지 정보 픽셀정보
		HBITMAP hOldBit;						// 기존 이미지 정보
		int		width, height;					// 이미지 가로, 세로 크기
		BYTE	loadType;						// 로드 타입
		float	x, y;							// 출력 위치 좌표
		int		curKeyFrameX, curKeyFrameY;		// 현재 키프레임 인덱스
		int		maxKeyFrameX, maxKeyFrameY;		// 최대 키프레임 수
		int		keyFrameWidth, keyFrameHeight;	// 키 프레임당 크기
		
		tagImageInfo()
		{
			resID		= 0;
			hMemDc		= NULL;
			hBitMap		= NULL;
			hOldBit		= NULL;
			width = 0, height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			x = 0.0f;			y = 0.0f;
			curKeyFrameX  = 0,	curKeyFrameY	= 0;
			maxKeyFrameX  = 0,	maxKeyFrameY	= 0;
			keyFrameWidth = 0;	keyFrameHeight  = 0;
		}
	} IMAGE_INFO, *PIMAGE_INFO;

private:
	IMAGE_INFO * imageInfo;		// 이미지 정보에 대한 구조체 포인터
	char * fileName;			// 파일경로 + 이름
	bool isTrans;				// 투명화 여부
	COLORREF transColor;		// 투명화할 색

public:
	// 빈 비트맵 이미지를 만든다.
	HRESULT Init(int width, int height);

	/* 리소스 파일에 비트맵 파일을 추가가능 다양한 이미지를 여기에 넣는다 단 용량이 커진다.
	   exe 파일 자체가 커지기 때문에 쓸 일이 별루 없을 것 */
	HRESULT Init(const DWORD resID, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// 파일로부터 데이터를 읽어서 만든다.
	HRESULT Init(const char * fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// 이미지 + 키 프레임 초기화
	HRESULT Init(const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans = FALSE, COLORREF transColor = FALSE);

	void Release();
	void Render(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int curKeyFrameX, int curKeyFrameY, float scale = 1.0f);

	HDC GetMemDc();

	Image();
	~Image();
};