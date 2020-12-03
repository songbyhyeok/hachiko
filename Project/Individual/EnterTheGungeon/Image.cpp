#include "Image.h"
#include "Animation.h"

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
	imageInfo->hBlendDC = CreateCompatibleDC(hdc);
	imageInfo->hBlendBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hBlendOldBit = (HBITMAP)SelectObject(
		imageInfo->hBlendDC, imageInfo->hBlendBitmap);

	// Rotate
	int maxSize = width > height ? width : height;
	imageInfo->rotateMaxSize = maxSize * 2;
	imageInfo->hRotateDC = CreateCompatibleDC(hdc);
	imageInfo->hRotateBitmap = CreateCompatibleBitmap(hdc, maxSize * 2, maxSize * 2);
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

	// Temp
	imageInfo->hTempDC = CreateCompatibleDC(hdc);
	imageInfo->hTempBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hTempOldBit = (HBITMAP)SelectObject(
		imageInfo->hTempDC, imageInfo->hTempBitmap);

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
	imageInfo->hRotateOldBit = (HBITMAP)SelectObject(
		imageInfo->hRotateDC, imageInfo->hRotateBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL
		|| imageInfo->hTempBitmap == NULL
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

		// Temp
		SelectObject(imageInfo->hTempDC, imageInfo->hTempOldBit);
		DeleteObject(imageInfo->hTempBitmap);
		DeleteDC(imageInfo->hTempDC);

		// Blend
		SelectObject(imageInfo->hBlendDC, imageInfo->hBlendOldBit);
		DeleteObject(imageInfo->hBlendBitmap);
		DeleteDC(imageInfo->hBlendDC);

		// Rotate
		SelectObject(imageInfo->hRotateDC, imageInfo->hRotateOldBit);
		DeleteObject(imageInfo->hRotateBitmap);
		DeleteDC(imageInfo->hRotateDC);

		delete imageInfo;
	}
}

void Image::Render(HDC hdc, int destX, int destY, bool reverse)
{
	if (isTrans && reverse)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			imageInfo->width, 0,
			-imageInfo->width - 1, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,

			imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, imageInfo->height,
			transColor
		);
	}

	else if (isTrans && !reverse)
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

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, bool _bitBlt, bool isReverse)
{
	if (isTrans && !isReverse)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,
			transColor
		);
	}

	else if (isTrans && isReverse)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			sourWidth, 0,
			-sourWidth - 1, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,
			transColor
		);
	}

	else if (_bitBlt)
	{
		BitBlt(hdc,
			destX, destY,
			imageInfo->width, imageInfo->height,

			imageInfo->hMemDC,
			0, 0,
			SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY,
	int currentKeyFrameX, int currentKeyFrameY, bool reverse, bool reverse2, float scale/* = 1.0f*/)
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

	if (isTrans && reverse && !reverse2)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX, 0,
			-imageInfo->keyFrameWidth - 1, imageInfo->keyFrameHeight,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth / 2)*scale,
			destY - (imageInfo->keyFrameHeight / 2)*scale,
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hBlendDC,
			imageInfo->keyFrameWidth * -imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);
	}

	else if (isTrans && !reverse && reverse2)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			0, imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth, -imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY - 1,

			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth, imageInfo->keyFrameHeight,
			SRCCOPY);

		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth / 2)*scale,
			destY - (imageInfo->keyFrameHeight / 2)*scale,
			imageInfo->keyFrameWidth * scale,
			imageInfo->keyFrameHeight * scale,

			imageInfo->hBlendDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			transColor
		);
	}

	else if (isTrans && !reverse && !reverse2)
	{
		GdiTransparentBlt(
			hdc,
			destX - (imageInfo->keyFrameWidth / 2)*scale,
			destY - (imageInfo->keyFrameHeight / 2)*scale,
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
			destX - (imageInfo->keyFrameWidth / 2), destY - (imageInfo->keyFrameHeight / 2),
			imageInfo->keyFrameWidth,
			imageInfo->keyFrameHeight,
			imageInfo->hMemDC,
			imageInfo->keyFrameWidth * imageInfo->currentKeyFrameX,
			imageInfo->keyFrameHeight * imageInfo->currentKeyFrameY,
			SRCCOPY);
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
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);
		// 2. ����� �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC, 0, 0,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			transColor);
		// 3. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
	else
	{
		AlphaBlend(hdc,
			destX,
			destY,
			imageInfo->width, imageInfo->height,
			imageInfo->hMemDC, 0, 0, imageInfo->width, imageInfo->height,
			blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, bool isReverse)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans && !isReverse)
	{
		StretchBlt(
			imageInfo->hTempDC,
			sourWidth, 0,
			-sourWidth - 1, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			SRCCOPY);

		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			imageInfo->hTempDC,
			0, 0,
			sourWidth, sourHeight,
			transColor);

		AlphaBlend(
			hdc,
			destX + (sourWidth / 2) - 60,
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,
			blendFunc);

	}

	else if (isTrans && isReverse)
	{
		StretchBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			hdc,
			destX + (sourWidth / 2) - 60,
			destY - (sourHeight / 2),
			sourWidth, sourHeight,
			SRCCOPY);

		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			transColor);

		AlphaBlend(hdc,
			destX + (sourWidth / 2) - 60,
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hBlendDC, 0, 0,
			sourWidth, sourHeight,
			blendFunc);
	}
}

void Image::RotateRender(HDC hdc, double dblAngle,
	int destX, int destY, double dblSizeRatio,
	HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	POINT apt[3] = { 0 };
	double dblWidth = (double)imageInfo->width * dblSizeRatio;
	double dblHeight = (double)imageInfo->height * dblSizeRatio;
	double ixRotate = (int)((double)(imageInfo->width / 2)*dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
	double iyRotate = (int)((double)(imageInfo->height / 2)*dblSizeRatio);
	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle * PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. ȸ������ �������� �����ǥ�� ���ϰ�
	// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
	// 3. ���� ���� ������ ��ǥ�� ����.
	int i;
	for (i = 0; i < 3; i++)
	{
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
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

void Image::RotateAlphaRender(HDC hdc, double dblAngle, int destX, int destY, BYTE alpha, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	// ����
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans)
	{
		// 1. ������ DC�� �׷��� �ִ� ������ blend DC�� ����
		BitBlt(imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
			hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2), SRCCOPY);

		// 2. �̹����� ȸ�����Ѽ� Rotate DC�� ����
		RECT rc = { 0, 0, imageInfo->rotateMaxSize, imageInfo->rotateMaxSize };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateRender(imageInfo->hRotateDC, dblAngle,
			imageInfo->rotateMaxSize / 2, imageInfo->rotateMaxSize / 2);

		// 3. Rotate DC �̹����� blend DC�� ������ ������ �����ؼ� ����
		GdiTransparentBlt(imageInfo->hBlendDC,
			0, 0,
			imageInfo->width, imageInfo->height,

			imageInfo->hRotateDC,
			(imageInfo->rotateMaxSize / 2) - (imageInfo->width / 2),
			(imageInfo->rotateMaxSize / 2) - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			transColor);

		// 4. blend DC�� ������ ������ DC�� ����
		AlphaBlend(hdc,
			destX - (imageInfo->width / 2),
			destY - (imageInfo->height / 2),
			imageInfo->width, imageInfo->height,
			imageInfo->hBlendDC, 0, 0, imageInfo->width, imageInfo->height,
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

void Image::AngleRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, double _dblAngle, BYTE alpha, bool _bitBlt, bool isReverse)
{
	blendFunc.SourceConstantAlpha = alpha;

	if (isTrans && !isReverse)
	{
		BitBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			hdc,
			destX + (sourWidth / 2),
			destY - (sourHeight / 2),
			SRCCOPY);

		/*StretchBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight,
			SRCCOPY);*/

		RECT rc = { 0, 0, 30, 30 };
		HBRUSH hBrush = CreateSolidBrush(transColor);
		FillRect(imageInfo->hRotateDC, &rc, hBrush);
		DeleteObject(hBrush);

		RotateRender(
			imageInfo->hRotateDC,
			_dblAngle,
			sourWidth / 2, sourHeight / 2);

		GdiTransparentBlt(
			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,

			imageInfo->hRotateDC,
			sourX, sourY,
			sourWidth, sourHeight,
			transColor);

		AlphaBlend(
			hdc,
			destX + (sourWidth / 2),
			destY - (sourHeight / 2),
			sourWidth, sourHeight,

			imageInfo->hBlendDC,
			0, 0,
			sourWidth, sourHeight,
			blendFunc);
	}
}

void Image::AnimationRender(HDC hdc, int destX, int destY, Animation * ani, bool _bitBlt, bool isReverse)
{
	Render(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, _bitBlt, isReverse);
}

void Image::AnimationAlphaRender(HDC hdc, int destX, int destY, Animation * ani, BYTE alpha, bool isReverse)
{
	AlphaRender(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, alpha, isReverse);
}

void Image::AniAngleRender(HDC hdc, int destX, int destY, Animation * ani, double _dblAngle, bool _bitBlt, bool isReverse)
{
	AngleRender(hdc, destX, destY, ani->GetFramePos().x, ani->GetFramePos().y, imageInfo->keyFrameWidth, imageInfo->keyFrameHeight, _dblAngle, 250, _bitBlt, isReverse);
}

HDC Image::GetMemDC()
{
	return imageInfo->hMemDC;
}

int Image::GetMaxKeyFrameX()
{
	return imageInfo->maxKeyFrameX;
}

int Image::GetMaxKeyFrameY()
{
	return imageInfo->maxKeyFrameY;
}

int Image::GetWidth()
{
	return imageInfo->width;
}

int Image::GetHeight()
{
	return imageInfo->height;
}

int Image::GetFrameWidth()
{
	return imageInfo->keyFrameWidth;
}

int Image::GetFrameHeight()
{
	return imageInfo->keyFrameHeight;
}

Image::Image()
{}

Image::~Image()
{}

// stretchBlt + alphaBlend
//StretchBlt(
//	imageInfo->hTempDC,
//	sourWidth, 0,
//	-sourWidth - 1, sourHeight,
//
//	imageInfo->hMemDC,
//	sourX, sourY,
//	sourWidth, sourHeight,
//	SRCCOPY);
//
//GdiTransparentBlt(
//	imageInfo->hBlendDC,
//	0, 0,
//	sourWidth, sourHeight,
//
//	imageInfo->hTempDC,
//	0, 0,
//	sourWidth, sourHeight,
//	transColor);
//
//AlphaBlend(
//	hdc,
//	destX + (sourWidth / 2) - 60,
//	destY - (sourHeight / 2),
//	sourWidth, sourHeight,
//
//	imageInfo->hBlendDC,
//	0, 0,
//	sourWidth, sourHeight,
//	blendFunc);