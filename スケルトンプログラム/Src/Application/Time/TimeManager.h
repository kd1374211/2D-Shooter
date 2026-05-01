#pragma once

class C_TimeManager
{
public:

	void Update();
	
	//時間シリーズ
	void SetTime(int a_sec) { m_timeF = a_sec * 60; }
	void AddTime(int a_addF);
	void SubTime(int a_subF);

	int GetTime()const { return(m_timeF); }

private:

	static const int MAXTIME = 5999;
	static const int MINTIME = 0;

	//残り時間（F）
	int m_timeF;

	C_TimeManager():m_timeF(0) {}
	~C_TimeManager() {}

public:

	static C_TimeManager& GetInstance()
	{
		static C_TimeManager instance;
		return instance;
	}

};

#define TIMEMGR C_TimeManager::GetInstance()