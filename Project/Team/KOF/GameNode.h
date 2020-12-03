#pragma once

#include "pch.h"

class GameNode
{
public:
	virtual HRESULT Init();	// 멤버변수 초기화, 메모리 할당
	virtual void Release();	// 메모리 해제
	virtual void Update();	// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);

	GameNode();
	~GameNode();
};

