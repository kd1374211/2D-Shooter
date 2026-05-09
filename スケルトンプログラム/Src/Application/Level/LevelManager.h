#pragma once

class C_LevelManager
{
public:

	void Reset();

	void Update();

	//ゲッター
	float GetTimeMulti()const { return(m_timeMulti); }
	int GetLevel()const { return(m_level); }
	int GetTargetWeight()const;

private:

	//レベル増加毎の時間入手量
	const float TIMEMULTI_LEVEL = 0.9f;

	//レベル増加時間
	static const int SURVIVETIME_LEVELUP = 1800;

	//現在レベル
	int m_level;

	//時間獲得倍率
	float m_timeMulti;

	C_LevelManager() :m_level(0), m_timeMulti(0) {};
	~C_LevelManager(){}

	//レベル増加
	void LevelUp();

	//レベルに合わせて敵の出現
	void Spawn();

public:

	static C_LevelManager& GetInstance()
	{
		static C_LevelManager instance;
		return instance;
	}

};

#define LEVELMGR C_LevelManager::GetInstance()