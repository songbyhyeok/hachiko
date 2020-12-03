// SingletonBase.h

#pragma once

template<typename T>
class SingletonBase
{
protected:
	static T* instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetSingleton();	// instance를 외부에 노출
	void ReleaseSingleton();	// 메모리 할당된 instance 해제
};

// 싱글톤 초기화
// static 변수 문법상 {} 영역 밖에서 초기화한다.
template <typename T>
T* SingletonBase<T>::instance = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	if (!instance)
	{
		instance = new T;	// 0x000001
	}

	return instance;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;		// 0x000001
		instance = 0;			// 0x000000
	}
}