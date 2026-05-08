#pragma once

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

private:

	static const int MAXSCORE = 99999;
	static const int MINSCORE = 0;

	//得点
	int m_score;
	int m_targetScore;

	//1フレームごとに増える点
	int m_scoreAdd;

	//このフレームで点が増えたか
	bool m_isScoreAdded;

	C_ScoreManager() :m_score(0), m_targetScore(0), m_scoreAdd(0), m_isScoreAdded(false) {}
	~C_ScoreManager() {}

public:

	static C_ScoreManager& GetInstance()
	{
		static C_ScoreManager instance;
		return instance;
	}

};

#define SCOREMGR C_ScoreManager::GetInstance()