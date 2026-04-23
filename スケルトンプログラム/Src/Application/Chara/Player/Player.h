#pragma once
#include "../CharaBase.h"
#include "../../Weapon/WeaponConst.h"

class C_Player : public C_CharaBase
{
public:

	C_Player();
	~C_Player() {};

	void Action()	override;
	void Update()	override;
	void Draw()		override;

private:

	C_WeaponBase* m_weapon;
};