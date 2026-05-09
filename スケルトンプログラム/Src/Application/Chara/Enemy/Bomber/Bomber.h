#pragma once
#include "../EnemyBase.h"

class C_Bomber :public C_EnemyBase
{
public:

	C_Bomber(Math::Vector2 a_pos);
	~C_Bomber()override {};

	void Update()override;
	void Draw()override;

	void CalcMoveAngle();

private:

	float m_moveAngle;

};