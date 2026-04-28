#include "AutoCannon.h"
#include "../../CharaTexManager.h"
#include "../../../Key/KeyStateManager.h"
#include "../../../Bullet/BulletManager.h"

C_AutoCannon::C_AutoCannon(S_TexData* a_texData, Math::Vector2 a_texScale) :m_bIsShot(false)
{
	m_nameTag = E_WeaponName::AutoCannon;

	m_texData = a_texData;
	m_scale = a_texScale;
	m_angle = PLAYERANGLE;
}

void C_AutoCannon::Update(Math::Vector2 a_playerPos)
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
	else if (m_texData->m_animCnt == SHOTBULLET_L)
	{
		Shot({ a_playerPos.x + POSOFSX_BULLET,a_playerPos.y + POSOFSY_BULLET });
	}
	else if (m_texData->m_animCnt == SHOTBULLET_R)
	{
		Shot({ a_playerPos.x + POSOFSX_BULLET,a_playerPos.y - POSOFSY_BULLET });
	}

	Math::Matrix trans = Math::Matrix::CreateTranslation(a_playerPos.x, a_playerPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angle));

	m_mat = rotat * scale * trans;
}

void C_AutoCannon::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = m_texData->m_texSize;
	Math::Rectangle rec = { (long)((int)(m_texData->m_animCnt * m_texData->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(m_texData->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_AutoCannon::Shot(Math::Vector2 a_pos)
{
	BULLETMGR.SpawnBullet(a_pos, SHOTSPEED_BULLET, 0, E_BulletType::B_AutoCannon);
}
