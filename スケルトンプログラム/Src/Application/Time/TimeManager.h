#pragma once

enum class E_TimeState
{
	Normal,
	Half,
	Stop
};

enum class E_TimeChange
{
	None,
	Sub,
	Add
};

class C_TimeManager
{
public:

	void Reset();
	void CheckTimeState();
	void Update();
	void DrawTimeCharge();
	
	//生存時間セッター（デバッグ用）
	void SetSurviveTime(int a_sec) { m_surviveTimeF = a_sec * 60; }

	//時間シリーズ
	void SetTime(int a_sec) { m_timeF = a_sec * 60; }
	void AddTime(int a_addF);
	void SubTime(int a_subF);

	//チャージ
	void AddTimeCharge(int a_amount);
	static const int TIMECHARGE_MAX = 300;

	//セッター
	void SetTimeState(E_TimeState a_state);

	//ゲッター
	int GetTime()const { return(m_timeF); }
	int GetSurviveTime()const { return(m_surviveTimeF); }
	int GetTimeCharge()const { return(m_timeChargeF); }
	E_TimeState GetTimeState()const { return(m_nowTimeState); }
	bool GetHalfTime()const { return(m_countF_state % 2 == 0 ? true : false); }
	E_TimeChange GetTimeChange()const { return(m_timeChange); }

private:

	//タイムゲージ
	int m_timeChargeF;

	//タイムゲージ画像
	const Math::Vector2 texDrawStart = { -570,270 };
	const Math::Vector2 texSize = { 8,12 };
	const Math::Vector2 texDrawSize = { 16,24 };
	static const int BARSECNUM = 25;
	static const int BARSEC_ONE = 5;
	static const int BARSEC_F = 12;
	const int texTypes[BARSEC_ONE] = { 0,1,1,1,2 };

	KdTexture m_timeChargeTex;

	//時間の流れ
	E_TimeState m_nowTimeState;
	int m_countF_state;

	//生存時間
	static const int MAXSURVIVETIME = 359999;
	static const int MAXTIME = 5999;
	static const int MINTIME = 0;

	//生存時間
	int m_surviveTimeF;

	//残り時間（F）
	int m_timeF;

	//時間増減フラグ
	E_TimeChange m_timeChange;

	C_TimeManager() :m_timeF(0), m_surviveTimeF(0), m_timeChargeF(0), m_nowTimeState(E_TimeState::Normal) { Load(); }
	~C_TimeManager() { Release(); }

	void Load();
	void Release();

public:

	static C_TimeManager& GetInstance()
	{
		static C_TimeManager instance;
		return instance;
	}

};

#define TIMEMGR C_TimeManager::GetInstance()