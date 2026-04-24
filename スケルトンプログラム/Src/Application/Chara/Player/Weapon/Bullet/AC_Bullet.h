#pragma once
#include "BulletBase.h"

class C_AutoCannon;

class C_AutoCannon_Bullet:public C_BulletBase
{
public:

	C_AutoCannon_Bullet(Math::Vector2 a_pos, C_AutoCannon* a_owner);
	~C_AutoCannon_Bullet(){}

	void Action()override;
	void Update()override;
	void Draw()override;

};