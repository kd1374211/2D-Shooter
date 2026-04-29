#include "BulletBase.h"
#include "../Const/ScreenConst.h"

void C_BulletBase::Update()
{
}

void C_BulletBase::Draw()
{
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
	if (fabs(m_pos.x) > SCREENSIZEHALF.x - (m_texData->m_texSize.x / 2.0f))return(false);
	else if (fabs(m_pos.y) > SCREENSIZEHALF.y - (m_texData->m_texSize.y / 2.0f))return(false);

	return(true);
}
