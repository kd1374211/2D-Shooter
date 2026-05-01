#pragma once
#include "WeaponBase.h"

class C_BigSpaceGun : public C_WeaponBase
{
public:

	C_BigSpaceGun(S_TexData* a_texData, Math::Vector3 a_texScale);
	~C_BigSpaceGun() {};

	void Update(Math::Vector2 a_playerPos)override;
	void Draw()override;

	//発射
	void Shot(Math::Vector2 a_pos)override;

private:

	//弾発射フレーム
	static const int SHOTBULLET = 16;

	//弾発射位置ズレ
	const float POSOFSX_BULLET = 20;

	//弾速度
	const float SHOTSPEED_BULLET = 10;

};