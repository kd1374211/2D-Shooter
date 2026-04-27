#pragma once

static const int STRLENG = 100;

const float PLAYERANGLE = -M_PI_2;
const float ENEMYANGLE = M_PI_2;

static const int CHARABASETEXNUM = 8;

enum E_CharaName
{
	Player,
	Max
};

enum E_CharaBaseTexType
{
	Base,
	Engine,
	EngineEffect,
	Weapon,
	OnHit,
	TexTypeMax,
	TexEnd = 999
};

enum E_SelectWeaponTexType
{
	Select_Weapon,
	Select_Engine,
	Select_Fire,
	Select_Max
};

struct S_TexData
{
	KdTexture* m_tex;
	int m_animCnt;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
};

struct S_BaseCharaTexData
{
	std::map<int, S_TexData> m_texDatas;
	Math::Vector2 m_texScale;
	Math::Vector2 m_hitSize;
};

//武器
enum E_WeaponName
{
	AutoCannon,
	BigSpaceGun,
	WeaponMax
};

struct S_PlayerSelectTex
{
	S_TexData m_texDatas[E_SelectWeaponTexType::Select_Max];
	Math::Vector2 m_texScale;
};
