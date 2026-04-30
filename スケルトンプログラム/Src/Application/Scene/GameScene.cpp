#include "GameScene.h"
#include "SceneManager.h"

#include "../Const/ScreenConst.h"

#include "../Chara/Player/Player.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Enemy/EnemyManager.h"
#include "../Key/KeyStateManager.h"

C_GameScene::C_GameScene() :m_player(nullptr), m_back(nullptr)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	m_player = new C_Player(SCENEMGR.GetSelectedWeapon());

	m_topBarTex.Load("Texture/Scene/Game/IngameTopBar.png");
}

C_GameScene::~C_GameScene()
{
	if (m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if (m_back)
	{
		delete m_back;
		m_back = nullptr;
	}

	BULLETMGR.ClearBullet();
	ENEMYMGR.ClearEnemy();

	m_topBarTex.Release();
}

void C_GameScene::Update()
{
	if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
	{
		ENEMYMGR.SpawnEnemy({ 640.0f,(float)(rand() % 500 - 250)}, E_CharaName::Fighter);
	}

	m_player->Update();
	ENEMYMGR.Update();
	BULLETMGR.Update();

	m_back->Update();
}

void C_GameScene::Draw()
{
	m_back->Draw();
	ENEMYMGR.Draw();
	m_player->Draw();

	BULLETMGR.Draw();

	//バー
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Rectangle rec = { 0,0,(long)m_topBarTex.GetInfo().Width,(long)m_topBarTex.GetInfo().Height };
	SHADER.m_spriteShader.DrawTex(&m_topBarTex, 0, SCREENSIZEHALF.y - m_topBarTex.GetInfo().Height / 2.0f, &rec);
}
