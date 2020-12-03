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
�Լ� ȣ�� ������ ����Ű (VK_...)�� � �������� Ȯ���� �����ϴ�.

GetAsyncKeyState() �Լ��� GetKeyState() �Լ��� Ű������ Ű�� ���ȴ����� üũ�ϴ� �Լ����̴�.

GetAsyncKeyState() �Լ��� �� ����(Asynchronism)�� ó���Ѵ�.��, ȣ��� �������� Ű ���¸� �����Ͽ�
, �޽��� ť�� ��ġ�� �ʰ� �ٷ� ������ �� �ֹǷ� Ű �Է��� �ٷ� ó���� �� ���� �ִ�.

GetKeyState() �Լ��� ȣ��� �������� �޽��� ť�� ��ġ��, �޽��� �߻� ���� ���¸� �����ϰ� �ǹǷ�
, Ű���� �޽��� ó�� ��ƾ������ ����ؾ� �Ѵ�.���Ӱ� ���� Ű �Է¿� �ٷ� ������ �� ��� �ϴ�
���α׷������� GetAsyncKeyState()�Լ��� ����ϴ� ���� ����.

2����
0 1 1bit -> 0�� 1�� ǥ����

16������ ���ڸ��� 4���� bit�� �̷�����ִ�.  ���ڸ��� 0000 16���� ���� ǥ���� ������ ���̴�.
���� 2������ 16������ ���ڸ��� ǥ���ϱ� ���ؼ��� 4bit�� �ʿ��� ���̴�.

/*
  1. ������ ���� ���� ���� ȣ�� �������� �ȴ��� ���� = 0x0000
	0x0000 & 0x8000 = 0�� ��ȯ -> FALSE

  2. ������ ���� ���� ���� ȣ�� �������� ���� ���� = 0x8000
	0x8000 & 0x8000 = 0x8000�� ��ȯ -> 0�� �ƴϹǷ� -> TRUE

  3. ������ ���� ���� �ְ� ȣ�� �������� ���� ���� = 0x8001
	0x8001 & 0x8000 = 0x8000�� ��ȯ -> 0�� �ƴϹǷ� -> TRUE

  4. ������ ���� ���� �ְ� ȣ�� �������� �ȴ��� ���� = 0x0001
	0x0001 & 0x8000 = 0�� ��ȯ -> FALSE

  �׷��Ƿ� �ȴ����� FALSE ������ TRUE�� ��ȯ�Ǿ� ���ǹ��� ����ϰ� �ȴ�.
*/
