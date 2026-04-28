#include "GameScene.h"
#include "../Chara/Player/Player.h"
#include "SceneManager.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/Enemy/EnemyManager.h"
#include "../Key/KeyStateManager.h"

C_GameScene::C_GameScene() :m_player(nullptr), m_back(nullptr)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	m_player = new C_Player(SCENEMGR.GetSelectedWeapon());
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
}
