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

	static const int ATTACKSTART = 80;
	static const int ATTACKSPAN = 80;

	static const int SHOTF = 6;
	const float SHOTANGLE_BASE = -15;
	const float SHOTANGLE_DIST = 15;
	static const int SHOTCNT = 3;
	static const int ATKENDF = 12;

	const float BULLETSPEED = -6.0f;

};