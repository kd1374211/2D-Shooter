#include "GameScene.h"
#include "SceneManager.h"

#include "../Const/ScreenConst.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/CharaManager.h"
#include "../Key/KeyStateManager.h"
#include "../Hit/HitCheck.h"
#include "../Time/TimeManager.h"
#include "../Score/ScoreManager.h"
#include "../Number/Number.h"

#include "../Chara/Enemy/EnemyConst.h"

C_GameScene::C_GameScene() :m_back(nullptr)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	CHARAMGR.SpawnPlayer(SCENEMGR.GetSelectedWeapon());
	TIMEMGR.SetTime(60);
	SCOREMGR.ResetScore();

	m_topBarTex.Load("Texture/Scene/Game/IngameTopBar.png");
	m_topBarBackTex.Load("Texture/Scene/Game/IngameTopBar_Back.png");
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

	m_topBarTex.Release();
	m_topBarBackTex.Release();
}

void C_GameScene::Update()
{
	if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
	{
		CHARAMGR.SpawnEnemy({ 640.0f,(float)(rand() % 500 - 250)}, E_CharaName::Fighter);
	}

	if (GetAsyncKeyState('1') & 0x8000)
	{
		for (auto itr : CHARAMGR.GetEnemy())
		{
			itr->GetHit(1);
		}
	}

	if (GetAsyncKeyState('2') & 0x8000)
	{
		SCOREMGR.AddScore(1);
	}

	if (GetAsyncKeyState('3') & 0x8000)
	{
		SCOREMGR.AddScore(100);
	}

	CHARAMGR.Update();
	BULLETMGR.Update();

	HITCHECK.Check();

	CHARAMGR.CheckEnemyDelete();
	BULLETMGR.CheckBulletDelete();

	TIMEMGR.Update();
	m_back->Update();
}

void C_GameScene::Draw()
{
	m_back->Draw();
	CHARAMGR.Draw();
	
	BULLETMGR.Draw();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	//バー
	Math::Rectangle rec = { 0,0,(long)m_topBarTex.GetInfo().Width,(long)m_topBarTex.GetInfo().Height };
	SHADER.m_spriteShader.DrawTex(&m_topBarTex, 0, SCREENSIZEHALF.y - m_topBarTex.GetInfo().Height / 2.0f, &rec);

	//タイム
	int timeF = TIMEMGR.GetTime();
	
	//フレーム
	int flame = timeF % 60;
	rec = { 0,0,(long)m_topBarBackTex.GetInfo().Width,(long)(m_topBarBackTex.GetInfo().Height * flame / 60.0f) };
	SHADER.m_spriteShader.DrawTex(&m_topBarBackTex, -27.0f, 253.0f + rec.height / 2.0f, &rec);

	//秒
	int sec = timeF / 60;
	NUMBER.DrawNumber({ -27,285 }, sec, 0, 1.0f);

	//得点
	NUMBER.DrawNumber({ 470,300 }, SCOREMGR.GetScore(), 4, 2.0f);
}
