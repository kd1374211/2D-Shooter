#include "SceneManager.h"
#include "../Const/TextureConst.h"

void C_SceneManager::Update()
{
	if (m_sceneQueue != E_SceneTypeTag::None)
	{
		switch (m_sceneQueue)
		{
		case E_SceneTypeTag::Title:
			SetScene(new C_TitleScene());
			break;
		case E_SceneTypeTag::Select:
			SetScene(new C_SelectScene());
			break;
		case E_SceneTypeTag::Game:
			SetScene(new C_GameScene());
			break;
		default:
			break;
		}

		m_sceneQueue = E_SceneTypeTag::None;
	}

	if (m_pCurrentScene == nullptr)return;

	m_pCurrentScene->Update();
}

void C_SceneManager::Draw()
{
	m_pCurrentScene->Draw();
}

void C_SceneManager::SetScene(C_SceneBase* a_pBase)
{
	if (m_pCurrentScene != nullptr)delete m_pCurrentScene;
	m_pCurrentScene = a_pBase;
}

C_SceneManager::~C_SceneManager()
{
	if (m_pCurrentScene != nullptr)
	{
		delete m_pCurrentScene;
		m_pCurrentScene = nullptr;
	}

	ReleaseTex();
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

				fscanf_s(fp, "%[^,],%[^,],%f,%f,%f,%f,",
					name, STRLENG,
					path,STRLENG,
					&m_sceneTex[i].m_texPos.x,
					&m_sceneTex[i].m_texPos.y,
					&m_sceneTex[i].m_texSize.x,
					&m_sceneTex[i].m_texSize.y
				);

				m_sceneTex[i].m_tex.Load(path);
			}
		}

		fclose(fp);
	}
}

void C_SceneManager::ReleaseTex()
{
	for (int i = 0;i < (int)E_GameTextures::Max;i++)
	{
		m_sceneTex[i].m_tex.Release();
	}
}
