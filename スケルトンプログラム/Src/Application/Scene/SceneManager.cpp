#include "SceneManager.h"

void C_SceneManager::Update()
{
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
	if (m_pCurrentScene != nullptr)delete m_pCurrentScene;
}
