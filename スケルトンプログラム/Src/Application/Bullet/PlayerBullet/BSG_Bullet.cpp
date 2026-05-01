#include "BSG_Bullet.h"
#include "../BulletManager.h"

C_BigSpaceGun_Bullet::C_BigSpaceGun_Bullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle)
{
	m_pos = a_pos;
	m_shotSpeed = a_speed;
	m_shotAngle = a_shotAngle;
	m_speed = { cosf(DirectX::XMConvertToRadians(m_shotAngle)), sinf(DirectX::XMConvertToRadians(m_shotAngle)) };

	m_team = E_BulletTeam::Player;
	m_texData = BULLETMGR.GetTexData(E_BulletType::B_BigSpaceGun);
	m_statData = BULLETMGR.GetStatData(E_BulletType::B_BigSpaceGun);
	m_texAngle = PLAYERANGLE;
}
