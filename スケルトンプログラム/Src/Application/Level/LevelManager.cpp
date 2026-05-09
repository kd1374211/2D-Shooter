#include "LevelManager.h"
#include "../Time/TimeManager.h"

void C_LevelManager::Reset()
{
	m_level = 1;
	m_timeMulti = 1.0f;
}

void C_LevelManager::Update()
{
	//先にレベルを合わせて
	if (TIMEMGR.GetSurviveTime() > SURVIVETIME_LEVELUP * m_level)
	{
		LevelUp();
	}
}

void C_LevelManager::LevelUp()
{
	m_level++;
	m_timeMulti *= TIMEMULTI_LEVEL;
}
