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
}
