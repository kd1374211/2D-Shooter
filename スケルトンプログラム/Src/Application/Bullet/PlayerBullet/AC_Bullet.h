#pragma once
#include "../BulletBase.h"

class C_AutoCannon_Bullet:public C_BulletBase
{
public:

	C_AutoCannon_Bullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle);
	~C_AutoCannon_Bullet()override{}

	void Update()override;
	void Draw()override;

};