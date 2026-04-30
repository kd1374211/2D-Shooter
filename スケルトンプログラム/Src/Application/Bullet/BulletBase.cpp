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
	if (m_pos.x > MOVEOUTMAX.x || m_pos.x < MOVEOUTMIN.x)return(false);
	else if (m_pos.y > MOVEOUTMAX.y || m_pos.y < MOVEOUTMIN.y)return(false);

	return(true);
}
