#include "ScoreManager.h"

void C_ScoreManager::ResetScore()
{
	m_score = 0;
	m_targetScore = 0;
	m_scoreAdd = 0;
}

void C_ScoreManager::AddScore(int a_score)
{
	m_targetScore += a_score;
	if (m_targetScore > MAXSCORE)m_targetScore = MAXSCORE;

	//scoreAdd計算
	int score = m_targetScore - m_score;
	int add = 1;

	while (score >= 10)
	{
		add *= 10;
		score /= 10;
	}

	m_scoreAdd = add;
}

void C_ScoreManager::Update()
{
	m_isScoreAdded = false;
	if (m_scoreAdd == 0)return;

	m_score += m_scoreAdd;
	m_isScoreAdded = true;

	//通り過ぎないよう補正
	if (m_score > m_targetScore)
	{
		m_score = m_targetScore;
		m_scoreAdd = 0;
	}
}
