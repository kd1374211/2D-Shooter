#include "ResultScene.h"
#include "SceneManager.h"

#include "../Key/KeyStateManager.h"
#include "../Time/TimeManager.h"
#include "../Score/ScoreManager.h"
#include "../Fonts/FontManager.h"

void C_ResultScene::Update()
{
	if (KEYMGR.GetIsPressed(E_KeyChecks::Enter))
	{
		SCENEMGR.SetSceneQueue(E_SceneTypeTag::Title);
	}
}

void C_ResultScene::Draw()
{
}
