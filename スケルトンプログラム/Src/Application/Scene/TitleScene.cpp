#include "TitleScene.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"
#include "../Background/Background.h"

C_TitleScene::C_TitleScene() :m_alpha(1.0f), m_alphaChangeMulti(-1)
{
	SetSceneTag(E_SceneTypeTag::Title);

	m_back = new C_Background();
	m_titleTex.Load("Texture/Scene/TitleScreen.png");
	m_startButtonTex.Load("Texture/Scene/PressEnter.png");
}

C_TitleScene::~C_TitleScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}
	m_titleTex.Release();
	m_startButtonTex.Release();
}

void C_TitleScene::Update()
{
	m_back->Update();

	m_alpha += ALPHACHANGE * m_alphaChangeMulti;
	if (m_alpha < ALPHAMIN || m_alpha > ALPHAMAX)
	{
		m_alphaChangeMulti *= -1;
	}

	if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Released)
	{
		SCENEMGR.SetSceneQueue(E_SceneTypeTag::Select);
	}
}

void C_TitleScene::Draw()
{
	//背景
	m_back->Draw();

	//タイトル
	long width = m_titleTex.GetInfo().Width;
	long height = m_titleTex.GetInfo().Height;
	Math::Rectangle rec = { 0,0,width,height };
	SHADER.m_spriteShader.DrawTex(&m_titleTex, 0, 0, width, height, &rec);

	//スタート
	width = m_startButtonTex.GetInfo().Width;
	height = m_startButtonTex.GetInfo().Height;
	rec = { 0,0,width,height };
	Math::Color color = { 1,1,1,m_alpha };
	SHADER.m_spriteShader.DrawTex(&m_startButtonTex, 0, 0, width, height, &rec, &color);
}
