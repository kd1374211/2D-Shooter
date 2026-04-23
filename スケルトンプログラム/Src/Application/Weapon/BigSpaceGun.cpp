#include "BigSpaceGun.h"
#include "WeaponTexManager.h"

C_BigSpaceGun::C_BigSpaceGun()
{
	m_nameTag = E_WeaponName::BigSpaceGun;
	m_texData = WPNTEXMGR.GetWeaponTexData(m_nameTag);
}

void C_BigSpaceGun::Update(Math::Vector2 a_playerPos)
{
	UpdateAnimCnt();

	Math::Matrix trans = Math::Matrix::CreateTranslation(a_playerPos.x, a_playerPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale.x, m_texData->m_texScale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(TEXANGLE);

	m_mat = rotat * scale * trans;
}

void C_BigSpaceGun::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = WEAPON.m_texSize;
	Math::Rectangle rec = { (long)((int)(1 * WEAPON.m_animCntMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&WEAPON.m_tex, 0, 0, texSize.x, texSize.y, &rec);
}
