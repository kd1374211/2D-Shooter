#pragma once

class C_ComboManager
{
public:

	//セッター達
	void SetCombo(int a_num) { m_comboCnt = a_num; }
	void Reset() { m_comboCnt = 0; }
	void Add() { m_comboCnt++; }

	//ゲッター
	int GetCombo()const { return(m_comboCnt); }

private:

	int m_comboCnt;

	C_ComboManager() :m_comboCnt(0) {}
	~C_ComboManager(){}

public:

	static C_ComboManager& GetInstance()
	{
		static C_ComboManager instance;
		return instance;
	}

};

#define COMBOMGR C_ComboManager::GetInstance()