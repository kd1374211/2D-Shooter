#include "BigSpaceGun.h"
#include "../../../Key/KeyStateManager.h"
#include "../../../Bullet/BulletManager.h"

C_BigSpaceGun::C_BigSpaceGun(S_TexData* a_texData, Math::Vector3 a_texScale)
{
	m_texData = a_texData;
	m_texScale = a_texScale;
	m_texAngle = PLAYERANGLE;
}

void C_BigSpaceGun::Update(Math::Vector2 a_playerPos)
{
	if (KEYMGR.GetIsPressed(E_KeyChecks::Space))
	{
		if (!m_bIsShot)
		{
			m_bIsShot = true;
		}
	}

	if (m_bIsShot)UpdateAnimCnt();

	if (m_texData->m_animCnt == 0)m_bIsShot = false;
	else if (m_texData->m_animCnt == SHOTBULLET)
	{
		Shot({ a_playerPos.x + POSOFSX_BULLET,a_playerPos.y });
	}
	
	Math::Matrix trans = Math::Matrix::CreateTranslation(a_playerPos.x, a_playerPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texScale.x, m_texScale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_BigSpaceGun::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = m_texData->m_texSize;
	Math::Rectangle rec = { (long)((int)(m_texData->m_animCnt * m_texData->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(m_texData->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_BigSpaceGun::Shot(Math::Vector2 a_pos)
{
	BULLETMGR.SpawnBullet(a_pos, SHOTSPEED_BULLET, 0, E_BulletType::B_BigSpaceGun);
}
