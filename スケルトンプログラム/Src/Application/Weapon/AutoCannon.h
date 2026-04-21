#pragma once
#include "WeaponBase.h"

class C_AutoCannon :public C_WeaponBase
{
public:

	C_AutoCannon();
	~C_AutoCannon() {};

	void Update()override;
	void Draw()override;

private:
};