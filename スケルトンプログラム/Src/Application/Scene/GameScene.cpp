#include "GameScene.h"
#include "SceneManager.h"

#include "../Const/ScreenConst.h"
#include "../Bullet/BulletManager.h"
#include "../Chara/CharaManager.h"
#include "../Key/KeyStateManager.h"

C_GameScene::C_GameScene() :m_back(nullptr)
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_back = new C_Background();
	CHARAMGR.SpawnPlayer(SCENEMGR.GetSelectedWeapon());

	m_topBarTex.Load("Texture/Scene/Game/IngameTopBar.png");
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
}

void C_GameScene::Update()
{
	if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
	{
		CHARAMGR.SpawnEnemy({ 640.0f,(float)(rand() % 500 - 250)}, E_CharaName::Fighter);
	}

	CHARAMGR.Update();
	BULLETMGR.Update();

	m_back->Update();
}

void C_GameScene::Draw()
{
	m_back->Draw();
	CHARAMGR.Draw();
	
	BULLETMGR.Draw();

	//バー
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	Math::Rectangle rec = { 0,0,(long)m_topBarTex.GetInfo().Width,(long)m_topBarTex.GetInfo().Height };
	SHADER.m_spriteShader.DrawTex(&m_topBarTex, 0, SCREENSIZEHALF.y - m_topBarTex.GetInfo().Height / 2.0f, &rec);
}
