#include "SceneManager.h"
#include "../Const/TextureConst.h"

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
	if (m_pCurrentScene != nullptr)delete m_pCurrentScene;

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
	LoadFontsData();
	LoadTex();
}

void C_SceneManager::LoadSelectWeaponData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Scene/SelectSceneWeaponStatData.csv", "r") == 0)
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

void C_SceneManager::LoadFontsData()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Scene/SceneFontsData.csv", "r") == 0)
	{
		char dummy[250] = {};

		while (fgets(dummy, 250, fp) != nullptr)//1行読み
		{
			int sceneType;

			S_TextsData data;
			float R, G, B, A;
			
			fscanf_s(fp, "%d,%d,%[^,],%f,%f,%f,%f,%f,%f,%f,", 
				&sceneType,
				&data.m_textTag,
				data.m_str,STRLENG,
				&data.m_pos.x,
				&data.m_pos.y,
				&data.m_scale,
				&R,
				&G,
				&B,
				&A);

			data.m_color = { R,G,B,A };
			m_sceneTexts[sceneType].push_back(data);
		}

		fclose(fp);
	}
}

void C_SceneManager::LoadTex()
{
	FILE* fp = nullptr;

	if (fopen_s(&fp, "Data/Scene/SceneTexData.csv", "r") == 0)
	{
		char dummy[250] = {};

		for (int i = 0;i < (int)E_GameTextures::Max;i++)
		{
			char name[STRLENG] = {};

			if (fgets(dummy, 250, fp) != nullptr)//1行読み
			{
				char path[STRLENG] = {};
				float scale;

				fscanf_s(fp, "%[^,],%[^,],%f,%f,%f,%f,%f,",
					name, STRLENG,
					path,STRLENG,
					&m_sceneTex[i].m_texPos.x,
					&m_sceneTex[i].m_texPos.y,
					&m_sceneTex[i].m_texSize.x,
					&m_sceneTex[i].m_texSize.y,
					&scale
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
}
