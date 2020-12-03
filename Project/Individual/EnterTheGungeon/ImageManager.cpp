#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	DeleteAll();
}

Image* ImageManager::AddImage(string strKey, int width, int height)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(width, height)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));
	return image;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, width, height, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));
	return image;
}

Image* ImageManager::AddImage(string strKey, const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, x, y, width, height, keyFrameX, keyFrameY, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));
	return image;
}

Image* ImageManager::AddImage(int size, string strKey, const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image[size];

	for (int i = 0; i < size; i++)
	{
		if (FAILED(image[i].Init(fileName, x, y, width, height, keyFrameX, keyFrameY, trans, transColor)))
		{
			image[i].Release();
			SAFE_DELETE(image);

			return nullptr;
		}

		mapImageDatas.insert(make_pair(strKey, &image[i]));
	}

	return image;
}

Image* ImageManager::FindImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		return iter->second;
	}

	return nullptr;
}

void ImageManager::DeleteImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		(iter->second)->Release();
		SAFE_DELETE((iter->second));

		mapImageDatas.erase(iter);
	}
}

void ImageManager::DeleteAll()
{
	map<string, Image*>::iterator iter;
	for (iter = mapImageDatas.begin(); iter != mapImageDatas.end(); /*iter++*/)
	{
		if (iter->second != nullptr)
		{
			if (iter->second == FindImage("ü��"))
			{
				iter->second->Release();
				SAFE_ARR_DELETE((iter->second));
			}

			else
				// second(value) �� �޸� ����
				(iter->second)->Release();
			SAFE_DELETE((iter->second));

			// key, value (pair) �� �޸� ����
			iter = mapImageDatas.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	// �� �� �޸� ����
	mapImageDatas.clear();
}

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}