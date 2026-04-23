#include "WeaponBase.h"

void C_WeaponBase::Update(Math::Vector2 a_playerPos)
{
}

void C_WeaponBase::Draw()
{
}

void C_WeaponBase::UpdateAnimCnt()
{
	m_animCnt++;

	if (m_animCnt >= WEAPON.m_animCntMax)m_animCnt -= WEAPON.m_animCntMax;
}
