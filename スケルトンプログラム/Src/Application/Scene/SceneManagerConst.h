#pragma once
#include "../Const/TextureConst.h"

enum class E_GameTextures
{
	Title,
	StartButton,
	StatWindow,
	StatBar,
	IngameTopBar,
	TopBarBack,
	ResultWindow,
	Transition,
	Max
};

enum class E_VariableTextsID
{
	None,
	SelectWeapon
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

struct S_TextsData
{
	char m_str[STRLENG];
	E_VariableTextsID m_textTag;
	Math::Vector2 m_pos;
	float m_scale;
	Math::Color m_color;
};