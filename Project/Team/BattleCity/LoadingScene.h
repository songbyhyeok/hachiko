#pragma once
#include "GameNode.h"
class Animation;
class LoadingScene : public GameNode
{
private:
	Image* bg;
	Animation* ani;
public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	LoadingScene();
	~LoadingScene();
};

