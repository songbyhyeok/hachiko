#include "Image.h"

#pragma comment (lib, "msimg32.lib")

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	// Blend
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	return E_NOTIMPL;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;

	// Blend
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// �޸� ����
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

HRESULT Image::Init(const char * fileName,
	float x, float y, int width, int height,
	int keyFrameX, int keyFrameY,
	bool trans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName,
		IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(
		imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	// �߰�
	imageInfo->x = x - (width / 2);
	imageInfo->y = y - (height / 2);
	imageInfo->currentKeyFrameX = 0;
	imageInfo->currentKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;
	imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;
	imageInfo->keyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;

	// Blend
	int maxSize = imageInfo->keyFrameWidth > imageInfo->keyFrameHeight ? imageInfo->keyFrameWidth : imageInfo->keyFrameHeight;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize);
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hBlendBitmap == NULL
		|| imageInfo->hRotateBitmap == NULL)
	{
		// �޸� ����
		Release();
		return E_FAIL;
	}

	blendFunc.AlphaFormat = 0;
	blendFunc.BlendFlags = 0;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = 0;

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);

		// Blend
		SelectObject(imageInfo->hBlendDC, imageInfo->hBlendOldBit);
		DeleteObject(imageInfo->hBlendBitmap);
		DeleteDC(imageInfo->hBlendDC);

		// Rotate


		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}
	else
	{
		// �޸𸮿� �ִ� �����͸� ȭ�鿡 ��Ӻ����Ѵ�.
		BitBlt(hdc,				// ���� ������ DC
			destX, destY,		// ���� ���� ��ġ
			imageInfo->width,	// �������� ����� ���� ũ��
			imageInfo->height,	// �������� ����� ���� ũ��
			imageInfo->hMemDC,	// ���� DC
			0, 0,				// �������� ���� ���� ��ġ
			SRCCOPY);			// ���� �ɼ�
	}

}

void Image::FrameRender(HDC hdc, int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY, float scale/* = 1.0f*/)
{
	// ���� Ű������ �ε����� �ִ� Ű������ �ε������� Ŭ ��
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	if (isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth / 2),
			destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);
	}
	else
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
	}

}

void Image::FrameRotateAlphaRender(HDC hdc, double dblAngle,
	int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY,
	BYTE alpha, double dblSizeRatio,
	HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// ���� Ű������ �ε����� �ִ� Ű������ �ε������� Ŭ ��
	imageInfo->currentKeyFrameX = currentKeyFrameX;
	imageInfo->currentKeyFrameY = currentKeyFrameY;

	if (imageInfo->currentKeyFrameX > imageInfo->maxKeyFrameX)
	{
		imageInfo->currentKeyFrameX = imageInfo->maxKeyFrameX;
	}
	if (imageInfo->currentKeyFrameY > imageInfo->maxKeyFrameY)
	{
		imageInfo->currentKeyFrameY = imageInfo->maxKeyFrameY;
	}

	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2),
			SRCCOPY);

		// 2. �̹����� ȸ�����Ѽ� Rotate DC�� ����
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateFrameRender(imageInfo->hRotateDC, dblAngle, imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);

		// 3. Rotate DC �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,

			imageInfo->hRotateDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, transColor);

		// 4. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->rotateMaxSize / 2), destY - (imageInfo->rotateMaxSize / 2),
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			imageInfo->hBlendDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			blendFunc);
	}

	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, BYTE alpha)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height, transColor);

		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			0, 0, imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{


	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc, destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);

		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height, imageInfo->hMemDC,
			0, 0, imageInfo->width, imageInfo->height, transColor);

		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc, destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height, blendFunc);
	}
}

void Image::RotateRender(HDC hdc, double dblAngle, int destX, int destY, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->width * dblSizeRatio;
	double dblHeight = (double)imageInfo->height * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->width / 2) * dblSizeRatio);
	double iyRotate = (int)((double)(imageInfo->height / 2) * dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ�� ���� �������� ��� ��ǥ�� ���Ѵ�.
	// 2. ȸ���� ��ġ��ǥ (�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}

	PlgBlt(hdc, apt, imageInfo->hMemDC, 0, 0,
		imageInfo->width, imageInfo->height, hMaskBmp, ixMask, iyMask);
}

void Image::RotateFrameRender(HDC hdc, double dblAngle, int destX, int destY, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->keyFrameWidth * dblSizeRatio;
	double dblHeight = (double)imageInfo->keyFrameHeight * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->keyFrameWidth / 2) * dblSizeRatio);
	double iyRotate = (int)((double)(imageInfo->keyFrameHeight / 2) * dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ�� ���� �������� ��� ��ǥ�� ���Ѵ�.
	// 2. ȸ���� ��ġ��ǥ (�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
		dblxDest = dblx * cosVal - dbly * sinVal;
		dblyDest = dblx * sinVal + dbly * cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = destX - (long)ixRotate + (long)dblxDest;
		apt[i].y = destY - (long)iyRotate + (long)dblyDest;
	}

	PlgBlt(hdc, apt, imageInfo->hMemDC, 0, 0,
		imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, hMaskBmp, ixMask, iyMask);
}

void Image::RotateAlphaRender(HDC hdc, double dblAngle, int destX, int destY, BYTE alpha, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			hdc,
			destX - (imageInfo->rotateMaxSize / 2),
			destY - (imageInfo->rotateMaxSize / 2), SRCCOPY);

		// 2. �̹����� ȸ�����Ѽ� Rotate DC�� ����
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateRender(imageInfo->hRotateDC, dblAngle, imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);

		// 3. Rotate DC �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,

			imageInfo->hRotateDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize, transColor);

		// 4. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->rotateMaxSize / 2), destY - (imageInfo->rotateMaxSize / 2),
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			imageInfo->hBlendDC,
			0, 0,
			imageInfo->rotateMaxSize, imageInfo->rotateMaxSize,
			blendFunc);
	}

	else
	{
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::MapRender(HDC hdc, int nY)
{
	if (nY < 0)
	{
		BitBlt(hdc, 0, -nY, WINSIZE_X, WINSIZE_Y + nY, imageInfo->hMemDC, 0, 0, SRCCOPY); // �ʱ� ȭ�� ��ũ��
		BitBlt(hdc, 0, 0, WINSIZE_X, -nY, imageInfo->hMemDC, 0, WINSIZE_Y + nY, SRCCOPY); //���� �������� ���
	}
	else
	{
		BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, imageInfo->hMemDC, 0, nY, SRCCOPY);
	}
}

Image::Image()
{
}


Image::~Image()
{
}
