#pragma once

//Ű�Է�, �����Ͱ���, ����Ŵ��� �̷� ������ <-�̱���

template <typename T>
class SingletonBase
{
protected:
	static T * instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T * GetSingleton();	// instance�� �ܺο� ����
	void ReleaseSingleton();	// �޸� �Ҵ�� instance ����
};

// �̱��� �ʱ�ȭ
// static ���� ������ {} ���� �ۿ��� �ʱ�ȭ�Ѵ�.
template <typename T>
T * SingletonBase<T>::instance = 0;

template <typename T>
T * SingletonBase<T>::GetSingleton()
{
	/*
	if (!instance)
		return instance;

	else
	{
		instance = new T;
		return instance;
	}

	return 0;
	*/

	if (!instance)
		return instance = new T;	// 0x000001

	return instance;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;	//0x000001
		instance = 0;		//0x000000
	}
}