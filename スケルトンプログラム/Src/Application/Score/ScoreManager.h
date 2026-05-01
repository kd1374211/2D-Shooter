#pragma once

class C_ScoreManager
{
public:

	void ResetScore() { m_score = 0; }
	void AddScore(int a_score);
	void SubScore(int a_score);

	int GetScore()const { return(m_score); }

private:

	static const int MAXSCORE = 9999;
	static const int MINSCORE = 0;

	//得点
	int m_score;

	C_ScoreManager() :m_score(0) {}
	~C_ScoreManager() {}

public:

	static C_ScoreManager& GetInstance()
	{
		static C_ScoreManager instance;
		return instance;
	}

};

#define SCOREMGR C_ScoreManager::GetInstance()