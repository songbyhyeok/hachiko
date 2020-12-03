#include "Image.h"
#include "pch.h"

HRESULT Image::Init(int width, int height)
{
	// �����츦 ����ϴ� �ڵ��� ������ ���
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	// ��Ʈ���� ����� ������ dc�� ������ش�.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	imageInfo->hBitMap = CreateCompatibleBitmap(hdc, width, height);
	// hMemDc�� hBitMap�� �������ش�. ���ϵǾ� �̹��� ���� hOldBit�� �޾��ش�.
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;	imageInfo->height = height;
	
	// ������ ������� HDC�� ����
	ReleaseDC(g_hWnd, hdc);

	// hBitMap �� hOldBit�� �������ִ� ������ �ִ�.
	// �ڵ� ���� ���ڰ� �������� ���� DC�� ���� �ּҰ� ������ ������

	// ��ο� �ִ� ������ �ε� �ߴµ� NULL�̸� �ε尡 �ȵ� ���̴�.
	if (imageInfo->hBitMap == NULL)
	{
		// �޸� ����
		Release();
		return E_FAIL;
	}

	// �� �Լ��� ���� �޸𸮿� �ø��� ������ �����.

	return S_OK;
}

HRESULT Image::Init(const DWORD resID, int width, int height, bool trans, COLORREF transColor)
{
	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	// �����츦 ����ϴ� �ڵ��� ������ ���
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->resID = 0;
	// ��Ʈ���� ����� ������ DC�� ������ش�.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	// ù��° �Ű������� �ν��Ͻ� �ڵ� HBITMAP���� ����ȯ
	imageInfo->hBitMap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	// hMemDc�� hBitMap�� �������ش�. ���ϵǾ� �̹��� ���� hOldBit�� �޾��ش�.
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;	imageInfo->height = height;

	isTrans = trans;
	this->transColor = transColor;

	// ������ ������� HDC�� ����
	ReleaseDC(g_hWnd, hdc);

	// hBitMap�� hOldBit�� �������ִ� ������ �ִ�.
	// �ڵ� ���� ���ڰ� �������� ���� DC�� ���� �ּҰ� ������ ������

	// ��ο� �ִ� ������ �ε��ߴµ� NULL�̸� �ε尡 �ȵ� ���̴�.
	if (imageInfo->hBitMap == NULL)
	{
		// �޸� ����
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
	// ��Ʈ���� ����� ������ DC�� ������ش�.
	imageInfo->hMemDc = CreateCompatibleDC(hdc);
	// ù��° �Ű������� �ν��Ͻ� �ڵ� HBITMAP���� ����ȯ
	imageInfo->hBitMap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit = (HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitMap);
	imageInfo->width = width;		imageInfo->height = height;
	
	// �߰�
	imageInfo->x = x - (width / 2);					imageInfo->y = y - (height / 2);
	imageInfo->curKeyFrameX = 0;					imageInfo->curKeyFrameY = 0;
	imageInfo->maxKeyFrameX = keyFrameX - 1;		imageInfo->maxKeyFrameY = keyFrameY - 1;
	imageInfo->keyFrameWidth = width / keyFrameX;	imageInfo->keyFrameHeight = height / keyFrameY;

	isTrans = trans;
	this->transColor = transColor;

	// ������ ������� HDC�� ����
	ReleaseDC(g_hWnd, hdc);

	// hBitMap, hOldBit�� �������ִ� ������ �ִ�.
	// �ڵ� ���� ���ڰ� �������� ���� DC�� ���� �ּҰ� ������ ������
	
	// ��ο� �ִ� ������ �ε��ߴµ� NULL�̸� �ε尡 �ȵ� ���̴�.
	if (imageInfo->hBitMap == NULL)
	{
		// �޸� ����
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		// 2�� ������ ����
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

	else // Ʈ���� �÷��� �����ϰ� �����϶�
		// �޸𸮿� �ִ� �����͸� ȭ�鿡 ��� �����Ѵ�.
		// HDC ������
		// dust ����� ������ǥ
		// imageInfo �������� ����� ����, ���� ũ��
		// DC 0, 0 �������� ���� ���� ��ġ 
		// STRCPY -> ���� �ɼ�
		BitBlt(hdc, destX, destY, imageInfo->width, imageInfo->height, imageInfo->hMemDc, 0, 0, SRCCOPY);
		//BitBlt(hdc, destX, destY, 458, 645, imageInfo->hMemDc, 669, 62, SRCCOPY);
}

void Image::FrameRender(HDC hdc, int destX, int destY, int curKeyFrameX, int curKeyFrameY, float scale)
{
	// ���� Ű������ �ε����� �ִ� Ű������ �ε������� Ŭ ��
	imageInfo->curKeyFrameX = curKeyFrameX;
	imageInfo->curKeyFrameY = curKeyFrameY;

	// ����ó��
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

	else // Ʈ���� �÷��� �����ϰ� �����϶�
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
