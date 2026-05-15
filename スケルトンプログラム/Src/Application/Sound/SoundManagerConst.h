#pragma once

enum class BGM
{
	Max
};

enum class SE
{
	AC_Shot,
	BSG_Shot,
	Max
};

struct S_SoundData
{
	std::shared_ptr<KdSoundEffect> m_sound;
	std::shared_ptr<KdSoundInstance> m_inst;
};