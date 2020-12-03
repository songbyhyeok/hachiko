#pragma once

#include "GameNode.h"

class UI : public GameNode
{
private:
	Image * selectChar;
	Image * selectBar;

	int select;

public:
	virtual HRESULT Init();
	virtual void Render(HDC hdc);

	void SetSelect(int _select);
	int GetSelect();

	UI();
	~UI();
};

