#pragma once
#include "WeaponBase.h"

class C_BigSpaceGun : public C_WeaponBase
{
public:

	C_BigSpaceGun();
	~C_BigSpaceGun() {};

	void Update(Math::Vector2 a_playerPos)override;
	void Draw()override;

private:
};