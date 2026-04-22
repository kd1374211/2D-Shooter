#pragma once
#include "SceneConst.h"

class C_SceneManager
{
public:

	void Update();
	void Draw();

	void SetScene(C_SceneBase* a_pBase);
	void SetSceneQueue(E_SceneTypeTag a_tag) { m_sceneQueue = a_tag; };

private:

	C_SceneBase* m_pCurrentScene;
	E_SceneTypeTag m_sceneQueue;

	C_SceneManager() :m_pCurrentScene(nullptr), m_sceneQueue(E_SceneTypeTag::None) {};
	~C_SceneManager();

public:

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager instance;
		return instance;
	}

};

#define SCENEMGR C_SceneManager::GetInstance()