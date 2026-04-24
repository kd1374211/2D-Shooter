#include "AC_Bullet.h"
#include "../AutoCannon.h"

C_AutoCannon_Bullet::C_AutoCannon_Bullet(Math::Vector2 a_pos, C_AutoCannon* a_owner)
{
	m_pos = a_pos;
	m_tex = a_owner->GetBulletTex();
	m_texScale = a_owner->GetTexScale();
}

void C_AutoCannon_Bullet::Action()
{
	m_pos.x += 15.0f;
	
	UpdateAnimCnt();
}

void C_AutoCannon_Bullet::Update()
{
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texScale.x, m_texScale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(PLAYERANGLE);

	m_mat = rotat * scale * trans;
}

void C_AutoCannon_Bullet::Draw()
{
	//マトリックス
	SHADER.m_spriteShader.SetMatrix(m_mat);

	//本体
	Math::Vector2 texSize = m_tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(m_tex->m_animCnt * m_tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&m_tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}
