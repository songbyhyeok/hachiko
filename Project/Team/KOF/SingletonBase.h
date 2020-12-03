#pragma once

//키입력, 데이터관리, 사운드매니저 이런 유형들 <-싱글톤

template <typename T>
class SingletonBase
{
protected:
	static T * instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T * GetSingleton();	// instance를 외부에 노출
	void ReleaseSingleton();	// 메모리 할당된 instance 해제
};

// 싱글톤 초기화
// static 변수 문법상 {} 영역 밖에서 초기화한다.
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