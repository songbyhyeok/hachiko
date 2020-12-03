#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Image;
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, Image*> mapImageDatas;


public:
	HRESULT Init();
	void Release();

	Image* AddImage(string strKey, int width, int height);
	// 파일에서 추가
	Image* AddImage(string strKey, const char* fileName, int width, int height,
		bool trans = FALSE, COLORREF transColor = FALSE);
	// 애니메이션 구조포함해서 추가
	Image* AddImage(string strKey, const char* fileName, float x, float y,
		int width, int height,
		int keyFrameX, int keyFrameY,
		bool trans = FALSE, COLORREF transColor = FALSE);

	Image* FindImage(string strKey);

	void DeleteImage(string strKey);
	void DeleteAll();

	ImageManager();
	~ImageManager();
};

