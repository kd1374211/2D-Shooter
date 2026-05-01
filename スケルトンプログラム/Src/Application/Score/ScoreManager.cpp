#include "ScoreManager.h"

void C_ScoreManager::AddScore(int a_score)
{
	m_score += a_score;
	if (m_score > MAXSCORE)m_score = MAXSCORE;
}

void C_ScoreManager::SubScore(int a_score)
{
	m_score -= a_score;
	if (m_score < MINSCORE)m_score = MINSCORE;
}
