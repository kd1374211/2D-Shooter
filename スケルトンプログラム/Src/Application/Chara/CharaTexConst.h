#pragma once

static const int STRLENG = 100;
static const int CHARATEXNUM = 3;

const float PLAYERANGLE = -M_PI_2;
const float ENEMYANGLE = M_PI_2;

enum E_CharaName
{
	Player,
	Max
};

enum E_TexType
{
	Base,
	EngineFire,
	HitImmune,
	Dead,
	TexTypeMax,
	TexEnd = 999
};

struct S_TexData
{
	KdTexture* m_pTex;
	int m_animCnt;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
};

struct S_CharaTexData
{
	std::map<E_TexType, S_TexData> m_tex;
	Math::Vector2 m_texScale;
	Math::Vector2 m_hitSize;
};