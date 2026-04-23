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
	auto itr = m_texData->m_tex.begin();
	for (int i = 0;i < m_texData->m_tex.size();i++)
	{
		S_TexData* data = &itr->second;

		if (data->m_texAnimMax != 1)
		{
			data->m_animCnt++;

			if (data->m_animCnt >= data->m_texAnimMax)
			{
				data->m_animCnt -= data->m_texAnimMax;
			}
		}

		itr++;
	}
}

S_TexData C_CharaBase::GetData(E_TexType a_type)
{
	S_TexData ans = m_texData->m_tex.find(a_type)->second;

	return(ans);
}
