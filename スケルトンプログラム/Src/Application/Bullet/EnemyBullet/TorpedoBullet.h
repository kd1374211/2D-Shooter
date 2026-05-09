#pragma once
#include "../BulletBase.h"

class C_TorpedoBullet :public C_BulletBase
{
public:

	C_TorpedoBullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle);
	~C_TorpedoBullet()override {}

	void Update()override;
	void Homing();

private:

	const float BULLETACCEL = 0.2f;
	const float BULLETSPEED_MAX = 5.0f;

	const float BULLETTURN_MAX = 0.25f;

};