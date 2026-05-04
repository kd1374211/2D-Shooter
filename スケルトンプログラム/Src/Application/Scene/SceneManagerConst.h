#pragma once

enum class E_GameTextures
{
	Title,
	StartButton,
	StatWindow,
	StatBar,
	IngameTopBar,
	TopBarBack,
	Transition,
	Max
};

struct S_SceneTexData
{
	KdTexture m_tex;
	Math::Vector2 m_texPos;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texDrawSize;
};

struct S_SelectWeaponStat
{
	int m_damage;
	int m_rate;
	int m_speed;
};