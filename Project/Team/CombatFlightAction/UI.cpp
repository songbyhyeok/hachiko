#include "UI.h"
#include "Image.h"

HRESULT UI::Init()
{
	selectChar = ImageManager::GetSingleton()->AddImage("SelectChar", "Image/UI/Select.bmp", WINSIZE_X, 400, true, RGB(255, 0, 255));
	selectBar = ImageManager::GetSingleton()->AddImage("SelectBar", "Image/UI/SelectBar.bmp", 150, 240, true, RGB(255, 255, 255));

	if (selectChar == nullptr || selectBar == nullptr)
		return E_FAIL;

	select = 0;

	return S_OK;
}

void UI::Render(HDC hdc)
{
	selectChar->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);
	selectBar->Render(hdc, WINSIZE_X / 2 - 70 + select, WINSIZE_Y / 2 + 40);
}

void UI::SetSelect(int _select)
{
	select += _select;
}

int UI::GetSelect()
{
	return select;
}

UI::UI()
{
}

UI::~UI()
{
}
