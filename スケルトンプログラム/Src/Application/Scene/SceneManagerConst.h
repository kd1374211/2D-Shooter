#pragma once
#include "../Const/TextureConst.h"

enum class E_GameTextures
{
	Title_Title,
	Title_PressEnter,
	Select_TopBar,
	Select_StatWindow,
	Select_ShipFrame,
	Select_StatBar,
	Select_Arrow,
	Game_TopBar,
	Game_ClockIcon,
	Game_FrameBar,
	Game_SlowAura,
	Game_StopAura,
	Result_Window,
	Ranking_Window,
	Ranking_GoldCrown,
	Transition,
	Max
};

enum class E_KeyTextures
{
	R,
	Arrows,
	Space,
	Shift,
	Max
};

enum class E_GameButtons
{
	Select_Start,
	Result_PlayAgain,
	Result_Ranking,
	Result_Title,
	Ranking_Return,
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
	Title_PressEnter,
	Select_SelectWeapon,
	Game_TimeCharge,
	Game_TimeControlMode,
	Game_Guide,
	Game_LevelUp,
	Result_NewRecord,
	Result_Rank,
	Result_ButtonTexts,
	Ranking_SelectWeapon
};

struct S_SceneTexData
{
	KdTexture m_tex;
	Math::Vector2 m_texPos;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texDrawSize;
};

struct S_KeyTexData
{
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texDrawSize;
};
struct S_KeyPosData
{
	Math::Vector2 m_pos;
	E_KeyTextures m_key;
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
	E_TextDrawPos m_textPos;
	float m_scale;
	Math::Color m_color;
};