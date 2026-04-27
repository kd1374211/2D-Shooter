#pragma once
#include "WeaponBase.h"

class C_BigSpaceGun : public C_WeaponBase
{
public:

	C_BigSpaceGun(S_TexData* a_texData, Math::Vector2 a_texScale);
	~C_BigSpaceGun() {};

	void Action(Math::Vector2 a_playerPos)override;
	void Update(Math::Vector2 a_playerPos)override;
	void Draw()override;

	void Shot(Math::Vector2 a_pos)override;

private:
};