#include "GameScene.h"
#include "SceneManager.h"

#include "../Const/ScreenConst.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/CharaManager.h"
#include "../Key/KeyStateManager.h"
#include "../Hit/HitCheck.h"
#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"
#include "../Level/LevelManager.h"

#include "../Chara/Enemy/EnemyConst.h"
#include "../Chara/Player/Player.h"

C_GameScene::C_GameScene() :m_back(nullptr), m_timeColor(1, 1, 1, 1), m_alphaChangeMulti_timeChargeMax(1.0f), m_textAlpha_timeChargeMax(1.0f), m_textAlpha_levelUp(MAXALPHA_LU), m_alphaChangeMulti_levelUp(-1.0f), m_isLevelUpText(false), m_countF_levelUp(0), m_currentState(E_TimeState::Normal), m_countF_timeState(0)
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
		if (isEnemySpawn)CHARAMGR.CheckEnemySpawn();

		//debug
		if (GetAsyncKeyState('0') & 0x8000)
		{
			TIMEMGR.SubTime(TIMEMGR.GetTime());
		}

		if (TIMEMGR.GetTime() <= 0)
		{
			SCENEMGR.SpawnTransition(E_SceneTypeTag::Result);
		}

		//Debug Keys
		if (GetAsyncKeyState('1') & 0x8000)
		{
			TIMEMGR.AddTime(20);
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
			TIMEMGR.SetTimeCharge(120);
		}

		if (GetAsyncKeyState('5') & 0x8000)
		{
			TIMEMGR.AddTimeCharge(10);
		}

		if (GetAsyncKeyState('6') & 0x8000)
		{
			TIMEMGR.SetSurviveTime(30);
		}
		if (GetAsyncKeyState('7') & 0x8000)
		{
			TIMEMGR.SetSurviveTime(60);
		}
		if (GetAsyncKeyState('8') & 0x8000)
		{
			TIMEMGR.SetSurviveTime(90);
		}
		if (GetAsyncKeyState('9') & 0x8000)
		{
			TIMEMGR.AddSurviveTime(1);
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (!isPressedAS)
			{
				isEnemySpawn = false;
			}
			isPressedAS = true;
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			if (!isPressedAS)
			{
				isEnemySpawn = true;
			}
			isPressedAS = true;
		}
		else
		{
			isPressedAS = false;
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			if (!isPressedQWE)
			{
				CHARAMGR.SpawnEnemy({ 658.0f,40 }, E_CharaName::Fighter);
			}
			isPressedQWE = true;
		}
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			if (!isPressedQWE)
			{
				CHARAMGR.SpawnEnemy({ 661.0f,-60 }, E_CharaName::Bomber);
			}
			isPressedQWE = true;
		}
		else if (GetAsyncKeyState('E') & 0x8000)
		{
			if (!isPressedQWE)
			{
				CHARAMGR.SpawnEnemy({ 652.0f,-160 }, E_CharaName::Torpedo);
			}
			isPressedQWE = true;
		}
		else
		{
			isPressedQWE = false;
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
	UpdateTimeChargeAlpha();

	UpdateLevelUpAlpha();
	UpdateTimeAura();
}

void C_GameScene::Draw()
{
	//画像
	m_back->Draw();
	CHARAMGR.Draw();
	
	//減速オーラ
	if (m_countF_timeState > 0)
	{
		if (m_currentState == E_TimeState::Half)
		{
			S_SceneTexData* slowAura = SCENEMGR.GetSceneTexData(E_GameTextures::Game_SlowAura);
			Math::Rectangle rec = { 0,0,(long)slowAura->m_texSize.x,(long)slowAura->m_texSize.y };
			Math::Vector2 DrawSize = slowAura->m_texSize * GetAuraScale();
			Math::Color color = { 1,1,1,0.1f };
			SHADER.m_spriteShader.DrawTex(&slowAura->m_tex, slowAura->m_texPos.x, slowAura->m_texPos.y, DrawSize.x, DrawSize.y, &rec, &color);
		}
		else if (m_currentState == E_TimeState::Stop)
		{
			S_SceneTexData* stopAura = SCENEMGR.GetSceneTexData(E_GameTextures::Game_StopAura);
			Math::Rectangle rec = { 0,0,(long)stopAura->m_texSize.x,(long)stopAura->m_texSize.y };
			Math::Vector2 DrawSize = stopAura->m_texSize * GetAuraScale();
			Math::Color color = { 1,1,1,0.2f };
			SHADER.m_spriteShader.DrawTex(&stopAura->m_tex, stopAura->m_texPos.x, stopAura->m_texPos.y, DrawSize.x, DrawSize.y, &rec, &color);
		}
	}
	

	BULLETMGR.Draw();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//キー色々
	for (auto& itr : SCENEMGR.GetKeyPosData(E_SceneTypeTag::Game))
	{
		S_KeyTexData* data = SCENEMGR.GetKeyTexData(itr.m_key);

		Math::Vector2 playerPos = CHARAMGR.GetPlayer()->GetPos();
		Math::Color color = playerPos.y > GUIDEALPHACHANGE_Y ? Math::Color(1, 1, 1, TRANSPARENTGUIDEALPHA) : Math::Color(1, 1, 1, DEFAULTGUIDEALPHA);
		Math::Rectangle rec = { 0,0,(long)data->m_texSize.x ,(long)data->m_texSize.y };
		SHADER.m_spriteShader.DrawTex(&data->m_tex, itr.m_pos.x, itr.m_pos.y, data->m_texDrawSize.x, data->m_texDrawSize.y, &rec, &color);
	}

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
			if (TIMEMGR.GetIsMaxCharge())
			{
				std::string text = itr.m_str;
				text.append(" MAX!");
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, text, itr.m_scale, { 0.8f,0.2f,0.2f,m_textAlpha_timeChargeMax });
			}
			else
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
			}
		}
		else if (itr.m_textTag == E_VariableTextsID::Game_Guide)
		{
			Math::Vector2 playerPos = CHARAMGR.GetPlayer()->GetPos();
			if (playerPos.y > GUIDEALPHACHANGE_Y)
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, Math::Color(1, 1, 1, TRANSPARENTGUIDEALPHA));
			}
			else
			{
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
			}
		}
		else if (itr.m_textTag == E_VariableTextsID::Game_LevelUp)
		{
			if (m_isLevelUpText)
			{
				Math::Color baseColor = itr.m_color;
				Math::Color color = { baseColor.x,baseColor.y,baseColor.z,m_textAlpha_levelUp };
				FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, color);
			}
		}
		else
		{
			FONTMGR.DrawWord(itr.m_pos, itr.m_textPos, itr.m_str, itr.m_scale, itr.m_color);
		}
	}

	//秒
	int sec = timeF / 60;
	FONTMGR.DrawNumber({ 30,300 },E_TextDrawPos::Center, sec, 2, 3.0f, m_timeColor);

	//レベル
	int level = LEVELMGR.GetLevel();
	FONTMGR.DrawNumber({ 60,345 }, E_TextDrawPos::Center, level, 1, 1.25f, level > ENEMYMAXLEVEL ? LEVELCOLOR[ENEMYMAXLEVEL - 1] : LEVELCOLOR[level - 1]);

	//得点
	FONTMGR.DrawNumber({ 490,280 }, E_TextDrawPos::Center, SCOREMGR.GetScore(), 5, SCOREMGR.GetIsScoreAdded() ? 3.5f : 3.0f, Math::Color(1, 1, 1, 1));
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

void C_GameScene::UpdateTimeChargeAlpha()
{
	if (!TIMEMGR.GetIsMaxCharge())return;

	//今たまったならalphaリセット
	if (TIMEMGR.GetIsMaxCharged())ResetTimeChargeAlpha();

	//α更新
	m_textAlpha_timeChargeMax += ALPHACHANGE_TCM * m_alphaChangeMulti_timeChargeMax;

	//反転チェック
	if (m_textAlpha_timeChargeMax <= MINALPHA_TCM || m_textAlpha_timeChargeMax >= MAXALPHA_TCM)m_alphaChangeMulti_timeChargeMax *= -1;
}

void C_GameScene::ResetTimeChargeAlpha()
{
	m_alphaChangeMulti_timeChargeMax = -1.0f;
	m_textAlpha_timeChargeMax = MAXALPHA_TCM;
}

void C_GameScene::UpdateLevelUpAlpha()
{
	//このフレームで上がったならalphaリセット
	if (LEVELMGR.GetIsLevelUp())ResetLevelUpAlpha();

	//文字出さないならリターン
	if (!m_isLevelUpText)return;

	//α更新
	m_textAlpha_levelUp += m_alphaChangeMulti_levelUp * ALPHACHANGE_LU;

	//反転チェック
	if (m_textAlpha_levelUp <= MINALPHA_LU || m_textAlpha_levelUp >= MAXALPHA_LU)m_alphaChangeMulti_levelUp *= -1;

	//フレーム更新
	m_countF_levelUp--;
	if (m_countF_levelUp <= 0)m_isLevelUpText = false;
}

void C_GameScene::ResetLevelUpAlpha()
{
	m_textAlpha_levelUp = MAXALPHA_LU;
	m_alphaChangeMulti_levelUp = -1.0f;
	m_isLevelUpText = true;
	m_countF_levelUp = LEVELUPTEXTF;
}

void C_GameScene::UpdateTimeAura()
{
	if (TIMEMGR.GetTimeState() != E_TimeState::Normal)
	{
		if (m_currentState != TIMEMGR.GetTimeState())
		{
			m_currentState = TIMEMGR.GetTimeState();
			m_countF_timeState = 0;
		}
	}

	//通常時ならサイズ減少
	if (TIMEMGR.GetTimeState() == E_TimeState::Normal)
	{
		//サイズ減少
		if (m_countF_timeState > 0)m_countF_timeState--;
	}
	else
	{
		//サイズ増加
		if (m_countF_timeState < AURASCALEMAXF)m_countF_timeState++;
	}
	
}

float C_GameScene::GetAuraScale()
{
	return m_countF_timeState * m_countF_timeState * AURASCALEMULTI;
}
