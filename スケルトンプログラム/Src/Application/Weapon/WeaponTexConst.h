#pragma once

const float TEXANGLE = -M_PI_2;

enum E_WeaponName
{
	AutoCannon,
	BigSpaceGun,
	WeaponMax
};

struct S_TexAnimData
{
	KdTexture m_tex;
	Math::Vector2 m_texSize;
	int m_animCntMax;
	float m_animCntMulti;
};

struct S_WeaponTex
{
	S_TexAnimData m_weapon;
	S_TexAnimData m_bullet;
	Math::Vector2 m_texScale;
};