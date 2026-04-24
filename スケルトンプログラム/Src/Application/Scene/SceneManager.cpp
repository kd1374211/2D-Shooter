#include "SceneManager.h"

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
}
