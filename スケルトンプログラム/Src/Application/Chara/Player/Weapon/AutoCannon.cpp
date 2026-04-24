#include "AutoCannon.h"
#include "../../CharaTexManager.h"
#include "../../../Key/KeyStateManager.h"

C_AutoCannon::C_AutoCannon() :m_bIsShot(false)
{
	m_nameTag = E_WeaponName::AutoCannon;
	m_texData = CHARATEXMGR.GetWeaponTexData(m_nameTag);
}

void C_AutoCannon::Action(Math::Vector2 a_playerPos)
{
	if (KEYMGR.GetIsPressed(E_KeyChecks::Space))
	{
		if (!m_bIsShot)
		{
			m_bIsShot = true;
		}
	}

	if(m_bIsShot)UpdateAnimCnt();

	if (WEAPON.m_animCnt == 0)m_bIsShot = false;
	else if (WEAPON.m_animCnt == SHOTBULLET_L)
	{
		Shot({ a_playerPos.x+POSOFSX_BULLET,a_playerPos.y + POSOFSY_BULLET });
	}
	else if (WEAPON.m_animCnt == SHOTBULLET_R)
	{
		Shot({ a_playerPos.x + POSOFSX_BULLET,a_playerPos.y - POSOFSY_BULLET });
	}
}

void C_AutoCannon::Update(Math::Vector2 a_playerPos)
{
	Math::Matrix trans = Math::Matrix::CreateTranslation(a_playerPos.x, a_playerPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale.x, m_texData->m_texScale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(PLAYERANGLE);

	m_mat = rotat * scale * trans;
}

void C_AutoCannon::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = WEAPON.m_texSize;
	Math::Rectangle rec = { (long)((int)(WEAPON.m_animCnt * WEAPON.m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&WEAPON.m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_AutoCannon::Shot(Math::Vector2 a_pos)
{
}
