#include "TitleScene.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"
#include "../Background/Background.h"
#include "../Fonts/FontManager.h"

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

	if (!SCENEMGR.GetIsStop())
	{
		if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Select);
		}
	}
}

void C_TitleScene::Draw()
{
	//背景
	m_back->Draw();

	for (auto &itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Title))
	{
		if (itr.m_textTag == E_VariableTextsID::Title_PressEnter)
		{
			Math::Color color = { itr.m_color.x,itr.m_color.y,itr.m_color.z,m_startButtonAlpha };
			FONTMGR.DrawWord(itr.m_pos,itr.m_textPos, itr.m_str, itr.m_scale, color);
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}
}
