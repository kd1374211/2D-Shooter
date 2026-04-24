#include "Background.h"
#include "../Const/ScreenConst.h"

void C_Background::Update()
{
	m_posX += MOVESPEED;
	if (m_posX > m_texWidth)m_posX -= m_texWidth;
}

void C_Background::Draw()
{
	Math::Rectangle rec = { (long)m_posX,0,(long)SCREENSIZE.x,(long)SCREENSIZE.y };
	SHADER.m_spriteShader.DrawTex(&m_bgTex, 0, 0, SCREENSIZE.x, SCREENSIZE.y, &rec);
}

void C_Background::Init()
{
	m_bgTex.Load("Texture/Map/Background.png");
	m_texWidth = m_bgTex.GetInfo().Width;
	m_posX = 0.0f;
}

void C_Background::Release()
{
	m_bgTex.Release();
}
