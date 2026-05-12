#include "ResultScene.h"
#include "SceneManager.h"
#include "../Background/Background.h"

#include "../Key/KeyStateManager.h"
#include "../Time/TimeManager.h"
#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"

C_ResultScene::C_ResultScene() :m_countF(0), m_nowSelect(E_ResultSelectIndex::PlayAgain), m_isSelect(false), m_rank(0)
{
	SetSceneTag(E_SceneTypeTag::Result);

	m_back = new C_Background();

	//生存時間をスコアに追加
	SCOREMGR.AddScore(TIMEMGR.GetSurviveTime());

	//ランク決定
	int score = SCOREMGR.GetTargetScore();
	for (int i = 0;i < RANKNUM;i++)
	{
		if (RANKTARGET[i] <= score)
		{
			m_rank = i;
			break;
		}
	}

	//ランキング更新
	SCOREMGR.UpdateRankingScore(score, SCENEMGR.GetSelectedWeapon());
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
	if (!SCENEMGR.GetIsStop())
	{
		//操作可能タイミング
		if (m_countF < ENDF)
		{
			m_countF++;

			if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
			{
				m_countF = ENDF;
			}
		}
		else
		{
			if (KEYMGR.GetKeyState(E_KeyChecks::Right) == E_KeyState::Pressed)
			{
				if (m_nowSelect == E_ResultSelectIndex::PlayAgain)m_nowSelect = E_ResultSelectIndex::ReturnTitle;
			}

			if (KEYMGR.GetKeyState(E_KeyChecks::Left) == E_KeyState::Pressed)
			{
				if (m_nowSelect == E_ResultSelectIndex::ReturnTitle)m_nowSelect = E_ResultSelectIndex::PlayAgain;
			}

			if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
			{
				if (m_nowSelect == E_ResultSelectIndex::PlayAgain)
				{
					SCENEMGR.SpawnTransition(E_SceneTypeTag::Game);
				}
				else
				{
					SCENEMGR.SpawnTransition(E_SceneTypeTag::Title);
				}

				m_isSelect = true;
			}
		}
	}

	m_back->Update();
}

void C_ResultScene::Draw()
{
	//背景
	m_back->Draw();

	//ウィンドウ画像
	S_SceneTexData* ResultWindow = SCENEMGR.GetSceneTexData(E_GameTextures::Result_Window);
	Math::Rectangle rec = { 0,0,(long)ResultWindow->m_texSize.x,(long)ResultWindow->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&ResultWindow->m_tex, ResultWindow->m_texPos.x, ResultWindow->m_texPos.y, ResultWindow->m_texDrawSize.x, ResultWindow->m_texDrawSize.y, &rec);

	if(m_countF>=ENDF)
	{
		//ボタン

		//もう一度プレイ
		S_ButtonPosData* playAgain = nullptr;

		//画像
		KdTexture* tex = nullptr;
		if (m_nowSelect == E_ResultSelectIndex::PlayAgain)
		{
			if (m_isSelect && KEYMGR.GetIsPressed(E_KeyChecks::Enter))
			{
				tex = SCENEMGR.GetButtonTex(E_ButtonState::Active);
			}
			else
			{
				tex = SCENEMGR.GetButtonTex(E_ButtonState::Hover);
			}
		}
		else
		{
			tex = SCENEMGR.GetButtonTex(E_ButtonState::Idle);
		}

		playAgain = SCENEMGR.GetButtonData(E_GameButtons::Result_PlayAgain);
		rec = { 0,0,(long)BUTTONTEXSIZE.x,(long)BUTTONTEXSIZE.y };
		SHADER.m_spriteShader.DrawTex(tex, playAgain->m_pos.x, playAgain->m_pos.y, playAgain->m_texDrawSize.x, playAgain->m_texDrawSize.y, &rec);

		//タイトルに戻る
		S_ButtonPosData* returnTitle = nullptr;

		//画像
		if (m_nowSelect == E_ResultSelectIndex::ReturnTitle)
		{
			if (m_isSelect && KEYMGR.GetIsPressed(E_KeyChecks::Enter))
			{
				tex = SCENEMGR.GetButtonTex(E_ButtonState::Active);
			}
			else
			{
				tex = SCENEMGR.GetButtonTex(E_ButtonState::Hover);
			}
		}
		else
		{
			tex = SCENEMGR.GetButtonTex(E_ButtonState::Idle);
		}

		returnTitle = SCENEMGR.GetButtonData(E_GameButtons::Result_Title);
		rec = { 0,0,(long)BUTTONTEXSIZE.x,(long)BUTTONTEXSIZE.y };
		SHADER.m_spriteShader.DrawTex(tex, returnTitle->m_pos.x, returnTitle->m_pos.y, returnTitle->m_texDrawSize.x, returnTitle->m_texDrawSize.y, &rec);

	}
	
	//文字
	for (auto& itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Result))
	{
		if (itr.m_textTag == E_VariableTextsID::Result_ButtonTexts)
		{
			if (m_countF >= ENDF)
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
			}
		}
		else if (itr.m_textTag == E_VariableTextsID::Result_Rank)
		{
			if (m_countF >= RANKF)
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, RANKS[m_rank], itr.m_scale, RESULTCOLOR);
			}
			else
			{
				int randRank = rand() % RANKNUM;
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, RANKS[randRank], itr.m_scale, itr.m_color);
			}
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}

	//数字
	if (m_countF >= TIMEF)
	{
		//生存時間取得
		int time = TIMEMGR.GetSurviveTime();

		int min, sec, frames;
		min = time / 3600;
		sec = time % 3600 / 60;
		frames = time % 60;

		std::string text = FONTMGR.ConvertToTime(min, sec, frames);
		FONTMGR.DrawWord({ -80,100 }, E_TextDrawPos::Center, text, 2, RESULTCOLOR);
	}
	else
	{
		//ランダム
		int min, sec, frames;
		min = rand() % 100;
		sec = rand() % 60;
		frames = rand() % 60;

		std::string text = FONTMGR.ConvertToTime(min, sec, frames);
		FONTMGR.DrawWord({ -80,100 }, E_TextDrawPos::Center, text, 2, { 1,1,1,1 });
	}

	if (m_countF >= SCOREF)
	{
		int score = SCOREMGR.GetTargetScore();
		FONTMGR.DrawNumber({ -80,-30 }, E_TextDrawPos::Center, score, 5, 2, RESULTCOLOR);
	}
	else
	{
		int scoreRand = 0;

		for (int i = 0;i < 5;i++)
		{
			scoreRand *= 10;
			scoreRand += rand() % 10;
		}
		FONTMGR.DrawNumber({ -80,-30 }, E_TextDrawPos::Center, scoreRand, 5, 2, { 1,1,1,1 });
	}
}
