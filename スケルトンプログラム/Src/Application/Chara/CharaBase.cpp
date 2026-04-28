#include "CharaBase.h"

void C_CharaBase::Update()
{
}

void C_CharaBase::Draw()
{
}

void C_CharaBase::CalcMove()
{
	m_move.Normalize();
	m_pos += m_move * m_moveSpeed;
}

void C_CharaBase::UpdateAnimCnt()
{

	for (auto &itr : m_texData->m_texDatas)
	{
		S_TexData* data = &itr.second;

		if (data->m_texAnimMax != 1)
		{
			data->m_animCnt++;

			if (data->m_animCnt >= data->m_texAnimMax)
			{
				data->m_animCnt -= data->m_texAnimMax;
			}
		}
	}
}
