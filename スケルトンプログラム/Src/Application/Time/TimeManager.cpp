#include "TimeManager.h"

void C_TimeManager::Reset()
{
	m_surviveTimeF = 0;
	m_timeF = 0;
	m_timeChargeF = 0;
	m_nowTimeState = E_TimeState::Normal;
}

void C_TimeManager::Update()
{
	m_timeF--;
	if (m_timeF < MINTIME)m_timeF = MINTIME;

	m_surviveTimeF++;
	if (m_surviveTimeF > MAXSURVIVETIME)m_surviveTimeF = MAXSURVIVETIME;
}

void C_TimeManager::DrawTimeCharge()
{
	int activeBar = m_timeChargeF / BARSEC_F;
	for (int i = 0;i < BARSECNUM;i++)
	{
		Math::Rectangle rec = { (long)(texTypes[i % BARSEC_ONE] * texSize.x),(long)(i >= activeBar ? 0 : texSize.y),(long)texSize.x,(long)texSize.y };
		SHADER.m_spriteShader.DrawTex(&m_timeChargeTex, texDrawStart.x + i * texDrawSize.x, texDrawStart.y, texDrawSize.x, texDrawSize.y, &rec);
	}
}

void C_TimeManager::AddTime(int a_addF)
{
	m_timeF += a_addF;
	if (m_timeF > MAXTIME)m_timeF = MAXTIME;
}

void C_TimeManager::SubTime(int a_subF)
{
	m_timeF -= a_subF;
	if (m_timeF < MINTIME)m_timeF = MINTIME;
}


void C_TimeManager::AddTimeCharge(int a_amount)
{
	m_timeChargeF += a_amount;
	if (m_timeChargeF > TIMECHARGE_MAX)m_timeChargeF = TIMECHARGE_MAX;
}

void C_TimeManager::Load()
{
	m_timeChargeTex.Load("Texture/Scene/Game/TimeChargeBar.png");
}

void C_TimeManager::Release()
{
	m_timeChargeTex.Release();
}
