#pragma once

#include <Windows.h>

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		RESOURCE,	// ���ҽ� ���Ͽ��� �����´�.
		FILE,		// �ܺ� ������ �ε��ؼ� �޸� ����
		EMPTY,		// ����ִ� ��Ʈ�� ������ �ϳ� ����� ��
		END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;							// ���ҽ��� ������ ���̵�
		HDC		hMemDc;							// �׸��⸦ �ְ��ϴ� �ڵ� �޸�DC �޸� ������ �ϸ� ��Ʈ�� ������ ������.
		HBITMAP hBitMap;						// �̹��� ���� �ȼ�����
		HBITMAP hOldBit;						// ���� �̹��� ����
		int		width, height;					// �̹��� ����, ���� ũ��
		BYTE	loadType;						// �ε� Ÿ��
		float	x, y;							// ��� ��ġ ��ǥ
		int		curKeyFrameX, curKeyFrameY;		// ���� Ű������ �ε���
		int		maxKeyFrameX, maxKeyFrameY;		// �ִ� Ű������ ��
		int		keyFrameWidth, keyFrameHeight;	// Ű �����Ӵ� ũ��
		
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
	IMAGE_INFO * imageInfo;		// �̹��� ������ ���� ����ü ������
	char * fileName;			// ���ϰ�� + �̸�
	bool isTrans;				// ����ȭ ����
	COLORREF transColor;		// ����ȭ�� ��

public:
	// �� ��Ʈ�� �̹����� �����.
	HRESULT Init(int width, int height);

	/* ���ҽ� ���Ͽ� ��Ʈ�� ������ �߰����� �پ��� �̹����� ���⿡ �ִ´� �� �뷮�� Ŀ����.
	   exe ���� ��ü�� Ŀ���� ������ �� ���� ���� ���� �� */
	HRESULT Init(const DWORD resID, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// ���Ϸκ��� �����͸� �о �����.
	HRESULT Init(const char * fileName, int width, int height, bool trans = FALSE, COLORREF transColor = FALSE);

	// �̹��� + Ű ������ �ʱ�ȭ
	HRESULT Init(const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans = FALSE, COLORREF transColor = FALSE);

	void Release();
	void Render(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int curKeyFrameX, int curKeyFrameY, float scale = 1.0f);

	HDC GetMemDc();

	Image();
	~Image();
};