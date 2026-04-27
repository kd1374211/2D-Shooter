#include "BigSpaceGun.h"
#include "../../CharaTexManager.h"

C_BigSpaceGun::C_BigSpaceGun(S_TexData* a_texData, Math::Vector2 a_texScale)
{
	m_nameTag = E_WeaponName::BigSpaceGun;

	m_texData = a_texData;
	m_scale = a_texScale;
}

void C_BigSpaceGun::Update(Math::Vector2 a_playerPos)
{
	UpdateAnimCnt();

	Math::Matrix trans = Math::Matrix::CreateTranslation(a_playerPos.x, a_playerPos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(PLAYERANGLE);

	m_mat = rotat * scale * trans;
}

void C_BigSpaceGun::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = m_texData->m_texSize;
	Math::Rectangle rec = { (long)((int)(1 * m_texData->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(m_texData->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_BigSpaceGun::Shot(Math::Vector2 a_pos)
{
}
