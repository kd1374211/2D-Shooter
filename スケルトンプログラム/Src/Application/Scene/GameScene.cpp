#include "GameScene.h"
#include "../Chara/Player/Player.h"

C_GameScene::C_GameScene()
{
	SetSceneTag(E_SceneTypeTag::Game);
	m_player = new C_Player();
}

void C_GameScene::Update()
{
	m_player->Action();
	m_player->Update();
}

void C_GameScene::Draw()
{
	m_player->Draw();
}
