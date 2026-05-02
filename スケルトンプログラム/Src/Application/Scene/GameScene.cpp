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

#include "../Chara/Enemy/EnemyConst.h"

C_GameScene::C_GameScene() :m_back(nullptr)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	CHARAMGR.SpawnPlayer(SCENEMGR.GetSelectedWeapon());
	TIMEMGR.SetTime(60);
	SCOREMGR.ResetScore();
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
	S_SceneTexData* topBar = SCENEMGR.GetSceneTexData(E_GameTextures::IngameTopBar);
	Math::Rectangle rec = { 0,0,(long)topBar->m_texSize.x,(long)topBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&topBar->m_tex, topBar->m_texPos.x, topBar->m_texPos.y, topBar->m_texDrawSize.x, topBar->m_texDrawSize.y, &rec);

	//タイム
	int timeF = TIMEMGR.GetTime();
	
	//フレーム
	int flame = timeF % 60;
	S_SceneTexData* barBack = SCENEMGR.GetSceneTexData(E_GameTextures::TopBarBack);
	rec = { 0,(long)(barBack->m_texSize.y * (flame / 60.0f)),(long)barBack->m_texSize.x,(long)(barBack->m_texSize.y) };
	SHADER.m_spriteShader.DrawTex(&barBack->m_tex, barBack->m_texPos.x, barBack->m_texPos.y, barBack->m_texDrawSize.x, barBack->m_texDrawSize.y, &rec);
	
	//秒
	int sec = timeF / 60;
	FONTMGR.DrawNumber({ -27,285 }, sec, 0, 2.0f);

	//得点
	FONTMGR.DrawNumber({ 470,300 }, SCOREMGR.GetScore(), 5, 3.5f);
}
