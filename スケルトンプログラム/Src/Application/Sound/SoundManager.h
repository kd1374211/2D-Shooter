#pragma once
#include "SoundManagerConst.h"

class C_SoundManager
{
public:

	void PlayBGM(BGM a_bgm);
	void PlaySE(SE a_se)const;

	void StopBGM(BGM a_bgm);
	void StopSE(SE a_se)const;

private:

	C_SoundManager() { Init(); }
	~C_SoundManager() { StopAll(); }

	void Init();
	void LoadBGM();
	void LoadSE();
	void StopAll();

	S_SoundData m_seData[(int)SE::Max];

public:

	static C_SoundManager& GetInstance()
	{
		static C_SoundManager instance;
		return instance;
	}

};

#define SOUNDMGR C_SoundManager::GetInstance()