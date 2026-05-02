#pragma once
#include "WeaponBase.h"

class C_AutoCannon :public C_WeaponBase
{
public:

	C_AutoCannon(S_TexData* a_texData,Math::Vector3 a_texScale);
	~C_AutoCannon() {};

	void Update(Math::Vector2 a_playerPos, bool a_isAuto)override;
	void Draw()override;

	//発射
	void Shot(Math::Vector2 a_pos)override;

private:

	//弾発射フレーム
	static const int SHOTBULLET_L = 2;
	static const int SHOTBULLET_R = 4;

	//弾発射位置ズレ
	const float POSOFSX_BULLET = 10;
	const float POSOFSY_BULLET = 13;

	//弾速度
	const float SHOTSPEED_BULLET = 15;

};