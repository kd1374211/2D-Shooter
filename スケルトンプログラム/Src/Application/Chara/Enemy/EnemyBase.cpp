#include "EnemyBase.h"

//仮
#include "../../Time/TimeManager.h"

C_EnemyBase::C_EnemyBase() :m_health(0), m_isEnd(false), m_nowAction(E_EnemyAction::Idle), m_countF(0), m_texAlpha(1.0f)
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
	Math::Color color = { 1,1,1,m_texAlpha };

	SHADER.m_spriteShader.DrawTex(tex->m_tex, 0, 0, texSize.x, texSize.y, &rec, &color);
}

void C_EnemyBase::UpdateTexAlpha()
{
	if (m_texAlpha < 1.0f)
	{
		m_texAlpha += ALPHACHANGE;
	}

	if (m_texAlpha >= 1.0f)m_texAlpha = 1.0f;
}

void C_EnemyBase::GetHit(int a_damage)
{
	m_statData.m_health -= a_damage;
	if (m_statData.m_health > 0)
	{
		m_texAlpha = HITALPHA;
	}
	else
	{
		m_texAlpha = 1.0f;
		ChangeAction(E_EnemyAction::Dead);
		TIMEMGR.AddTime(m_statData.m_timeAddOnKill);
	}
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

void C_EnemyBase::UpdateAnimCnt()
{
	//炎
	S_TexData* data = GetTexData(E_CharaBaseTexType::EngineEffect);
	data->m_animCnt++;

	if (data->m_animCnt >= data->m_texAnimMax)
	{
		data->m_animCnt -= data->m_texAnimMax;
	}

	//本体
	switch (m_nowAction)
	{
	case E_EnemyAction::Idle:
		data = GetTexData(E_CharaBaseTexType::Base);
		break;
	case E_EnemyAction::Attack:
		data = GetTexData(E_CharaBaseTexType::Attack);
		break;
	case E_EnemyAction::Dead:
		data = GetTexData(E_CharaBaseTexType::OnHit);
		break;
	}

	data->m_animCnt++;

	if (data->m_animCnt >= data->m_texAnimMax)
	{
		data->m_animCnt -= data->m_texAnimMax;
	}
}

void C_EnemyBase::CheckActionEnd()
{
	if (m_nowAction == E_EnemyAction::Attack)
	{
		if (GetTexData(E_CharaBaseTexType::Attack)->m_animCnt == 0)
		{
			ChangeAction(E_EnemyAction::Idle);
		}
	}
	else if (m_nowAction == E_EnemyAction::Dead)
	{
		if (GetTexData(E_CharaBaseTexType::OnHit)->m_animCnt == 0)
		{
			m_isEnd = true;
		}
	}
}

bool C_EnemyBase::CheckIsDead() const
{
	return(m_nowAction == E_EnemyAction::Dead ? true : false);
}
