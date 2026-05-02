#include "WeaponBase.h"

void C_WeaponBase::Update(Math::Vector2 a_playerPos, bool a_isAuto)
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
	m_texData->m_animCnt++;

	if (m_texData->m_animCnt >= m_texData->m_texAnimMax)m_texData->m_animCnt -= m_texData->m_texAnimMax;
}
