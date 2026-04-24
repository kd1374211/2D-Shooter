#include "TitleScene.h"
#include "../Key/KeyStateManager.h"
#include "SceneManager.h"

C_TitleScene::C_TitleScene()
{
	SetSceneTag(E_SceneTypeTag::Title);
}

void C_TitleScene::Update()
{
	if (KEYMGR.GetKeyState(E_KeyChecks::Enter) == E_KeyState::Released)
	{
		SCENEMGR.SetSceneQueue(E_SceneTypeTag::Select);
	}
}

void C_TitleScene::Draw()
{
}
