#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	for (int i = 0; i < KEY_MAX_COUNT; i++)
	{
		SetKeyDown(i, false);	
		SetKeyUp(i, true);
	}

	return S_OK;
}

void KeyManager::Release() {}

bool KeyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->GetKeyDown()[key])
		{
			this->SetKeyDown(key, true);

			return true;
		}

		else
			this->SetKeyDown(key, false);
	}

	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->SetKeyUp(key, false);

		return false;
	}

	else
	{
		if (!this->GetKeyUp()[key])
		{
			this->SetKeyUp(key, true);

			return true;
		}
	}

	return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bitset<KEY_MAX_COUNT> KeyManager::GetKeyUp() { return keyUp; }
bitset<KEY_MAX_COUNT> KeyManager::GetKeyDown() { return keyDown; }

void KeyManager::SetKeyUp(int key, bool state) { keyUp.set(key, state); }
void KeyManager::SetKeyDown(int key, bool state) { keyDown.set(key, state); }

KeyManager::KeyManager() {}
KeyManager::~KeyManager() {}

/*
함수 호출 시점에 가상키 (VK_...)가 어떤 상태인지 확인이 가능하다.

GetAsyncKeyState() 함수와 GetKeyState() 함수는 키보드의 키가 눌렸는지를 체크하는 함수들이다.

GetAsyncKeyState() 함수는 비 동기(Asynchronism)로 처리한다.즉, 호출된 시점에서 키 상태를 조사하여
, 메시지 큐를 거치지 않고 바로 리턴을 해 주므로 키 입력을 바로 처리해 줄 수가 있다.

GetKeyState() 함수는 호출된 시점에서 메시지 큐를 거치며, 메시지 발생 후의 상태를 리턴하게 되므로
, 키보드 메시지 처리 루틴내에서 사용해야 한다.게임과 같이 키 입력에 바로 반응을 해 줘야 하는
프로그램에서는 GetAsyncKeyState()함수를 사용하는 편이 좋다.

2진수
0 1 1bit -> 0과 1을 표현함

16진수는 한자리의 4개의 bit로 이루어져있다.  한자리의 0000 16개의 수를 표현이 가능한 것이다.
따라서 2진수로 16진수의 한자리를 표현하기 위해서는 4bit가 필요한 것이다.

/*
  1. 이전에 누른 적이 없고 호출 시점에서 안눌린 상태 = 0x0000
	0x0000 & 0x8000 = 0이 반환 -> FALSE

  2. 이전에 누른 적이 없고 호출 시점에서 눌린 상태 = 0x8000
	0x8000 & 0x8000 = 0x8000이 반환 -> 0이 아니므로 -> TRUE

  3. 이전에 누른 적이 있고 호출 시점에서 눌린 상태 = 0x8001
	0x8001 & 0x8000 = 0x8000이 반환 -> 0이 아니므로 -> TRUE

  4. 이전에 누른 적이 있고 호출 시점에서 안눌린 상태 = 0x0001
	0x0001 & 0x8000 = 0이 반환 -> FALSE

  그러므로 안눌리면 FALSE 눌리면 TRUE가 반환되어 조건문을 통과하게 된다.
*/
