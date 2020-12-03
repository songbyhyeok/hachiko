#pragma once

#include "pch.h"
#include "SingletonBase.h"
#include <bitset>

#define KEY_MAX_COUNT 256

using namespace std;

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bitset<KEY_MAX_COUNT> keyUp; // 256개의 비트로 잡고 이름은 keyUp
	bitset<KEY_MAX_COUNT> keyDown; // 256개의 비트로 잡고 이름은 keyUp으로 한다.

public:
	HRESULT Init();
	void Release();

	bool IsOnceKeyUp(int key);		// 키를 한번 눌렀을 때
	bool IsOnceKeyDown(int key);	// 키를 눌렀다 뗏을 때
	bool IsStayKeyDown(int key);	// 키를 누르고 있을 때

	void SetKeyUp(int key, bool state);
	void SetKeyDown(int key, bool state);

	bitset<KEY_MAX_COUNT> GetKeyUp();
	bitset<KEY_MAX_COUNT> GetKeyDown();

	KeyManager();
	~KeyManager();
};

