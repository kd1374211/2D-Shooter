#include "ScoreManager.h"
#include "../Const/TextureConst.h"

void C_ScoreManager::ResetScore()
{
	m_score = 0;
	m_targetScore = 0;
}

void C_ScoreManager::AddScore(int a_score)
{
	m_targetScore += a_score;
	if (m_targetScore > MAXSCORE)m_targetScore = MAXSCORE;
}

void C_ScoreManager::Update()
{
	m_isScoreAdded = false;

	//上がりきったならリターン
	if (m_targetScore == m_score)return;

	m_score += SCOREADD;
	m_isScoreAdded = true;

	//通り過ぎないよう補正
	if (m_score > m_targetScore)
	{
		m_score = m_targetScore;
	}
}

bool C_ScoreManager::GetIsNewRecord(int a_score, E_WeaponName a_weapon) const
{
	if (m_rankingScore[a_weapon][0] == a_score)return(true);

	return(false);
}

void C_ScoreManager::LoadRankingScore()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Score/ScoreSave.txt", "r") == 0)
	{
		for (int i = 0;i < E_WeaponName::WeaponMax;i++)
		{
			for (int j = 0;j < RANKINGNUM;j++)
			{
				fscanf_s(fp, "%d,",
					&m_rankingScore[i][j]
				);
			}

			char dummy[STRLENG];
			fgets(dummy, STRLENG, fp);
		}

		fclose(fp);
	}
}

void C_ScoreManager::SaveRankingScore()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Score/ScoreSave.txt", "w") == 0)
	{
		for (int i = 0;i < E_WeaponName::WeaponMax;i++)
		{
			for (int j = 0;j < RANKINGNUM;j++)
			{
				fprintf_s(fp, "%d,",
					m_rankingScore[i][j]
				);
			}

			fprintf_s(fp, "\n");
		}

		fclose(fp);
	}
}

void C_ScoreManager::UpdateRankingScore(int a_score, E_WeaponName a_weapon)
{
	//順位確認
	int i;
	for (i = 0;i < RANKINGNUM;i++)
	{
		if (m_rankingScore[a_weapon][i] < a_score)break;
	}

	//ランク外ならリターン
	if (i == RANKINGNUM)return;

	//入れ替え作業
	int work = a_score;
	for (;i < RANKINGNUM;i++)
	{
		int work2 = m_rankingScore[a_weapon][i];
		m_rankingScore[a_weapon][i] = work;
		work = work2;
	}

	//セーブ
	SaveRankingScore();
}
