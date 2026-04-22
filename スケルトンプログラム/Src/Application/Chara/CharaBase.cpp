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

S_TexData C_CharaBase::GetData(E_TexType a_type)
{
	S_TexData ans = m_texData->m_texData.find(a_type)->second;

	return(ans);
}
