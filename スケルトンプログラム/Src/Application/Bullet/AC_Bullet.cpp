#include "AC_Bullet.h"
#include "BulletManager.h"

C_AutoCannon_Bullet::C_AutoCannon_Bullet(Math::Vector2 a_pos)
{
	m_pos = a_pos;
	m_team = E_BulletTeam::Player;
	m_texData = BULLETMGR.GetTexData(E_BulletType::B_AutoCannon);
}

void C_AutoCannon_Bullet::Update()
{
	m_pos.x += 15.0f;

	UpdateAnimCnt();

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale.x, m_texData->m_texScale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(PLAYERANGLE);

	m_mat = rotat * scale * trans;
}

void C_AutoCannon_Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Vector2 texSize = m_texData->m_texSize;
	Math::Rectangle rec = { (long)((int)(m_animCnt * m_texData->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&m_texData->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}
