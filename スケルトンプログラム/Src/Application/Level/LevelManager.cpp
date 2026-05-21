#include "LevelManager.h"
#include "../Time/TimeManager.h"
#include "../Sound/SoundManager.h"

void C_LevelManager::Reset()
{
	m_level = 1;
	m_timeMulti = 1.0f;
	m_isLevelUp = false;
}

void C_LevelManager::Update()
{
	//フラグリセット
	m_isLevelUp = false;

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
	m_isLevelUp = true;
	SOUNDMGR.PlaySE(SE::LevelUp);
}
