#pragma once
#include "SoundManagerConst.h"

class C_SoundManager
{
public:

	void PlayBGM(BGM a_bgm)const;
	void PlaySE(SE a_se)const;

	void PauseBGM(BGM a_bgm)const { if (!m_bgmData[(int)a_bgm].m_inst->IsPause())m_bgmData[(int)a_bgm].m_inst->Pause(); }
	void ResumeBGM(BGM a_bgm)const { if (m_bgmData[(int)a_bgm].m_inst->IsPause())m_bgmData[(int)a_bgm].m_inst->Resume(); }
	void SlowTime();
	void SlowEnd();
	
	void StopBGM()const;
	void StopSE(SE a_se)const;

	void Reset();

private:

	C_SoundManager() { Init(); }
	~C_SoundManager() { StopAll(); }

	void Init();
	void LoadBGM();
	void LoadSE();
	void StopAll();

	S_SoundData m_bgmData[(int)BGM::Max];
	S_SoundData m_seData[(int)SE::Max];

	const float INGAMEBGMVOL_SLOW = 0.05f;
	const float INGAMEBGMVOL = 0.15f;

public:

	static C_SoundManager& GetInstance()
	{
		static C_SoundManager instance;
		return instance;
	}

};

#define SOUNDMGR C_SoundManager::GetInstance()