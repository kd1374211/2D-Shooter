#include "main.h"
#include "Scene.h"
#include "Scene/SceneManager.h"
#include "Key/KeyStateManager.h"
#include "Bullet/BulletManager.h"
#include "Chara/CharaManager.h"

void Scene::Draw2D()
{
	SCENEMGR.Draw();

	//リセット
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);

	// 文字列表示
	//SHADER.m_spriteShader.DrawString(0, 0, "Hello World", Math::Vector4(1, 1, 0, 1));
}

void Scene::Update()
{
    KEYMGR.UpdateKeyState();

	SCENEMGR.Update();
}

void Scene::Init()
{
	SCENEMGR.SetSceneQueue(E_SceneTypeTag::Title);
}

void Scene::Release()
{
	BULLETMGR.ClearBullet();
	CHARAMGR.ClearChara();
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);

		for (int i = 0;i < (int)E_KeyChecks::Max;i++)
		{
			char *key,*keyState;

			switch ((E_KeyChecks)i)
			{
			case E_KeyChecks::Up:
				key = "Up";
				break;
			case E_KeyChecks::Left:
				key = "Left";
				break;
			case E_KeyChecks::Down:
				key = "Down";
				break;
			case E_KeyChecks::Right:
				key = "Right";
				break;
			case E_KeyChecks::Enter:
				key = "Enter";
				break;
			case E_KeyChecks::Space:
				key = "Space";
				break;
			default:
				key = "?";
				break;
			}

			E_KeyState state = KEYMGR.GetKeyState((E_KeyChecks)i);
			switch (state)
			{
			case E_KeyState::Hold:
				keyState = "Hold";
				break;
			case E_KeyState::Pressed:
				keyState = "Pressed";
				break;
			case E_KeyState::Released:
				keyState = "Released";
				break;
			case E_KeyState::None:
				keyState = "None";
				break;
			}

			ImGui::Text("%s Key : %s\n", key, keyState);
		}

		ImGui::Text("Enemy : %d", CHARAMGR.GetEnemy().size());
		ImGui::Text("Bullet : %d", BULLETMGR.GetBullets().size());
	}
	ImGui::End();
}
