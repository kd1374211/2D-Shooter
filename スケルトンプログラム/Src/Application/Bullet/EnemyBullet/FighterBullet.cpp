#include "FighterBullet.h"
#include "../BulletManager.h"

C_FighterBullet::C_FighterBullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle)
{
	m_pos = a_pos;
	m_shotAngle = a_shotAngle;
	m_shotSpeed = a_speed;
	m_speed = { cosf(DirectX::XMConvertToRadians(m_shotAngle)), sinf(DirectX::XMConvertToRadians(m_shotAngle)) };

	m_team = E_BulletTeam::Enemy;
	m_texData = BULLETMGR.GetTexData(E_BulletType::B_FighterGun);
	m_statData = BULLETMGR.GetStatData(E_BulletType::B_FighterGun);
	m_texAngle = m_shotAngle + ENEMYANGLE;
}
