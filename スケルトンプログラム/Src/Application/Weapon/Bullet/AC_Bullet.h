#pragma once
#include "BulletBase.h"

class C_AutoCannon_Bullet:public C_BulletBase
{
public:

	C_AutoCannon_Bullet(){}
	~C_AutoCannon_Bullet(){}

	void Update()override;
	void Draw()override;

};