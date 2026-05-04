#include "ResultScene.h"
#include "SceneManager.h"
#include "../Background/Background.h"

#include "../Key/KeyStateManager.h"
#include "../Time/TimeManager.h"
#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"

C_ResultScene::C_ResultScene()
{
	SetSceneTag(E_SceneTypeTag::Result);

	m_back = new C_Background();
}

C_ResultScene::~C_ResultScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}
}

void C_ResultScene::Update()
{
	if (KEYMGR.GetIsPressed(E_KeyChecks::Enter))
	{
		SCENEMGR.SpawnTransition(E_SceneTypeTag::Title);
	}

	m_back->Update();
}

void C_ResultScene::Draw()
{
	//背景
	m_back->Draw();

	//ウィンドウ画像
	S_SceneTexData* ResultWindow = SCENEMGR.GetSceneTexData(E_GameTextures::ResultWindow);
	Math::Rectangle rec = { 0,0,(long)ResultWindow->m_texSize.x,(long)ResultWindow->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&ResultWindow->m_tex, ResultWindow->m_texPos.x, ResultWindow->m_texPos.y, ResultWindow->m_texDrawSize.x, ResultWindow->m_texDrawSize.y, &rec);

	//Result文字
	for (auto& itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Result))
	{
		FONTMGR.DrawWord(itr.m_pos, itr.m_str, itr.m_scale, itr.m_color);
	}
}
