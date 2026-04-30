#include "EnemyBase.h"

C_EnemyBase::C_EnemyBase() :m_health(0), m_isEnd(false), m_nowAction(E_EnemyAction::Idle), m_countF(0), m_mainAnimCnt(0)
{
	m_texAngle = ENEMYANGLE;
}

void C_EnemyBase::Update()
{
}

void C_EnemyBase::Draw()
{
}

void C_EnemyBase::DrawMainShip()
{
	S_TexData* tex = nullptr;

	switch (m_nowAction)
	{
	case E_EnemyAction::Idle:
		tex = GetTexData(E_CharaBaseTexType::Base);
		break;
	case E_EnemyAction::Attack:
		tex = GetTexData(E_CharaBaseTexType::Attack);
		break;
	case E_EnemyAction::Dead:
		tex = GetTexData(E_CharaBaseTexType::OnHit);
		break;
	default:
		tex = GetTexData(E_CharaBaseTexType::Base);
		break;
	}

	//本体
	Math::Vector2 texSize = tex->m_texSize;
	Math::Rectangle rec = { (long)((int)(tex->m_animCnt * tex->m_texAnimMulti) * texSize.x),0,(long)texSize.x,(long)texSize.y };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec);
}

void C_EnemyBase::GetHit()
{
}

void C_EnemyBase::ChangeAction(E_EnemyAction a_action)
{
	m_nowAction = a_action;

	switch (m_nowAction)
	{
	case E_EnemyAction::Idle:
		GetTexData(E_CharaBaseTexType::Base)->m_animCnt = 0;
		break;
	case E_EnemyAction::Attack:
		GetTexData(E_CharaBaseTexType::Attack)->m_animCnt = 0;
		break;
	case E_EnemyAction::Dead:
		GetTexData(E_CharaBaseTexType::OnHit)->m_animCnt = 0;
		break;
	}
}

bool C_EnemyBase::GetIsDead() const
{
	return(m_nowAction == E_EnemyAction::Dead ? true : false);
}
