#pragma once
#include "../Chara/CharaManagerConst.h"

class C_ScoreManager
{
public:

	void ResetScore();
	void AddScore(int a_score);
	
	void Update();

	//ゲッター
	int GetScore()const { return(m_score); }
	int GetTargetScore()const { return(m_targetScore); }
	bool GetIsScoreAdded()const { return(m_isScoreAdded); }
	int GetRankingScore(int a_rank, E_WeaponName a_weapon)const { return(m_rankingScore[a_weapon][a_rank]); }
	bool GetIsNewRecord(int a_score, E_WeaponName a_weapon)const;

	//ランキング用
	void LoadRankingScore();
	void SaveRankingScore();
	void UpdateRankingScore(int a_score, E_WeaponName a_weapon);

private:

	static const int MAXSCORE = 99999;
	static const int MINSCORE = 0;

	//ランキング数
	static const int RANKINGNUM = 5;

	//武器種・ランキング毎のスコア
	int m_rankingScore[E_WeaponName::WeaponMax][RANKINGNUM];

	//得点
	int m_score;
	int m_targetScore;

	//1フレームごとに増える点
	static const int SCOREADD = 10;

	//このフレームで点が増えたか
	bool m_isScoreAdded;

	C_ScoreManager() :m_score(0), m_targetScore(0), m_isScoreAdded(false), m_rankingScore() { LoadRankingScore(); }
	~C_ScoreManager() {}

public:

	static C_ScoreManager& GetInstance()
	{
		static C_ScoreManager instance;
		return instance;
	}

};

#define SCOREMGR C_ScoreManager::GetInstance()