#pragma once
#include "WeaponBase.h"

class C_AutoCannon :public C_WeaponBase
{
public:

	C_AutoCannon();
	~C_AutoCannon() {};

	void Action(Math::Vector2 a_playerPos)override;
	void Update(Math::Vector2 a_playerPos)override;
	void Draw()override;

	void Shot(Math::Vector2 a_pos)override;

private:

	static const int SHOTBULLET_L = 2;
	static const int SHOTBULLET_R = 4;

	const float POSOFSX_BULLET = 10;
	const float POSOFSY_BULLET = 13;

	bool m_bIsShot;

};