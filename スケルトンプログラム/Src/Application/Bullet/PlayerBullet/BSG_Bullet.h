#pragma once
#include "../BulletBase.h"

class C_BigSpaceGun_Bullet :public C_BulletBase
{
public:

	C_BigSpaceGun_Bullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle);
	~C_BigSpaceGun_Bullet()override {}

};