#include "WeaponBase.h"

void C_WeaponBase::Action(Math::Vector2 a_playerPos)
{
}

void C_WeaponBase::Update(Math::Vector2 a_playerPos)
{
}

void C_WeaponBase::Draw()
{
}

void C_WeaponBase::Shot(Math::Vector2 a_pos)
{
}

void C_WeaponBase::UpdateAnimCnt()
{
	WEAPON.m_animCnt++;

	if (WEAPON.m_animCnt >= WEAPON.m_texAnimMax)WEAPON.m_animCnt -= WEAPON.m_texAnimMax;
}
