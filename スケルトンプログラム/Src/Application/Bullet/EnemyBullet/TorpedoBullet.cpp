#include "TorpedoBullet.h"
#include "../BulletManager.h"
#include "../../Const/ScreenConst.h"
#include "../../Time/TimeManager.h"
#include "../../Chara/CharaManager.h"
#include "../../Chara/Player/Player.h"

C_TorpedoBullet::C_TorpedoBullet(Math::Vector2 a_pos, float a_speed, float a_shotAngle)
{
	m_pos = a_pos;
	m_shotAngle = a_shotAngle;
	m_shotSpeed = a_speed;
	m_speed = { cosf(DirectX::XMConvertToRadians(m_shotAngle)), sinf(DirectX::XMConvertToRadians(m_shotAngle)) };

	m_team = E_BulletTeam::Enemy;
	m_texData = BULLETMGR.GetTexData(E_BulletType::B_Torpedo);
	m_statData = BULLETMGR.GetStatData(E_BulletType::B_Torpedo);
	m_texAngle = ENEMYANGLE;
}

void C_TorpedoBullet::Update()
{
	if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
	{
		if (m_shotSpeed < BULLETSPEED_MAX)m_shotSpeed += BULLETACCEL;
		Homing();

		m_pos += m_speed * m_shotSpeed;

		UpdateAnimCnt();
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_shotAngle - m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_TorpedoBullet::Homing()
{
	Math::Vector2 playerPos = CHARAMGR.GetPlayer()->GetPos();
	float TargetAngle = DirectX::XMConvertToDegrees(atan2f(playerPos.y - m_pos.y, playerPos.x - m_pos.x));
	float BulletAngle = m_shotAngle;

	while (TargetAngle > 360.0f)TargetAngle -= 360.0f;
	while (BulletAngle > 360.0f)BulletAngle -= 360.0f;
	if (TargetAngle < BulletAngle)TargetAngle += 360.0f;

	float Dist = TargetAngle - BulletAngle;
	if (Dist < 180.0f)
	{
		if (Dist < BULLETTURN_MAX)
		{
			m_shotAngle += Dist;
		}
		else
		{
			m_shotAngle += BULLETTURN_MAX;
		}
	}
	else
	{
		if (360.0f - Dist < BULLETTURN_MAX)
		{
			m_shotAngle -= 360.0f - Dist;
		}
		else
		{
			m_shotAngle -= BULLETTURN_MAX;
		}
	}

	while (m_shotAngle > 360.0f)m_shotAngle -= 360.0f;
	while (m_shotAngle < 0.0f)m_shotAngle += 360.0f;
	m_speed = { cosf(DirectX::XMConvertToRadians(m_shotAngle)), sinf(DirectX::XMConvertToRadians(m_shotAngle)) };
}
