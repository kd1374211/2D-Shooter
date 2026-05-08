#include "TimeManager.h"

void C_TimeManager::Reset()
{
	m_surviveTimeF = 0;
	m_timeF = 0;
	m_timeChargeF = 120;
	SetTimeState(E_TimeState::Normal);
}

void C_TimeManager::CheckTimeState()
{
	if (m_nowTimeState != E_TimeState::Normal)
	{
		//先に終了チェック
		if (m_timeChargeF <= 0)
		{
			SetTimeState(E_TimeState::Normal);
			return;
		}
		m_countF_state++;

		if (m_nowTimeState == E_TimeState::Stop || m_nowTimeState == E_TimeState::Half && GetHalfTime())m_timeChargeF--;
	}
}

void C_TimeManager::Update()
{
	m_timeChange = E_TimeChange::None;
	if (m_nowTimeState == E_TimeState::Normal || m_nowTimeState == E_TimeState::Half && GetHalfTime())
	{
		m_timeF--;
		if (m_timeF < MINTIME)m_timeF = MINTIME;
	}

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
	m_timeChange = E_TimeChange::Add;
	if (m_timeF > MAXTIME)m_timeF = MAXTIME;
}

void C_TimeManager::SubTime(int a_subF)
{
	m_timeF -= a_subF;
	m_timeChange = E_TimeChange::Sub;
	if (m_timeF < MINTIME)m_timeF = MINTIME;
}


void C_TimeManager::AddTimeCharge(int a_amount)
{
	if (m_nowTimeState == E_TimeState::Stop)return;

	m_timeChargeF += a_amount;
	if (m_timeChargeF > TIMECHARGE_MAX)m_timeChargeF = TIMECHARGE_MAX;
}

void C_TimeManager::SetTimeState(E_TimeState a_state)
{
	m_nowTimeState = a_state;
	m_countF_state = 0;
}

void C_TimeManager::Load()
{
	m_timeChargeTex.Load("Texture/Scene/Game/TimeChargeBar.png");
}

void C_TimeManager::Release()
{
	m_timeChargeTex.Release();
}
