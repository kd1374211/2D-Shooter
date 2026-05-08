#include "BulletBase.h"
#include "../Const/ScreenConst.h"
#include "../Time/TimeManager.h"

void C_BulletBase::Update()
{
	if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
	{
		m_pos += m_speed * m_shotSpeed;

		UpdateAnimCnt();
	}

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

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void C_BulletBase::UpdateAnimCnt()
{
	m_animCnt++;

	if (m_animCnt >= m_texData->m_texAnimMax)
	{
		m_animCnt -= m_texData->m_texAnimMax;
	}
}

void C_BulletBase::OnHit()
{
	m_isEnd = true;
}

bool C_BulletBase::GetIsInScreen()
{
	if (m_pos.x > SCREENSIZEHALF.x || m_pos.x < -SCREENSIZEHALF.x)return(false);
	else if (m_pos.y > SCREENSIZEHALF.y || m_pos.y < -SCREENSIZEHALF.y)return(false);

	return(true);
}
