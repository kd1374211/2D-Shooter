#pragma once

static const int STRLENG = 100;

const float PLAYERANGLE = -M_PI_2;
const float ENEMYANGLE = M_PI_2;

enum E_CharaName
{
	Player,
	Max
};

enum E_CharaBaseTexType
{
	Base,
	OnHit,
	TexTypeMax
};

struct S_TexData
{
	KdTexture m_tex;
	int m_animCnt;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
};

struct S_BaseCharaTexData
{
	S_TexData m_texDatas[E_CharaBaseTexType::TexTypeMax];
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

struct S_WeaponTex
{
	S_TexData m_weapon;
	S_TexData m_bullet;
	Math::Vector2 m_texScale;
};