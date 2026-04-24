#include "CharaBase.h"

void C_CharaBase::Action()
{
}

void C_CharaBase::Update()
{
}

void C_CharaBase::Draw()
{
}

void C_CharaBase::UpdateAnimCnt()
{
	for (int i = 0;i < E_CharaBaseTexType::TexTypeMax;i++)
	{
		S_TexData* data = &m_texData->m_texDatas[i];

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
