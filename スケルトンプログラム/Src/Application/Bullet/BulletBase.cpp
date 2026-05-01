#include "BulletBase.h"
#include "../Const/ScreenConst.h"

void C_BulletBase::Update()
{
	m_pos += m_speed * m_shotSpeed;

	UpdateAnimCnt();

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	Math::Matrix scale = Math::Matrix::CreateScale(m_texData->m_texScale);
	Math::Matrix rotat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_texAngle));

	m_mat = rotat * scale * trans;
}

void C_BulletBase::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);

	Math::Vector2 texSize = m_texData->m_texSize;
	Math::Rectangle rec = { (long)((int)(m_animCnt * m_texData->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(&m_texData->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_BulletBase::UpdateAnimCnt()
{
	m_animCnt++;

	if (m_animCnt >= m_texData->m_texAnimMax)
	{
		m_animCnt -= m_texData->m_texAnimMax;
	}
}

bool C_BulletBase::GetIsInScreen()
{
	if (m_pos.x > MOVEOUTMAX.x || m_pos.x < MOVEOUTMIN.x)return(false);
	else if (m_pos.y > MOVEOUTMAX.y || m_pos.y < MOVEOUTMIN.y)return(false);

	return(true);
}
