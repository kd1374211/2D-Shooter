#include "RankingScene.h"
#include "SceneManager.h"

#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"
#include "../Key/KeyStateManager.h"
#include "../Background/Background.h"

C_RankingScene::C_RankingScene(E_SceneTypeTag a_scene) :m_nowRanking(E_WeaponName::AutoCannon)
{
	m_back = new C_Background();
	m_backScene = a_scene;
	m_nowRanking = SCENEMGR.GetSelectedWeapon();
}

C_RankingScene::~C_RankingScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}
}

void C_RankingScene::Update()
{
	if (!SCENEMGR.GetIsStop())
	{
		//選択
		if (KEYMGR.GetKeyState(E_KeyChecks::Right) == E_KeyState::Pressed)
		{
			if (m_nowRanking < E_WeaponName::BigSpaceGun)m_nowRanking++;
		}
		else if (KEYMGR.GetKeyState(E_KeyChecks::Left) == E_KeyState::Pressed)
		{
			if (m_nowRanking > E_WeaponName::AutoCannon)m_nowRanking--;
		}

		//戻る
		if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
		{
			SCENEMGR.SpawnTransition(m_backScene);
		}
	}

	//背景
	m_back->Update();
}

void C_RankingScene::Draw()
{
	//画像
	m_back->Draw();

	//ウィンドウ
	S_SceneTexData* window = SCENEMGR.GetSceneTexData(E_GameTextures::Ranking_Window);
	Math::Rectangle rec = { 0,0,(long)window->m_texSize.x,(long)window->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&window->m_tex, window->m_texPos.x, window->m_texPos.y, window->m_texDrawSize.x, window->m_texDrawSize.y, &rec);

	std::string name = {};

	//矢印
	S_SceneTexData* selectArrow = SCENEMGR.GetSceneTexData(E_GameTextures::Select_Arrow);
	rec = { 0,0,(long)selectArrow->m_texSize.x,(long)selectArrow->m_texSize.y };

	//一番左じゃなければ
	if (m_nowRanking != E_WeaponName::AutoCannon)
	{
		SHADER.m_spriteShader.DrawTex(&selectArrow->m_tex, -(ARROWPOS.x), ARROWPOS.y, -(selectArrow->m_texDrawSize.x), selectArrow->m_texDrawSize.y, &rec);
	}

	//一番右じゃなければ
	if (m_nowRanking != E_WeaponName::BigSpaceGun)
	{
		SHADER.m_spriteShader.DrawTex(&selectArrow->m_tex, ARROWPOS.x, ARROWPOS.y, selectArrow->m_texDrawSize.x, selectArrow->m_texDrawSize.y, &rec);
	}

	//王冠
	S_SceneTexData* goldCrown = SCENEMGR.GetSceneTexData(E_GameTextures::Ranking_GoldCrown);
	rec = { 0,0,(long)goldCrown->m_texSize.x,(long)goldCrown->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&goldCrown->m_tex, -350.0f, RANKINGPOSY[0], goldCrown->m_texDrawSize.x, goldCrown->m_texDrawSize.y, &rec);

	//決定ボタン
	S_ButtonPosData* returnButton = nullptr;
	KdTexture* tex = nullptr;
	returnButton = SCENEMGR.GetButtonData(E_GameButtons::Ranking_Return);

	//決定後かつ決定ボタンを押しているか
	if (KEYMGR.GetIsPressed(E_KeyChecks::Enter))
	{
		tex = SCENEMGR.GetButtonTex(E_ButtonState::Active);
	}
	else
	{
		tex = SCENEMGR.GetButtonTex(E_ButtonState::Hover);
	}
	rec = { 0,0,(long)BUTTONTEXSIZE.x,(long)BUTTONTEXSIZE.y };
	SHADER.m_spriteShader.DrawTex(tex, returnButton->m_pos.x, returnButton->m_pos.y, returnButton->m_texDrawSize.x, returnButton->m_texDrawSize.y, &rec);

	//選択武器名
	switch (m_nowRanking)
	{
	case E_WeaponName::AutoCannon:
		name = "Dual Gun";
		break;
	case E_WeaponName::BigSpaceGun:
		name = "Ball Launcher";
		break;
	default:
		name = "ERROR";
		break;
	}

	//文字
	for (auto& itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Ranking))
	{
		if (itr.m_textTag == E_VariableTextsID::Ranking_SelectWeapon)
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, name, itr.m_scale, itr.m_color);
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}

	//ランキング
	for (int i = 0;i < RANKINGNUM;i++)
	{
		std::string rank = std::to_string(i + 1);
		switch (i)
		{
		case 0:
			rank += "st";
			break;
		case 1:
			rank += "nd";
			break;
		case 2:
			rank += "rd";
			break;
		case 3:
		case 4:
			rank += "th";
			break;
		}
		//順位
		FONTMGR.DrawWord({ RANKINGPOSX_RANK,RANKINGPOSY[i] }, E_TextDrawPos::Right, rank, RANKINGSCALE, RANKINGCOLOR[i]);

		//スコア
		FONTMGR.DrawNumber({ RANKINGPOSX_SCORE,RANKINGPOSY[i] }, E_TextDrawPos::Left, SCOREMGR.GetRankingScore(i, (E_WeaponName)m_nowRanking), 5, RANKINGSCALE, RANKINGCOLOR[i]);
	}
}
