#pragma once

enum class BGM
{
	Ingame,
	Max
};

enum class SE
{
	AC_Shot,
	BSG_Shot,
	TimeStop,
	Max
};

struct S_SoundData
{
	std::shared_ptr<KdSoundEffect> m_sound;
	std::shared_ptr<KdSoundInstance> m_inst;
};