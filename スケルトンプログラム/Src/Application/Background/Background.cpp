#include "Background.h"
#include "../Const/ScreenConst.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneBase.h"
#include "../Time/TimeManager.h"

void C_Background::Update()
{
	//ゲームシーン時のみ時間の影響を受ける
	if (SCENEMGR.GetCurrentScene()->GetSceneTag() == E_SceneTypeTag::Game)
	{
		if (TIMEMGR.GetTimeState() == E_TimeState::Normal || TIMEMGR.GetTimeState() == E_TimeState::Half && TIMEMGR.GetHalfTime())
		{
			m_posX += MOVESPEED;
		}
	}
	else
	{
		m_posX += MOVESPEED;
	}

	if (m_posX > m_texWidth)m_posX -= m_texWidth;
}

void C_Background::Draw()
{
	Math::Rectangle rec = { (long)m_posX,0,(long)SCREENSIZEHALF.x,(long)SCREENSIZEHALF.y };
	SHADER.m_spriteShader.DrawTex(&m_bgTex, 0, 0, SCREENSIZE.x, SCREENSIZE.y, &rec);
	Math::Color color = { 1.0f,1.0f,1.0f,0.7f };
	SHADER.m_spriteShader.DrawTex(&m_bgTex2, 0, 0, SCREENSIZE.x, SCREENSIZE.y, &rec, &color);
}

void C_Background::Init()
{
	m_bgTex.Load("Assets/Texture/Map/Background.png");
	m_bgTex2.Load("Assets/Texture/Map/Background2.png");
	m_texWidth = m_bgTex.GetInfo().Width;
	m_posX = 0.0f;
}

void C_Background::Release()
{
	m_bgTex.Release();
	m_bgTex2.Release();
}
