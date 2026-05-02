#include "SceneConst.h"
#include "../Chara/Player/Weapon/WeaponConst.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"

C_SelectScene::C_SelectScene() :m_weaponSelectIndex(E_WeaponName::AutoCannon)
{
	SetSceneTag(E_SceneTypeTag::Select);
}

void C_SelectScene::Update()
{
	if (KEYMGR.GetKeyState(E_KeyChecks::Right) == E_KeyState::Pressed)
	{
		if (m_weaponSelectIndex < E_WeaponName::WeaponMax)m_weaponSelectIndex++;
	}
	else if (KEYMGR.GetKeyState(E_KeyChecks::Left) == E_KeyState::Pressed)
	{
		if (m_weaponSelectIndex > E_WeaponName::AutoCannon)m_weaponSelectIndex--;
	}
	else if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Pressed)
	{
		SCENEMGR.SetSceneQueue(E_SceneTypeTag::Game);
		SCENEMGR.SetSelectedWeapon((E_WeaponName)m_weaponSelectIndex);
	}
}

void C_SelectScene::Draw()
{
	//ステータスバー
	S_SceneTexData* statBar = SCENEMGR.GetSceneTexData(E_GameTextures::StatBar);
	Math::Rectangle rec = { 0,0,(long)statBar->m_texSize.x,(long)statBar->m_texSize.y };
	SHADER.m_spriteShader.DrawTex(&statBar->m_tex, statBar->m_texPos.x, statBar->m_texPos.y, statBar->m_texSize.x, statBar->m_texSize.y, &rec);
}
