#include "BSG_Bullet.h"
#include "../BulletManager.h"
#include "../../Time/TimeManager.h"

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

void C_BigSpaceGun_Bullet::Update()
{
	m_pos += m_speed * m_shotSpeed;

	UpdateAnimCnt();

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_shotAngle + m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_BigSpaceGun_Bullet::OnHit()
{
	TIMEMGR.AddTimeCharge(m_statData->m_timeChargeOnHit);
	m_isEnd = true;
}
