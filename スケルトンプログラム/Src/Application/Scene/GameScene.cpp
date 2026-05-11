#include "GameScene.h"
#include "SceneManager.h"

#include "../Const/ScreenConst.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/CharaManager.h"
#include "../Key/KeyStateManager.h"
#include "../Hit/HitCheck.h"
#include "../Time/TimeManager.h"
#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"
#include "../Level/LevelManager.h"

#include "../Chara/Enemy/EnemyConst.h"

C_GameScene::C_GameScene() :m_back(nullptr), m_timeColor(1, 1, 1, 1)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	CHARAMGR.SpawnPlayer(SCENEMGR.GetSelectedWeapon(), PLAYERSPAWNPOS);
	LEVELMGR.Reset();
	TIMEMGR.Reset();
	TIMEMGR.SetTime(60);
	SCOREMGR.ResetScore();
	CHARAMGR.RestartGame();
}

C_GameScene::~C_GameScene()
{
	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}

	BULLETMGR.ClearBullet();
	CHARAMGR.ClearChara();
}

void C_GameScene::Update()
{
	if (!SCENEMGR.GetIsStop())
	{
		//先に減速管理
		TIMEMGR.CheckTimeState();
		TIMEMGR.Update();

		//レベル更新
		LEVELMGR.Update();

		//召喚
		CHARAMGR.CheckEnemySpawn();

		if (GetAsyncKeyState('0') & 0x8000)
		{
			TIMEMGR.SubTime(TIMEMGR.GetTime());
		}

		if (TIMEMGR.GetTime() <= 0)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Result);
		}

		if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
		{
			CHARAMGR.SpawnEnemy({ 640.0f,(float)(rand() % 500 - 250) }, E_CharaName::Torpedo);
		}

		if (GetAsyncKeyState('1') & 0x8000)
		{
			TIMEMGR.AddTime(5);
		}

		if (GetAsyncKeyState('2') & 0x8000)
		{
			TIMEMGR.SetTime(60);
		}

		if (GetAsyncKeyState('3') & 0x8000)
		{
			SCOREMGR.AddScore(100);
		}

		if (GetAsyncKeyState('4') & 0x8000)
		{
			TIMEMGR.AddTimeCharge(-5);
		}

		if (GetAsyncKeyState('5') & 0x8000)
		{
			TIMEMGR.AddTimeCharge(10);
		}
	}

	//停止状態で動ける要素後で考える
	CHARAMGR.Update();
	BULLETMGR.Update();

	HITCHECK.Check();

	CHARAMGR.CheckEnemyDelete();
	BULLETMGR.CheckBulletDelete();

	SCOREMGR.Update();

	m_back->Update();
	UpdateTimeColor();
}

void C_GameScene::Draw()
{
	//画像
	m_back->Draw();
	CHARAMGR.Draw();
	
	BULLETMGR.Draw();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//バー
	S_SceneTexData* topBar = SCENEMGR.GetSceneTexData(E_GameTextures::Game_TopBar);
	Math::Rectangle rec = { 0,0,(long)topBar->m_texSize.x,(long)topBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&topBar->m_tex, topBar->m_texPos.x, topBar->m_texPos.y, topBar->m_texDrawSize.x, topBar->m_texDrawSize.y, &rec);

	//時計
	S_SceneTexData* clock = SCENEMGR.GetSceneTexData(E_GameTextures::Game_ClockIcon);
	rec = { 0,0,(long)clock->m_texSize.x,(long)clock->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&clock->m_tex, clock->m_texPos.x, clock->m_texPos.y, clock->m_texDrawSize.x, clock->m_texDrawSize.y, &rec);

	//タイムゲージ
	TIMEMGR.DrawTimeCharge();

	//時間取得
	int timeF = TIMEMGR.GetTime();

	//フレームバー
	int flame = timeF % 60;

	S_SceneTexData* frameBar = SCENEMGR.GetSceneTexData(E_GameTextures::Game_FrameBar);
	rec = { (long)(flame / 10 * frameBar->m_texSize.x),0,(long)frameBar->m_texSize.x,(long)frameBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&frameBar->m_tex, frameBar->m_texPos.x, frameBar->m_texPos.y, frameBar->m_texDrawSize.x, frameBar->m_texDrawSize.y, &rec);
	
	//文字
	for (auto& itr : SCENEMGR.GetSceneTextsData(E_SceneTypeTag::Game))
	{
		if (itr.m_textTag == E_VariableTextsID::Game_TimeCharge)
		{
			if (TIMEMGR.GetTimeCharge() == TIMEMGR.TIMECHARGE_MAX)
			{
				std::string text = itr.m_str;
				text.append(" MAX");
				FONTMGR.DrawWord(itr.m_pos, text, itr.m_scale, { 0.8f,0.2f,0.2f,1 });
			}
			else
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_str, itr.m_scale, itr.m_color);
			}
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}

	//秒
	int sec = timeF / 60;
	FONTMGR.DrawNumber({ 30,310 }, sec, 2, 3.0f, m_timeColor);

	//得点
	FONTMGR.DrawNumber({ 490,280 }, SCOREMGR.GetScore(), 5, SCOREMGR.GetIsScoreAdded() ? 3.5f : 3.0f, Math::Color(1, 1, 1, 1));
}

void C_GameScene::UpdateTimeColor()
{
	switch (TIMEMGR.GetTimeChange())
	{
	case E_TimeChange::None:
		if (m_timeColor.x < 1.0f)m_timeColor.x += 0.1f;
		if (m_timeColor.y < 1.0f)m_timeColor.y += 0.1f;
		if (m_timeColor.z < 1.0f)m_timeColor.z += 0.1f;
		break;
	case E_TimeChange::Add:
		m_timeColor = { 0,1,0,1 };
		break;
	case E_TimeChange::Sub:
		m_timeColor = { 1,0,0,1 };
		break;
	}
}
