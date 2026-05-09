#pragma once
#include "../EnemyBase.h"

class C_Torpedo :public C_EnemyBase
{
public:

	C_Torpedo(Math::Vector2 a_pos);
	~C_Torpedo()override {}

	void Update()override;
	void Draw()override;

	//アニメーション
	void UpdateAnimCnt()override;
	void CheckActionEnd()override;

private:

	const float ATTACKSTARTX = 580.0f;
	static const int BACKWAITF = 60;

	//行動管理
	bool m_isAttackStart;
	bool m_isStartBack;

	int m_countF_back;

	static const int SHOTCOUNT = 6;
	const int SHOTF[SHOTCOUNT] = { 50, 70, 90, 110, 130, 150 };
	const int SHOTPOSOFSX = -7;
	const int SHOTPOSOFSY[SHOTCOUNT] = { 13, -13, 23, -23, 33, -33 };
	
	//弾速度
	const float BULLETSPEED = 1.0f;

	//弾角度
	const float BULLETANGLE = 180.0f;

};