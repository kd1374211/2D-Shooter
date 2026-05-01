#pragma once
#include "../BulletBase.h"

class C_FighterBullet :public C_BulletBase
{
public:

	C_FighterBullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle);
	~C_FighterBullet()override {}

private:

};