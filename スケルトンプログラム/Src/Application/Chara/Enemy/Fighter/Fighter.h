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

	//移動速度
	const float MOVESPEED = 3.0f;

	//攻撃開始/間隔
	static const int ATTACKSTART = 100;
	static const int ATTACKSPAN = 120;

	//攻撃アニメーションから弾が出るまで
	static const int SHOTF = 6;

	//発射角度
	const float SHOTANGLE_BASE = -15;
	const float SHOTANGLE_DIST = 15;

	//発射数
	static const int SHOTCNT = 3;

	//攻撃終了F
	static const int ATKENDF = 12;

	//弾速度
	const float BULLETSPEED = -7.0f;

};