#pragma once

static const int STRLENG = 100;
static const int CHARATEXNUM = 5;

enum E_CharaName
{
	Player,
	Max
};

enum E_TexType
{
	Base,
	Engine,
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
};

struct S_CharaTexData
{
	std::map<E_TexType, S_TexData> m_texData;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texScale;
	Math::Vector2 m_hitSize;
};