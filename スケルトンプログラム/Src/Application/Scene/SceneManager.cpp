#include "SceneManager.h"
#include "../Const/TextureConst.h"
#include "../Sound/SoundManager.h"

void C_SceneManager::Update()
{
	if (m_sceneQueue != E_SceneTypeTag::None)
	{
		SetScene(m_sceneQueue);

		m_sceneQueue = E_SceneTypeTag::None;
	}

	if (m_pTransition != nullptr)
	{
		m_pTransition->Update();

		if (m_pTransition->GetIsEnd())
		{
			delete m_pTransition;
			m_pTransition = nullptr;
			m_isStop = false;
		}
	}

	if (m_pCurrentScene == nullptr)return;

	m_pCurrentScene->Update();
}

void C_SceneManager::Draw()
{
	if (m_pCurrentScene != nullptr)m_pCurrentScene->Draw();
	if (m_pTransition != nullptr)m_pTransition->Draw();
}

void C_SceneManager::SpawnTransition(E_SceneTypeTag a_nextScene)
{
	if (m_pTransition == nullptr)
	{
		m_pTransition = new C_Transition(a_nextScene);
		m_isStop = true;
	}
}

void C_SceneManager::SetScene(E_SceneTypeTag a_tag)
{
	//BGM stop
	SOUNDMGR.StopBGM();

	E_SceneTypeTag scene = E_SceneTypeTag::None;
	if (m_pCurrentScene != nullptr)
	{
		if (a_tag == E_SceneTypeTag::Ranking)
		{
			switch (m_pCurrentScene->GetSceneTag())
			{
			case E_SceneTypeTag::Result:
				scene = E_SceneTypeTag::Title;
				break;
			case E_SceneTypeTag::Select:
				scene = E_SceneTypeTag::Select;
				break;
			default:
				scene = E_SceneTypeTag::Title;
				break;
			}
		}
		delete m_pCurrentScene;
	}

	switch (a_tag)
	{
	case E_SceneTypeTag::Title:
		m_pCurrentScene = new C_TitleScene();
		break;
	case E_SceneTypeTag::Select:
		m_pCurrentScene = new C_SelectScene();
		break;
	case E_SceneTypeTag::Game:
		m_pCurrentScene = new C_GameScene();
		break;
	case E_SceneTypeTag::Result:
		m_pCurrentScene = new C_ResultScene();
		break;
	case E_SceneTypeTag::Ranking:
		m_pCurrentScene = new C_RankingScene(scene);
		break;
	default:
		break;
	}
}

C_SceneManager::~C_SceneManager()
{
	if (m_pCurrentScene != nullptr)
	{
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
	}

	if (m_pTransition != nullptr)
	{
		delete m_pTransition;
		m_pTransition = nullptr;
	}

	Release();
}

void C_SceneManager::Init()
{
	LoadSelectWeaponData();
	LoadTextsData();
	LoadButtonData();
	LoadKeyData();
	LoadTex();
}

void C_SceneManager::LoadSelectWeaponData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Scene/SelectSceneWeaponStatData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < E_WeaponName::WeaponMax;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				char path[STRLENG] = {};

				fscanf_s(fp, "%[^,],%d,%d,%d,",
					name, STRLENG,
					&m_weaponStatData[i].m_damage,
					&m_weaponStatData[i].m_rate,
					&m_weaponStatData[i].m_speed
				);
			}
		}

		fclose(fp);
	}
}

void C_SceneManager::LoadTextsData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Scene/SceneFontsData.csv", "r") == 0)
	{
		char dummy[250] = {};

		while (fgets(dummy, 250, fp) != nullptr)//1行読み
		{
			int sceneType;

			S_TextsData data;
			float R, G, B, A;
			
			if (fscanf_s(fp, "%d,%d,%[^,],%f,%f,%d,%f,%f,%f,%f,%f,",
				&sceneType,
				&data.m_textTag,
				data.m_str, STRLENG,
				&data.m_pos.x,
				&data.m_pos.y,
				&data.m_textPos,
				&data.m_scale,
				&R,
				&G,
				&B,
				&A) == EOF)break;

			data.m_color = { R,G,B,A };
			m_sceneTexts[sceneType].push_back(data);
		}

		fclose(fp);
	}
}

void C_SceneManager::LoadButtonData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Scene/ButtonTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < (int)E_ButtonState::Max;i++)
		{
			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				char name[STRLENG] = {};
				char path[STRLENG] = {};
				
				fscanf_s(fp, "%[^,],%[^,],",
					name, STRLENG,
					path, STRLENG
				);

				m_buttonTex[i].Load(path);
			}
		}

		fclose(fp);
	}

	if (fopen_s(&fp, "Assets/Data/Scene/ButtonPosData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < (int)E_GameButtons::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				Math::Vector2 scale;

				fscanf_s(fp, "%[^,],%f,%f,%f,%f,",
					name, STRLENG,
					&m_sceneButtons[i].m_pos.x,
					&m_sceneButtons[i].m_pos.y,
					&scale.x,
					&scale.y
				);

				m_sceneButtons[i].m_texDrawSize = BUTTONTEXSIZE * scale;
			}
		}

		fclose(fp);
	}

}

void C_SceneManager::LoadKeyData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Key/KeyTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < (int)E_KeyTextures::Max;i++)
		{
			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				char name[STRLENG] = {};
				char path[STRLENG] = {};
				float scale;

				fscanf_s(fp, "%[^,],%[^,],%f,%f,%f,",
					name, STRLENG,
					path, STRLENG,
					&m_keyTex[i].m_texSize.x,
					&m_keyTex[i].m_texSize.y,
					&scale
				);

				m_keyTex[i].m_texDrawSize = m_keyTex[i].m_texSize * scale;
				m_keyTex[i].m_tex.Load(path);
			}
		}

		fclose(fp);
	}

	fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Key/KeyPosData.csv", "r") == 0)
	{
		char dummy[250] = {};

		while (fgets(dummy, 250, fp) != nullptr)//1行読み
		{
			int sceneType;

			S_KeyPosData data;

			if (fscanf_s(fp, "%d,%f,%f,%d,",
				&sceneType,
				&data.m_pos.x,
				&data.m_pos.y,
				&data.m_key) == EOF)break;

			m_keyTexPos[sceneType].push_back(data);
		}

		fclose(fp);
	}
}

void C_SceneManager::LoadTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Assets/Data/Scene/SceneTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < (int)E_GameTextures::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				char path[STRLENG] = {};
				Math::Vector2 scale;

				fscanf_s(fp, "%[^,],%[^,],%f,%f,%f,%f,%f,%f",
					name, STRLENG,
					path, STRLENG,
					&m_sceneTex[i].m_texPos.x,
					&m_sceneTex[i].m_texPos.y,
					&m_sceneTex[i].m_texSize.x,
					&m_sceneTex[i].m_texSize.y,
					&scale.x,
					&scale.y
				);

				m_sceneTex[i].m_texDrawSize = m_sceneTex[i].m_texSize * scale;
				m_sceneTex[i].m_tex.Load(path);
			}
		}

		fclose(fp);
	}
}

void C_SceneManager::Release()
{
	for (int i = 0;i < (int)E_GameTextures::Max;i++)
	{
		m_sceneTex[i].m_tex.Release();
	}

	for (int i = 0;i < (int)E_ButtonState::Max;i++)
	{
		m_buttonTex[i].Release();
	}

	for (int i = 0;i < (int)E_KeyTextures::Max;i++)
	{
		m_keyTex[i].m_tex.Release();
	}
}
