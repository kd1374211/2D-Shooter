#pragma once

enum E_BulletType
{
	B_AutoCannon,
	B_BigSpaceGun,
	B_FighterGun,
	BulletMax
};

enum class E_BulletTeam
{
	Player,
	Enemy,
	None
};

struct S_BulletTexData
{
	KdTexture m_tex;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
	Math::Vector2 m_texScale;
};
