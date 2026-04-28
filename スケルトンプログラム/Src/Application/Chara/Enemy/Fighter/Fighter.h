#pragma once
#include "../EnemyBase.h"

class C_Fighter :public C_EnemyBase
{
public:

	C_Fighter(Math::Vector2 a_pos);
	~C_Fighter()override{}

	void Update()override;
	void Draw()override;

private:

	const float MOVESPEED = 4.0f;

	static const int ATTACKSTART = 60;
	static const int ATTACKSPAN = 60;

	static const int SHOTF = 6;
	const float SHOTANGLE_L = -30;
	const float SHOTANGLE_R = 30;

};