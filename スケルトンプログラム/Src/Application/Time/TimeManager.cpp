#include "TimeManager.h"

void C_TimeManager::Reset()
{
	m_surviveTimeF = 0;
	m_timeF = 0;
}

void C_TimeManager::Update()
{
	m_timeF--;
	if (m_timeF < MINTIME)m_timeF = MINTIME;

	m_surviveTimeF++;
	if (m_surviveTimeF > MAXSURVIVETIME)m_surviveTimeF = MAXSURVIVETIME;
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
