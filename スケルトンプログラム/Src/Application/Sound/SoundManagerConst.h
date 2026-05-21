#pragma once

enum class BGM
{
	Title,
	Select,
	Ingame,
	Result,
	Ranking,
	Max
};

enum class SE
{
	Cursor,
	Enter,
	AC_Shot,
	BSG_Shot,
	LevelUp,
	GetHit,
	Explosion,
	FullCharge,
	TimeStop,
	Drum,
	DrumFinish,
	Max
};

struct S_SoundData
{
	std::shared_ptr<KdSoundEffect> m_sound;
	std::shared_ptr<KdSoundInstance> m_inst;
};