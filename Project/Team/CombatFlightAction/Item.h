
#include "GameNode.h"

class Image;

class Item : public GameNode
{
private:
	Image* item;

	float scale;

	float angle;
	float speed;

	bool isDropA;
	bool isDropB;
	bool isDropC;

	bool isDecide;

public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetIsDropA(bool _isBool) { isDropA = _isBool; }
	bool GetIsDropA() { return isDropA; }
	
	void SetIsDropB(bool _isBool) { isDropB = _isBool; }
	bool GetIsDropB() { return isDropB; }
	
	void SetIsDropC(bool _isBool) { isDropC = _isBool; }
	bool GetIsDropC() { return isDropC; }

	void SetIsDecide(bool _isBool) { isDecide = _isBool; }
	bool GetIsDecide() { return isDecide; }

	void DropItem();
	void Disappear();
};
