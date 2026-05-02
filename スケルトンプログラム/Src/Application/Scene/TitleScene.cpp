#include "TitleScene.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"
#include "../Background/Background.h"

C_TitleScene::C_TitleScene() :m_startButtonAlpha(1.0f), m_alphaChangeMulti(-1)
{
	SetSceneTag(E_SceneTypeTag::Title);

	m_back = new C_Background();
}

C_TitleScene::~C_TitleScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}
}

void C_TitleScene::Update()
{
	m_back->Update();

	m_startButtonAlpha += ALPHACHANGE * m_alphaChangeMulti;
	if (m_startButtonAlpha < ALPHAMIN || m_startButtonAlpha > ALPHAMAX)
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
	S_SceneTexData* title = SCENEMGR.GetSceneTexData(E_GameTextures::Title);
	Math::Rectangle rec = { 0,0,(long)title->m_texSize.x,(long)title->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&title->m_tex, title->m_texPos.x, title->m_texPos.y, title->m_texSize.x, title->m_texSize.y, &rec);

	//スタート
	S_SceneTexData* start = SCENEMGR.GetSceneTexData(E_GameTextures::StartButton);
	rec = { 0,0,(long)start->m_texSize.x,(long)start->m_texSize.y };
	Math::Color color = { 1,1,1,m_startButtonAlpha };
	SHADER.m_spriteShader.DrawTex(&start->m_tex, start->m_texPos.x, start->m_texPos.y, start->m_texSize.x, start->m_texSize.y, &rec, &color);
}
