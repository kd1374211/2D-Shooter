#pragma once

//弾丸種
enum E_BulletType
{
	B_AutoCannon,
	B_BigSpaceGun,
	B_FighterGun,
	BulletMax
};

//どっちの弾か
enum class E_BulletTeam
{
	Player,
	Enemy,
	None
};

//画像
struct S_BulletTexData
{
	KdTexture m_tex;
	int m_texAnimMax;
	float m_texAnimMulti;
	Math::Vector2 m_texSize;
	Math::Vector3 m_texScale;
};

//ステータス
struct S_BulletStatData
{
	float m_hitRadius;
	int m_damage;
};