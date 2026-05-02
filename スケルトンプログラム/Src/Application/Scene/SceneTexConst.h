#pragma once

enum class E_GameTextures
{
	Title,
	StartButton,
	StatBar,
	IngameTopBar,
	TopBarBack,
	Max
};

struct S_SceneTexData
{
	KdTexture m_tex;
	Math::Vector2 m_texPos;
	Math::Vector2 m_texSize;
};