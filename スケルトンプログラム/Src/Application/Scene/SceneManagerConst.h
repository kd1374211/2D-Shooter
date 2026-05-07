#pragma once
#include "../Const/TextureConst.h"

enum class E_GameTextures
{
	StatWindow,
	StatBar,
	SelectArrow,
	TopBar,
	ClockIcon,
	FrameBar,
	ResultWindow,
	Transition,
	Max
};

enum class E_GameButtons
{
	Select_Start,
	Result_PlayAgain,
	Result_Title,
	Max
};

enum class E_ButtonState
{
	Idle,
	Hover,
	Active,
	Max
};

enum class E_VariableTextsID
{
	None,
	Select_SelectWeapon,
	Result_Rank,
	Result_ButtonTexts
};

struct S_SceneTexData
{
	KdTexture m_tex;
	Math::Vector2 m_texPos;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texDrawSize;
};

const Math::Vector2 BUTTONTEXSIZE = { 114.0f,38.0f };
struct S_ButtonPosData
{
	Math::Vector2 m_pos;
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