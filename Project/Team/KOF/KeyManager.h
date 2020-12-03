#pragma once

#include "pch.h"
#include "SingletonBase.h"
#include <bitset>

#define KEY_MAX_COUNT 256

using namespace std;

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bitset<KEY_MAX_COUNT> keyUp; // 256���� ��Ʈ�� ��� �̸��� keyUp
	bitset<KEY_MAX_COUNT> keyDown; // 256���� ��Ʈ�� ��� �̸��� keyUp���� �Ѵ�.

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyUp(int key);		// Ű�� �ѹ� ������ ��
	bool IsOnceKeyDown(int key);	// Ű�� ������ ���� ��
	bool IsStayKeyDown(int key);	// Ű�� ������ ���� ��

	void SetKeyUp(int key, bool state);
	void SetKeyDown(int key, bool state);

	bitset<KEY_MAX_COUNT> GetKeyUp();
	bitset<KEY_MAX_COUNT> GetKeyDown();

	KeyManager();
	~KeyManager();
};

