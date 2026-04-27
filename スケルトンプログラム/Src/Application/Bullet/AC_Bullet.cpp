#include "AC_Bullet.h"

C_AutoCannon_Bullet::C_AutoCannon_Bullet(Math::Vector2 a_pos)
{
}

void C_AutoCannon_Bullet::Action()
{
	m_pos.x += 15.0f;
	
	UpdateAnimCnt();
}

void C_AutoCannon_Bullet::Update()
{
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	//Math::Matrix scale = Math::Matrix::CreateScale(m_scale.x, m_scale.y, 1);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(PLAYERANGLE);

	//m_mat = rotat * scale * trans;
}

void C_AutoCannon_Bullet::Draw()
{
	
}
